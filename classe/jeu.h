class Jeu {
private:
    vector<Joueur *> joueurs = {};
    Pli *pliActuel{};
    unsigned int symboleDe = 0;
    Carte *cartes[60]{};
    unsigned int joueurTour;
    unsigned int indexPapayoo = 0;
public:
    Jeu(unsigned int nombreJoueurs, unsigned int nombreJoueursHumains) {
        unsigned int index = 0;
        for (unsigned int couleur = 1; couleur <= 4; couleur++) {
            for (unsigned int valeur = 1; valeur <= 10; ++valeur) {
                this->cartes[index] = new Carte(valeur, couleur, 0);
                index++;
            }
        }
        for (unsigned int valeur = 1; valeur <= 20; ++valeur) {
            this->cartes[index] = new Carte(valeur, 5, valeur);
            index++;
        }

        this->pliActuel = new Pli;
        this->joueurTour = 0;

        for (unsigned int nbr = 0; nbr < nombreJoueursHumains; nbr++) {
            this->joueurs.push_back(new Humain("J" + to_string(nbr)));
        }
        for (unsigned int nbr = 0; nbr < nombreJoueurs - nombreJoueursHumains; nbr++) {
            this->joueurs.push_back(new Bot("Bot" + to_string(nbr)));
        }
    }

    void melangerTableau(Carte *tableau[], int taille) { //fonction pour mélanger un tableau
        srand(time(NULL));
        int indexAleatoire = -1;
        Carte *valeurIndexAleatoire;
        for (int index = 0;
             index < taille; index += 1) { //itération de chaque élément du tableau que l'on veut mélanger
            indexAleatoire = rand() %
                             taille; //sélection aléatoire d'un index du tableau avec qui on va échanger les valeurs avec l'élément de l'index auquel est rendu la boucle
            valeurIndexAleatoire = tableau[indexAleatoire]; //enregistrement de la valeur situé à l'index choisi aléatoirement
            tableau[indexAleatoire] = tableau[index]; //modification de la valeur située à l'index choisi aléatoirement par la valeur située à l'index auquel est rendu la boucle
            tableau[index] = valeurIndexAleatoire; //modification de la valeur située à l'index auquel est rendu la boucle par l'ancienne valeur de l'index choisi aléatoirement
        }
    }

    void melangereCarte() {
        unsigned int seed = 666;
        this->melangerTableau(this->cartes, 60);
    }

    void distribueCarte() {
        this->melangereCarte();
        for (unsigned int joueur = 0; joueur < this->joueurs.size(); joueur++) {
            vector<Carte *> cartesJoueur = {};
            for (int i = 0; i < 60 / this->joueurs.size(); ++i) {
                cartesJoueur.push_back(this->cartes[i + (60 / this->joueurs.size()) * joueur]);
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

    void initialisationManche() {
        distribueCarte();

        vector<vector<Carte *>> troisCarteDonneeJoueurs = {};
        for (unsigned int i = 0; i < this->joueurs.size(); i++) {
            troisCarteDonneeJoueurs.push_back(this->joueurs[i]->donneTroisCarte());
        }

        for (unsigned int i = 0; i < this->joueurs.size(); i++) {
            this->joueurs[i]->recoisCartes(troisCarteDonneeJoueurs[i + 1 % this->joueurs.size()]);
        }
        this->symboleDe = this->joueurs[this->joueurTour]->lancerDe();
        unsigned int index = 0;


        while (this->cartes[index]->getValeur() != 7 or this->cartes[index]->getCouleur() != this->symboleDe) {
            index++;
        }
        this->indexPapayoo = index;
        this->cartes[this->indexPapayoo]->setPoint(40);
    }

    void manche() {
        this->initialisationManche();
        cout << "test" << endl;

        for (unsigned int pli = 0; pli < 60 / this->joueurs.size(); pli++) {
            this->pliActuel->nouveauPli(this->joueurTour);

            for (unsigned int numJoueurTour = 0; numJoueurTour < this->joueurs.size(); numJoueurTour++) {
                unsigned int indexJoueur = (this->joueurTour + numJoueurTour) % this->joueurs.size();
                this->pliActuel->ajouterCarteJouer(this->joueurs[indexJoueur]->jouerUneCarte());
            }
            this->joueurTour = this->pliActuel->trouveGagnantPli();
            this->joueurs[this->joueurTour]->addPoints(this->pliActuel->calculPointPli());
        }

        this->pliActuel->nouveauPli(this->joueurTour);
        this->joueurTour = (this->joueurTour + 1) % this->joueurs.size();
        this->cartes[this->indexPapayoo]->setPoint(0);
    }
};