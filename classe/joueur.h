class Joueur {
private:
    string nom;
protected:
    int unsigned points;
    vector<Carte *> cartes;
public:
    Joueur(string nom) {
        this->nom = nom;
        this->points = 0;
        this->cartes = {};
    }

    static bool tri(Carte *a, Carte *b) {
        return (a->getValeur() + 20 * a->getCouleur()) < (b->getValeur() + 20 * b->getCouleur());
    }


    void afficherCartes(vector<int> indexCartesJouable = {}) {
        int num = 0;
        for (int i = 0; i < this->cartes.size(); ++i) {
            bool present = false;
            if (indexCartesJouable.empty()) {
                present = true;
                num++;
                cout << num << ": ";
            } else {
                for (int h = 0; h < indexCartesJouable.size(); ++h) {
                    if (i == indexCartesJouable[h]) {
                        present = true;
                        num++;
                        cout << num << ": ";
                    }
                }
            }

            this->cartes[i]->afficherCarteCouleur(present);
            cout << "| ";
        }
    }

    void triCarte() {
        sort(this->cartes.begin(), this->cartes.end(), this->tri);
    }


    virtual void recoisCartes(vector<Carte *> carteEnPlus) {
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());
        this->triCarte();
    }

    int unsigned lancerDe() {
        int couleurs[4] = {2, 14, 9, 12};
        int resultDe = rand() % 4 + 1;
        cout << endl;
        cout << this->getNom() << " à lancé le dé et le papayoo est : ";
        couleurTerminal(0, couleurs[resultDe-1]);
        cout << " 7 ";
        resetCouleurTerminal();
        cout << endl;
        return resultDe;
    }

    virtual vector<Carte *> donneTroisCarte() {
        return {nullptr};
    };

    virtual Carte *jouerUneCarte(vector<Carte *> carteJouer) {
        return nullptr;
    };

    string getNom() {
        return this->nom;
    }

    int unsigned getPoints() {
        return this->points;
    }

    void addPoints(int unsigned points) {
        this->points += points;
    }

    vector<Carte *> getCartes() {
        return this->cartes;
    }

    void setCartes(vector<Carte *> cartes) {
        this->cartes = cartes;
        this->triCarte();

    }

    virtual void suppimerCarteIndex(int indexCarte) {
        this->cartes.erase(
                this->cartes.begin() + indexCarte); //supprime la carte donnée de la liste des cartes du joueur
    }

    virtual void suppimerCarte(Carte* carte) {
        int index = 0;
        while (this->cartes[index]->getCouleur()!=carte->getCouleur() or this->cartes[index]->getValeur()!=carte->getValeur() or index==this->cartes.size()-1){
            index++;
        }
        if (this->cartes[index]->getCouleur()==carte->getCouleur() and this->cartes[index]->getValeur()==carte->getValeur()){
            this->suppimerCarteIndex(index);
        }
    }

    vector<int> cartesDispo(unsigned int couleurCarteJouer = 0) {
        vector<int> indexCartesDispo = {}; //vector avec la liste des index des cartes qui peuvent être joué par le joueur (bot ou humain)
        for (int i = 0; i < this->cartes.size(); i++) { //boucle pour chaque carte présente dans le jeu du joueur
            if (couleurCarteJouer == 0 or this->cartes[i]->getCouleur() ==
                                          couleurCarteJouer) { //si aucune carte n'a été joué ou que la couleur de la carte correspond à la première carte joué pour le pli
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





