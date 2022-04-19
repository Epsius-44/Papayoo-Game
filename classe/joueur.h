class Joueur {
private:
    string nom; //nom du joueur
protected:
    int unsigned points; //nombre de points du joueur
    vector<Carte *> cartes; //liste des cartes du joueur
public:
    Joueur(string nom) { //constructeur prenant en paramètre le nom du joueur
        this->nom = nom;
        this->points = 0;
        this->cartes = {};
    }

    static bool tri(Carte *a, Carte *b) { //fonction utiliser pour trier les cartes du joueur par couler et par valeur
        return (a->getValeur() + 20 * a->getCouleur()) < (b->getValeur() + 20 * b->getCouleur());
    }


    void afficherCartes(vector<int> indexCartesJouable = {}) { //afficher les cartes du joueur, prend en paramètre une liste d'index de cartes qui peuvent être sélectionnables
        int num = 0;//numéro pour sélectionner la carte sélectionnable
        for (int i = 0; i < this->cartes.size(); ++i) {//pour chaque carte
            bool selectionnable = false; //booléen indiquant si la carte peut être sélectionnée
            if (indexCartesJouable.empty()) { //si la liste des index des cartes sélectionnables est vide alors toutes les cartes sont sélectionnable
                selectionnable = true; //carte est sélectionnable
                num++; //incrémenter le numéro de la carte sélectionnable
                cout << num << ": "; //afficher le numéro pour sélectionner la carte
            } else {//si la liste des index des cartes sélectionnables n'est pas vide
                for (int index = 0; index < indexCartesJouable.size(); index++) { //pour chaque index de carte dans liste des index des cartes sélectionnable
                    if (i == indexCartesJouable[index]) {
                        selectionnable = true; //carte est sélectionnable
                        num++; //incrémenter le numéro de la carte sélectionnable
                        cout << num << ": "; //afficher le numéro pour sélectionner la carte
                    }
                }
            }
            this->cartes[i]->afficherCarteCouleur(selectionnable); //afficher la carte
            cout << "| ";//afficher un séparateur entre chaque carte du jeu du joueur
        }
    }

    void triCarte() {//trier les cartes du joueur en fonction de la couleur et de la valeur des cartes
        sort(this->cartes.begin(), this->cartes.end(), this->tri);
    }


    virtual void recoisCartes(vector<Carte *> carteEnPlus) {//ajoute des cartes au jeu du joueur
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());//ajouter les cartes à la liste des cartes du joueur
        this->triCarte();//trier les cartes
    }

    int unsigned lancerDe() {//lancer le dé pour déterminer la couleur du papayoo
        int resultDe = rand() % 4 + 1; //chiffre aléatoire entre 1 et 4
        return resultDe; //retourne le chiffre obtenu
    }

    virtual vector<Carte *> donneTroisCarte() { //donner trois cartes
        return {nullptr};
    };

    virtual Carte *jouerUneCarte(vector<Carte *> carteJouer) {//jouer une carte
        return nullptr;
    };

    string getNom() {//retourner le nom du joueur
        return this->nom;
    }

    int unsigned getPoints() {//retourner le nombre de points du joueur
        return this->points;
    }

    void addPoints(int unsigned points) { //ajouter des points au joueur
        this->points += points;
    }

    vector<Carte *> getCartes() {//retourner la liste des cartes du joueur
        return this->cartes;
    }

    virtual void suppimerCarteIndex(int indexCarte) { //supprimer une carte de la liste des cartes du joueur à partir de son index dans celle-ci
        this->cartes.erase(this->cartes.begin() + indexCarte); //supprime la carte donnée de la liste des cartes du joueur
    }

    virtual void suppimerCarte(Carte* carte) { //supprimer une carte de la liste des cartes du joueur à partir de la couleur et de la valeur de la carte
        int index = 0; //index dans la liste des cartes du joueur de la carte à supprimer
        while (index!=this->cartes.size() and (this->cartes[index]->getCouleur()!=carte->getCouleur() or this->cartes[index]->getValeur()!=carte->getValeur())){ //tant que la carte correspondant à l'index dans la liste des cartes du joueur ne correspond pas à la carte qu'on veut supprimer ou qu'on dépasse la dernière carte de la liste des cartes du joueur
            index++; //ajouter 1 à index
        }
        if (index!=this->cartes.size()){ //si index ne correspond pas à la taille de la liste des cartes du joueur alors la carte peut être supprimer
            this->suppimerCarteIndex(index); //supprimer la carte grace à l'index obtenu
        }
    }

    vector<int> cartesDispo(unsigned int couleurCarteJouer = 0) {
        vector<int> indexCartesDispo = {}; //vector avec la liste des index des cartes qui peuvent être joué par le joueur (bot ou humain)
        for (int i = 0; i < this->cartes.size(); i++) { //boucle pour chaque carte présente dans le jeu du joueur
            if (couleurCarteJouer == 0 or this->cartes[i]->getCouleur() == couleurCarteJouer) { //si aucune carte n'a été joué ou que la couleur de la carte correspond à la première carte joué pour le pli
                indexCartesDispo.push_back(i); //ajouter index de la carte à la liste des cartes disponibles
            }
        }
        if (indexCartesDispo.empty()) { //si le jeu du joueur ne contient aucune carte avec la même couleur que la première carte jouée pour le pli
            for (int i = 0; i < this->cartes.size(); i++) {
                indexCartesDispo.push_back(i); //ajout de chaque carte du joueur dans la liste des cartes disponible
            }
        }
        return indexCartesDispo; //renvoi de la liste des index correspondant aux cartes que le joueur peut jouer
    }
};
