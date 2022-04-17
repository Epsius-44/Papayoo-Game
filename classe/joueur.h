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

    void afficherCartes() {
        for (int i = 0; i < this->cartes.size(); ++i) {
            cout << i + 1 << " | ";
            this->cartes[i]->afficherCarte();
        }
    }

    virtual void recoisCartes(vector<Carte *> carteEnPlus) {
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());
    }

    int unsigned lancerDe() {
        return rand() % 4 + 1;
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
    }

    vector<int> cartesDispo(unsigned int couleurCarteJouer = 0) {
        vector<int> indexCartesDispo = {}; //vector avec la liste des index des cartes qui peuvent être joué par le joueur (bot ou humain)
        for (int i = 0; i < this->cartes.size(); i++) { //boucle pour chaque carte présente dans le jeu du joueur
            if (couleurCarteJouer == 0 or this->cartes[i]->getCouleur() ==
                                          couleurCarteJouer) { //si aucune carte n'a été joué ou que la couleur de la carte correspond à la première carte joué pour le pli
                indexCartesDispo.push_back(i); //ajouter index de la carte à la liste des cartes disponibles
            }
        }
        if (indexCartesDispo.size() ==
            0) { //si le jeu du joueur ne contient aucune carte avec la même couleur que la première carte jouée pour le pli
            for (int i = 0; i < this->cartes.size(); i++) {
                indexCartesDispo.push_back(i); //ajout de chaque carte du joueur dans la liste des cartes dispo
            }
        }
        return indexCartesDispo; //renvoi de la liste des index correspondant aux cartes que le joueur peut jouer
    }
};





