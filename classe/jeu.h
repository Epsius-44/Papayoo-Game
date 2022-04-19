class Jeu {
private:
    vector<Joueur *> joueurs = {};
    Pli *pliActuel{};
    unsigned int symboleDe = 0;
    Carte *cartes[60]{};
    unsigned int joueurTour;
    unsigned int indexPapayoo = 0;
    unsigned int numManche = 1;
    unsigned int nombreManches = 0;
public:
    Jeu() {
        unsigned int nombreJoueursHumains = 0;
        unsigned int nombreJoueurs = 0;
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

        this->joueurTour = 0;

        cout << "Nombres de joueurs (humains et bots): ";
        while (!(cin >> nombreJoueurs) or nombreJoueurs<3 or nombreJoueurs>6){
            cout << "Saisie incorrecte, saisissez une valeur entre 3 et 6: ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
        cout << "Nombres de joueurs humains sur les " << nombreJoueurs << " joueurs: ";
        while (!(cin >> nombreJoueursHumains) or nombreJoueursHumains<0 or nombreJoueursHumains>nombreJoueurs){
            cout << "Saisie incorrecte, saisissez une valeur entre 1 et " << nombreJoueurs << ": ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
        cout << "Nombres de manches: ";
        while (!(cin >> this->nombreManches) or this->nombreManches<1){
            cout << "Saisie incorrecte, saisissez une valeur supérieur ou égal à 1: ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }

        for (unsigned int nbr = 0; nbr < nombreJoueursHumains; nbr++) {
            this->joueurs.push_back(new Humain("J" + to_string(nbr)));
        }
        for (unsigned int nbr = 0; nbr < nombreJoueurs - nombreJoueursHumains; nbr++) {
            this->joueurs.push_back(new Bot("Bot" + to_string(nbr)));
        }
        this->pliActuel = new Pli(this->joueurs);
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

    void melangerCarte() {
        this->melangerTableau(this->cartes, 60);
    }

    void distribueCarte() {
        this->melangerCarte();
        for (unsigned int joueur = 0; joueur < this->joueurs.size(); joueur++) {
            vector<Carte *> cartesJoueur = {};
            for (int i = 0; i < 60 / this->joueurs.size(); ++i) {
                cartesJoueur.push_back(this->cartes[i + (60 / this->joueurs.size()) * joueur]);
            }
            this->joueurs[joueur]->recoisCartes(cartesJoueur);
        }
    }

    void initialisationManche() {
        affichageManche();
        distribueCarte();
        vector<vector<Carte *>> troisCarteDonneeJoueurs = {};
        for (unsigned int i = 0; i < this->joueurs.size(); i++) {
            troisCarteDonneeJoueurs.push_back(this->joueurs[i]->donneTroisCarte());
        }

        for (unsigned int i = 0; i < this->joueurs.size(); i++) {
            this->joueurs[(i + 1) % this->joueurs.size()]->recoisCartes(troisCarteDonneeJoueurs[i]);
        }
        this->symboleDe = this->joueurs[(this->numManche-1)%this->joueurs.size()]->lancerDe();
        unsigned int index = 0;
        while (this->cartes[index]->getValeur() != 7 or this->cartes[index]->getCouleur() != this->symboleDe) {
            index++;
        }
        this->indexPapayoo = index;
        this->cartes[this->indexPapayoo]->setPoint(40);
    }

    void manche() {
        string vide;
        for (int mancheRecommence=0; mancheRecommence<this->nombreManches;mancheRecommence++) {
            unsigned int joueurDebute = (this->numManche - 1) % this->joueurs.size();
            this->initialisationManche();
            for (int i = 0; i < 60 / this->joueurs.size(); i++) {
                this->pliActuel->nouveauPli(joueurDebute);
                joueurDebute = this->pliActuel->commencerPli(this->symboleDe);
                this->affichageScore();
                attendre();
            }
            this->numManche++;
        }
        clearTerminal();
        cout << "\n score finale: \n";
        this->affichageScore();
        attendre();
    }

    void affichageManche(){
        cout << "\nmanche n° " << this->numManche << " / " << this->nombreManches << "\n";
    }

    void affichageScore(){
        cout << "\n*****************************************\nscores:\n";
        for (int j = 0; j<this->joueurs.size();j++){
            cout << this->joueurs[j]->getNom() << ": " << this->joueurs[j]->getPoints()<<" points\n";
        }
        cout << "*****************************************\n";
    }
};