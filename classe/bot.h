class Bot : public Joueur {
private:
    unsigned int nombreCartesCouleur[5] = {0, 0, 0, 0, 0}; //nombre de cartes par couleur
    unsigned int sommeCartesCouleur[5] = {0, 0, 0, 0, 0}; //somme des valeurs des cartes par couleur
    float valeurCartesCouleur[5] = {0, 0, 0, 0,
                                    0}; //calcul pour savoir quelle couleur il faut éliminer en premier ou donner
    int couleurDe = 0; //couleur du dé

public:
    Bot(string nom) : Joueur(nom) {}


    void setCouleurDe(int couleurDe) { //définition de la couleur du dé
        this->couleurDe = couleurDe;
    };

    void calculValeurCartes() { //calcul de la valeur d'une couleur
        for (int i = 0; i < 5; i++) { //pour chaque couleur
            if (this->couleurDe == i + 1) { //couleur correspondante au dé
                this->valeurCartesCouleur[i] = round(this->sommeCartesCouleur[i] / this->nombreCartesCouleur[i] *
                                                     (1 + (float(this->nombreCartesCouleur[i] + 2) / 10)) * 10) /
                                               10; // =x/y*((1.x)+0.2) | x→ nombre de cartes d'une couleur    y→ somme des valeurs des cartes d'une couleur | arrondi au dixième près
            } else if (this->couleurDe != 4) { //couleur ne correspondant pas au payoo
                this->valeurCartesCouleur[i] = round((this->sommeCartesCouleur[i] / this->nombreCartesCouleur[i] *
                                                      (1 + (float(this->nombreCartesCouleur[i]) / 10))) * 10) /
                                               10; // =x/y*(1.x) | x→ nombre de cartes d'une couleur    y→ somme des valeurs des cartes d'une couleur |arrondi au dixième près
            } else { //couleur correspondante au payoo
                this->valeurCartesCouleur[i] = round((this->sommeCartesCouleur[i] / this->nombreCartesCouleur[i] *
                                                      (1 + (float(this->nombreCartesCouleur[i]) / 10))) * 5) /
                                               10; // =(x/y*(1.x))/2 | x→ nombre de cartes d'une couleur    y→ somme des valeurs des cartes d'une couleur |arrondi au dixième près

            }
        }
    }

    virtual void recoisCartes(vector<Carte *> carteEnPlus) {
        unsigned int couleurCarte = 0;
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(),
                            carteEnPlus.end()); //insertion des cartes dans la liste des cartes du joueur
        for (int i = 0; i < carteEnPlus.size(); i++) { //boucle pour chaque carte reçue par le joueur
            couleurCarte = carteEnPlus[i]->getCouleur() - 1; //couleur de la carte
            this->nombreCartesCouleur[couleurCarte] += 1; //ajoute +1 aux nombres de carte de cette couleur
            this->sommeCartesCouleur[couleurCarte] += carteEnPlus[i]->getValeur(); //ajoute la valeur de cette carte à la somme de cette couleur
        }
        this->calculValeurCartes(); //calcul score par couleur
        this->triCarte();
    }

    int indexCarteDefausser() {
        int couleurCarteDonne = 0; //couleur de la carte qui sera données
        int carteIndexSelect = -1; //position de la carte dans la liste des cartes du joueur
        vector<int> couleursPossible = this->couleursAvecLePlusDeValeurs(); //liste des couleurs avec le plus de valeurs
        srand(time(NULL));
        couleurCarteDonne = couleursPossible[rand() %
                                             couleursPossible.size()]; //choisis une couleur au hasard parmi la liste des couleurs possibles
        for (int indexCarte = 0; indexCarte < this->cartes.size(); indexCarte++) {
            if (this->cartes[indexCarte]->getCouleur() == couleurCarteDonne and
                (carteIndexSelect == -1 or this->cartes[indexCarte]->getValeur() >
                this->cartes[carteIndexSelect]->getValeur())) {
                carteIndexSelect = indexCarte; //sélectionne la carte avec la plus grande valeur et de la même couleur que la couleur sélectionner
            }
        }
        return carteIndexSelect;
    }

    virtual void supprimerCarte(int indexCarte) {
        this->nombreCartesCouleur[this->cartes[indexCarte]->getCouleur() -
                                  1] -= 1; //ajoute -1 au nombre de cartes de la couleur de la carte données
        this->sommeCartesCouleur[this->cartes[indexCarte]->getCouleur() -
                                 1] -= this->cartes[indexCarte]->getValeur(); //enlève la valeur de la carte donnée au nombre de points des cartes de la couleur de la carte données
        this->cartes.erase(this->cartes.begin() + indexCarte); //supprime la carte donnée de la liste des cartes du joueur
        this->calculValeurCartes(); //recalcule la valeur des couleurs des cartes du joueur
    }

    virtual vector<Carte *> donneTroisCarte() {
        vector<Carte *> carteDonne; //vector avec les cartes qui seront données
        for (int i = 0; i < 3; i++) {//boucle pour sélectionner 3 cartes
            int carteIndexSelect = this->indexCarteDefausser();
            carteDonne.push_back(this->cartes[carteIndexSelect]); //ajoute la carte à la liste des cartes données
            this->supprimerCarte(carteIndexSelect); //supprime la carte du jeu du joueur
        }
        return carteDonne;
    }

    vector<int> couleursAvecLePlusDeValeurs() {
        float valeurCarteCouleurSelect = 0; //valeur de la plus grosse valeur
        vector<int> couleurPossible; //liste des couleurs possible avec les plus grosses valeurs
        for (int couleur = 0;
             couleur < 5; couleur++) { //récupère la plus grande valeur de couleurs dans le jeu du joueur
            if (this->valeurCartesCouleur[couleur] > valeurCarteCouleurSelect) {
                valeurCarteCouleurSelect = this->valeurCartesCouleur[couleur];
            }
        }
        for (int couleur = 0;
             couleur < 5; couleur++) { //ajoute toutes les couleurs qui ont la plus grande valeur de couleurs
            if (this->valeurCartesCouleur[couleur] == valeurCarteCouleurSelect) {
                couleurPossible.push_back(couleur + 1);
            }
        }
        return couleurPossible;
    }

    virtual Carte *jouerUneCarte(vector<Carte *> carteJouer) {
        int indexCarteJouer = -1;
        if (carteJouer.empty()) { //Si le joueur commence le pli
            indexCarteJouer = this->jouerNouvelleCarte();
        } else { //Si le joueur ne commence pas le pli
            indexCarteJouer = this->jouerCarteBot(carteJouer);
        }
        Carte *carteJouerJoueur = this->cartes[indexCarteJouer]; //enregistre la carte que le joueur va jouer
        this->supprimerCarte(indexCarteJouer); //supprime la carte du jeu du joueur
        return carteJouerJoueur; //retourne la carte jouer par le joueur
    }

    int carteLaPlusProche(vector<int> indexCarte, unsigned int valeurCible) { //renvoie l'index de la carte la plus proche de la valeurCible et qui est en priorité inférieure sans qu'elle soit égale à la valeur cible
        unsigned int valeurCarteSelect = this->cartes[indexCarte[0]]->getValeur(); //carte sélectionnée correspond à la première carte de la liste des cartes passée en paramètres de la fonction
        int indexCarteSelect = indexCarte[0];
        for (int i = 1; i <
                        indexCarte.size(); i++) { //pour chaque carte de la liste des cartes passée en paramètres de la fonction sauf la première carte
            unsigned int valeurCarte = this->cartes[indexCarte[i]]->getValeur(); //valeur de la carte
            if ((valeurCarte > valeurCible and valeurCarte < valeurCarteSelect) or
                (valeurCarte < valeurCible and valeurCarte > valeurCarteSelect) or
                (valeurCarteSelect > valeurCible and valeurCarte <
                                                     valeurCarteSelect)) { //vérifier si la valeur de la carte est supérieure à la valeur cible mais inférieure à la valeur de la carte déjà sélectionnée ou si la valeur de la carte est inférieure à la valeur cible mais supérieure à la valeur de la carte déjà sélectionnée
                valeurCarteSelect = valeurCarte;
                indexCarteSelect = indexCarte[i];//sélection de la carte
            }
        }
        return indexCarteSelect; //retourne la carte sélectionnée
    }


    int jouerCarteBot(vector<Carte *> carteJouer) {
        int indexCarteJouer = -1;
        unsigned int couleurAJouer = carteJouer[0]->getCouleur(); //couleur qui doit être joué
        vector<int> cartePossibleJouer = this->cartesDispo(
                couleurAJouer); //liste des index correspondants aux cartes qui peuvent être joué
        if (cartePossibleJouer.size() == 1) { //s'il n'y a qu'une seule carte qui peut être joué
            return cartePossibleJouer[0];
        }
        if (this->cartes[cartePossibleJouer[0]]->getCouleur() ==
            couleurAJouer) { //si les cartes qui peuvent être joué correspondent à la couleur demandée
            unsigned int valeurLaPlusHaute = carteJouer[0]->getValeur();
            for (int i = 1; i <
                            carteJouer.size(); i++) { //récupération de la valeur de la carte la plus forte jouée et de la même couleur que celle demandé
                if (carteJouer[i]->getValeur() > valeurLaPlusHaute and carteJouer[i]->getCouleur() == couleurAJouer) {
                    valeurLaPlusHaute = carteJouer[i]->getValeur();
                }
            }
            if (couleurAJouer == this->couleurDe and valeurLaPlusHaute >
                                                     7) { //couleur demandée correspond à celle du papayoo et la valeur la plus haute est supérieur à 7 alors joueur essaye de poser le 7 (papayoo)
                for (int i = 1; i < carteJouer.size(); i++) {
                    if (this->cartes[cartePossibleJouer[i]]->getValeur() == 7) {
                        return cartePossibleJouer[i]; //joue le papayoo car un autre joueur a joué une carte plus forte que 7 et va donc probablement ramassé les cartes à la fin du pli
                    }
                }
            }
            indexCarteJouer = this->carteLaPlusProche(cartePossibleJouer, valeurLaPlusHaute); //joue la carte qui a une valeur soit en dessous de la valeur la plus haute du pli soit qui à une valeur supérieure mais la plus proche possible de la carte la plus haute
            if (couleurAJouer == this->couleurDe and this->cartes[indexCarteJouer]->getValeur() ==
                                                     7) { //évité que le joueur joue le papayoo si dans les cartes joué par les autres joueurs aucune est supérieur à 7
                cartePossibleJouer.erase(cartePossibleJouer.begin() + indexCarteJouer);
                indexCarteJouer = this->carteLaPlusProche(cartePossibleJouer, valeurLaPlusHaute);
            }
            return indexCarteJouer;
        } else { //si le joueur peut se défausser de n'importe quelle carte de son jeu
            for (int i = 0; i < cartePossibleJouer.size(); i++) { //se défausse en priorité du papayoo
                if (this->cartes[cartePossibleJouer[i]]->getCouleur() == this->couleurDe and
                    this->cartes[cartePossibleJouer[i]]->getCouleur() == 7) {
                    return cartePossibleJouer[i];
                }
            }
            return indexCarteDefausser();
        }
    }

    int jouerNouvelleCarte() {
        vector<int> couleursPossibleJouer; //liste dex couleurs qui peuvent avec la valeur la plus faible
        float valeurCouleurSelect = 0;
        int couleurSelect = 0;
        for (int couleurs = 0; couleurs < 5; couleurs++) { //pour chaque couleur
            if (this->nombreCartesCouleur[couleurs] != 0 and
                (valeurCouleurSelect == 0 or this->valeurCartesCouleur[couleurs] <
                                             valeurCouleurSelect)) { //si la couleur contient des cartes et que la couleur a la valeur la plus faible
                valeurCouleurSelect = this->valeurCartesCouleur[couleurs]; //attribuer la valeur la plus faible à valeurCouleurSelect
            }
        }
        for (int couleurs = 0; couleurs < 5; couleurs++) { //pour chaque couleur
            if (this->valeurCartesCouleur[couleurs] == valeurCouleurSelect) { //si la couleur à la valeur la plus faible
                couleursPossibleJouer.push_back(
                        couleurs + 1); //ajouter la couleur à la liste des couleurs qui va être joué
            }
        }
        couleurSelect = couleursPossibleJouer[rand() %
                                              couleursPossibleJouer.size()]; //sélection aléatoire d'une couleur

        vector<int> indexCartesCouleurSelect; //liste des cartes du joueur dont la couleur correspond à celle de la couleur sélectionnée
        for (int indexCarte = 0; indexCarte < this->cartes.size(); indexCarte++) { //pour chaque carte du joueur
            if (this->cartes[indexCarte]->getCouleur() ==
                couleurSelect) { //si la carte à la même couleur que celle sélectionnée
                indexCartesCouleurSelect.push_back(indexCarte); //ajouté cette carte à la liste des cartes avec la couleur sélectionnée
            }
        }
        return this->carteLaPlusProche(indexCartesCouleurSelect, round(this->valeurCartesCouleur[couleurSelect -
                                                                                                 1])); //retourne l'index de la carte qui est le plus proche de la valeur de la couleur
    }

};