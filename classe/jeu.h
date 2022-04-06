class Jeu {
private:
    vector<Joueur *> joueurs = {};
    Pli *pliActuel{};
    unsigned int symboleDe = 0;
    Carte *cartes[60]{};
public:
    Jeu(unsigned int nombreJoueurs) {
        unsigned int index = 0;
        for (unsigned int couleur = 1; couleur <= 4; couleur++) {
            for (unsigned int valeur = 1; valeur <= 10; ++valeur) {
                index++;
                this->cartes[index] = new Carte(valeur, couleur, 0);
            }
        }
        for (unsigned int valeur = 1; valeur <= 20; ++valeur) {
            index++;
            this->cartes[index] = new Carte(valeur, 5, valeur);
        }

        this->pliActuel = new Pli;

        for (unsigned int nbr = 0; nbr < nombreJoueurs; nbr++) {
            this->joueurs.push_back(new Joueur('J' + to_string(nbr)));
        }
    }

    void melangereCarte() {
        unsigned int seed = 666;
        shuffle(this->cartes[0], this->cartes[59], default_random_engine(seed));
    }

    void distribueCarte() {
        this->melangereCarte();
        for (unsigned int joueur = 0; joueur < this->joueurs.size(); joueur++) {
            vector<Carte*> cartesJoueur = {};
            for (int i = 0; i < 60 / this->joueurs.size(); ++i) {
                cartesJoueur.push_back(this->cartes[i+(60/ this->joueurs.size())*joueur]);
            }
            this->joueurs[joueur]->recoisCartes(cartesJoueur);
        }
    }

    void nouveauPli(unsigned int idJoueurDebute) {
        this->pliActuel->nouveauPli(idJoueurDebute);
    }

    void setSymboleDe(unsigned int de) {
        assert(de < 1 or de > 4 && "La valeur du dé n'est pas valable, elle doit être situé entre 1 et 4");
        this->symboleDe = de;
    }

    unsigned int getSybmboleDe() {
        return this->symboleDe;
    }

};