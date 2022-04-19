class Jeu { // Classe jeu qui gère le déroulement d'une partie
private:
    vector<Joueur *> joueurs = {}; // Liste des joueurs pour interagir
    Pli *pliActuel{}; // Interaction avec le pli actuel
    unsigned int symboleDe = 0; // Stock la valeur du dé
    Carte *cartes[60]{}; // Liste des cartes du jeu
    unsigned int indexPapayoo = 0; // Stock l'index de la carte qui change
    unsigned int numManche = 1; // Stock le numéro de la manche actuel
    unsigned int nombreManches = 0; // Nombre de manches avant la fin du jeu
    TerminalInterface* terminal = new TerminalInterface; // Interaction avec l'interface terminal
public:
    // Contructeur de la classe
    Jeu() {
        unsigned int nombreJoueursHumains = 0; // Définie une valeur par défaut au nombre d'humains
        unsigned int nombreJoueurs = 0; // Définir une valeur par défaut au nombre de joueurs
        // --- Création des cartes ---
        unsigned int index = 0; // Variable d'itération du tableau cartes
        for (unsigned int couleur = 1; couleur <= 4; couleur++) { // Boucle qui crée les cartes des 4 couleurs
            for (unsigned int valeur = 1; valeur <= 10; ++valeur) { // Boucle qui crée les cartes de 1 à 10
                this->cartes[index] = new Carte(valeur, couleur, 0, terminal); // Instantiation de la carte et ajout dans le tableau cartes
                index++; // Augmentation de 1 de l'itérateur
            }
        }
        for (unsigned int valeur = 1; valeur <= 20; ++valeur) { // Boucle qui crée les cartes payoo de 1 à 20
            this->cartes[index] = new Carte(valeur, 5, valeur, terminal); // Instantiation de la carte et ajout dans le tableau cartes
            index++; // Augmentation de 1 de l'itérateur
        }

        // --- Création des joueurs ---
        // Nombre de joueurs
        cout << "Nombres de joueurs (humains et bots): ";
        while (!(cin >> nombreJoueurs) or nombreJoueurs<3 or nombreJoueurs>6){ // Tant que l'input n'est pas entre 3 et 6
            cout << "Saisie incorrecte, saisissez une valeur entre 3 et 6: ";
            cin.clear(); // vider l'input
            cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // Ignore l'input après un saut de ligne
        }
        // Nombre d'humains
        cout << "Nombres de joueurs humains sur les " << nombreJoueurs << " joueurs: ";
        while (!(cin >> nombreJoueursHumains) or nombreJoueursHumains<0 or nombreJoueursHumains>nombreJoueurs){ // tant du nombre d'humains est inférieur à 1 ou supérieur au nombre de joueurs
            cout << "Saisie incorrecte, saisissez une valeur entre 1 et " << nombreJoueurs << ": ";
            cin.clear(); // vider l'input
            cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // Ignore l'input après un saut de ligne
        }
        // --- Nombre de manches ---
        cout << "Nombres de manches: ";
        while (!(cin >> this->nombreManches) or this->nombreManches<1){ // tant que le nombre de manche est inférieur à 1
            cout << "Saisie incorrecte, saisissez une valeur supérieur ou égal à 1: ";
            cin.clear(); // vider l'input
            cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // Ignore l'input après un saut de ligne
        }
        // --- Création des joueurs ---
        for (unsigned int nbr = 0; nbr < nombreJoueursHumains; nbr++) { // boucle de création des Humains
            this->joueurs.push_back(new Humain("J" + to_string(nbr),terminal)); // Instanciation des humains et ajout dans le vecteur joueurs
        }
        for (unsigned int nbr = 0; nbr < nombreJoueurs - nombreJoueursHumains; nbr++) { // boucle de création des bots
            this->joueurs.push_back(new Bot("Bot" + to_string(nbr))); // Instanciation des bot et ajout dans le vecteur joueurs
        }
        this->pliActuel = new Pli(this->joueurs, terminal); // Intancie le premier pli et le stock dans pliActuel
    }

    // Methode qui mélange un tableau passer en paramètre sous forme de pointeur avec sa taille
    void melangerTableau(Carte *tableau[], int taille) { //fonction pour mélanger un tableau
        srand(time(NULL)); // Initialise le générateur de nombre aléatoire
        int indexAleatoire = -1;
        Carte *valeurIndexAleatoire;
        for (int index = 0; index < taille; index += 1) { //itération de chaque élément du tableau que l'on veut mélanger
            indexAleatoire = rand() % taille; //sélection aléatoire d'un index du tableau avec qui on va échanger les valeurs avec l'élément de l'index auquel est rendu la boucle
            valeurIndexAleatoire = tableau[indexAleatoire]; //enregistrement de la valeur situé à l'index choisi aléatoirement
            tableau[indexAleatoire] = tableau[index]; //modification de la valeur située à l'index choisi aléatoirement par la valeur située à l'index auquel est rendu la boucle
            tableau[index] = valeurIndexAleatoire; //modification de la valeur située à l'index auquel est rendu la boucle par l'ancienne valeur de l'index choisi aléatoirement
        }
    }

    // Methode qui mélange les cartes sans paramètre
    void melangerCarte() {
        this->melangerTableau(this->cartes, 60); // appel la methode melangerTableau pour mélanger les cartes
    }
    // Methode qui distribue les cartes sans paramètre
    void distribueCarte() {
        this->melangerCarte(); // Appel la méthode pour mélanger les cartes
        for (unsigned int joueur = 0; joueur < this->joueurs.size(); joueur++) { // Pour chaque joueur
            vector<Carte *> cartesJoueur = {}; // Créer un vecteur des cartes du joueur
            for (int i = 0; i < 60 / this->joueurs.size(); ++i) { // Pour 60 / nombre joueurs
                cartesJoueur.push_back(this->cartes[i + (60 / this->joueurs.size()) * joueur]); // Ajoute une carte au vecteur de carte du joueur
            }
            this->joueurs[joueur]->recoisCartes(cartesJoueur); // Utilise la methode recoisCarte du joueur avec le vecteur cartesJoueur pour lui donner
        }
    }

    // Methode qui initialise la manche
    void initialisationManche() {
        this->affichageManche(); // Appel la methode affichageManche
        this->distribueCarte(); // Distribue les cartes avec la methode
        vector<vector<Carte *>> troisCarteDonneeJoueurs = {}; // Initialise le vecteur des cartes échanger
        for (unsigned int i = 0; i < this->joueurs.size(); i++) { // Pour chaque joueur
            troisCarteDonneeJoueurs.push_back(this->joueurs[i]->donneTroisCarte()); // Appel la methode pour donner trois cartes du joueur
        }

        for (unsigned int i = 0; i < this->joueurs.size(); i++) { // Pour chque joueur
            this->joueurs[(i + 1) %
                          this->joueurs.size()]->recoisCartes(troisCarteDonneeJoueurs[i]); // Appel la methode pour recevoir les cartes donner par le joueur précédant
        }
        this->initialisationPapayoo();
    }

    void initialisationPapayoo(){
        this->symboleDe = this->joueurs[(this->numManche - 1) % this->joueurs.size()]->lancerDe(); // Appel la fonction lancerDe du premier joueur de la manche et le stock
        unsigned int index = 0; // Index itérer pour avoir l'index de la carte Papayoo
        while (this->cartes[index]->getValeur() != 7 or this->cartes[index]->getCouleur() != this->symboleDe) { // Tant que la carte est différente de 7 et d'une autre couleur que le dé
            index++; // Incrémenter l'index
        }
        this->indexPapayoo = index; // Stock l'index de la carte Papayoo
        this->cartes[this->indexPapayoo]->setPoint(40); // Change le nombre de point du Papayoo

        for (int joueur=0;joueur<this->joueurs.size();joueur++){
            this->joueurs[joueur]->setCouleurDe(this->symboleDe);
        }
    }

    // Methode pour joueur (regroupe toutes les manches)
    void jouer() {
        for (int mancheRecommence=0; mancheRecommence<this->nombreManches;mancheRecommence++) { // Pour i inférieur au nombre de manches
            unsigned int joueurDebute = (this->numManche - 1) % this->joueurs.size(); // Définie le joueur qui commence
            this->initialisationManche(); // Initialise la manche avec la methode associer
            for (int i = 0; i < 60 / this->joueurs.size(); i++) { // Pour le nombre de carte par joueur
                joueurDebute = this->pliActuel->commencerPli(this->symboleDe,joueurDebute); // Initaliser un pli avec la methode associe au pli actuel
                this->affichageScore(); // Affiche les scores avec la methode associé
                this->terminal->attendre(); // Attendre pour laisser l'affichage des scores visibles
            }
            this->numManche++; // Recommencer une manche
        }
        this->terminal->clearTerminal(); // Efface la console avec une methode du terminal
        cout << "\n score finale: \n";
        this->affichageScore(); // Affiche le score finale
        this->terminal->attendre(); // Attendre pour laisser l'affichage des scores visibles
    }

    // Methode qui affiche le numéro de la manche
    void affichageManche(){
        cout << "\nmanche n° " << this->numManche << " / " << this->nombreManches << "\n";
    }

    // Methode qui affiche le score
    void affichageScore(){
        cout << "\n*****************************************\nscores:\n";
        for (int j = 0; j<this->joueurs.size();j++){ // Pour chaque joueur
            cout << this->joueurs[j]->getNom() << ": " << this->joueurs[j]->getPoints()<<" points\n";
        }
        cout << "*****************************************\n";
    }
};