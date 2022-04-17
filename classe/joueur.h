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

    void recoisCartes(vector<Carte *> carteEnPlus) {
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());
    }

    int unsigned lancerDe() {
        return rand() % 4 + 1;
    }

    virtual vector<Carte *> donneTroisCarte() {
        return {nullptr};
    };

    virtual Carte *jouerUneCarte() {
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

    vector<int> cartesDispo(int couleurCarteJouer=0) {
        vector<int> indexCartesDispo = {}; //vector avec la liste des index des cartes qui peuvent être joué par le joueur (bot ou humain)
        for (int i = 0; i < this->cartes.size(); i++) { //boucle pour chaque carte présente dans le jeu du joueur
            if (couleurCarteJouer == 0 or this->cartes[i]->getCouleur()==couleurCarteJouer) { //si aucune carte n'a été joué ou que la couleur de la carte correspond à la première carte joué pour le pli
                indexCartesDispo.push_back(i); //ajouter index de la carte à la liste des cartes disponibles
            }
        }
        if (indexCartesDispo.size()==0){ //si le jeu du joueur ne contient aucune carte avec la même couleur que la première carte joué pour le pli
            for (int i = 0; i < this->cartes.size(); i++) {
                    indexCartesDispo.push_back(i); //ajout de chaque carte du joueur dans la liste des cartes dispo
            }
        }
        return indexCartesDispo; //renvoi de la liste des index correspondant aux cartes que le joueur peut jouer
    }
}

class Humain : public Joueur {
public:
    Humain(string nom) : Joueur(nom) {}

    virtual vector<Carte *> donneTroisCarte() {
        //shuffle(this->cartes.begin(), this->cartes.end(), default_random_engine(666));
        // TODO Remove card
        return vector<Carte *>(this->cartes.begin(), this->cartes.begin());
    }

    virtual Carte *jouerUneCarte() {
        unsigned int idCarteChoisi;
        this->afficherCartes();
        cout << "Choisir une carte entre 1 et " << this->cartes.size() << " : ";
        cin >> idCarteChoisi;
        Carte *carteChoisi = this->cartes[idCarteChoisi - 1];
        cout << "Le joueur " << this->getNom() << " joue : ";
        carteChoisi->afficherCarte();
        this->cartes.erase(this->cartes.begin() + idCarteChoisi - 1);
        return carteChoisi;
    }
};

class Bot : public Joueur {
public:
    Bot(string nom) : Joueur(nom) {}

    virtual vector<Carte *> donneTroisCarte() {
        shuffle(this->cartes.begin(), this->cartes.end(), default_random_engine(666));
        return vector<Carte *>(this->cartes.begin(), this->cartes.begin() + 3);
    }

    virtual Carte *jouerUneCarte() {
        return this->cartes[rand() % this->cartes.size()];
    }
};