class Humain : public Joueur { //classe Humain hérité de la classe Joueur
private:
    TerminalInterface* terminal; //interaction avec le terminal
public:
    Humain(string nom,TerminalInterface* terminal) : Joueur(nom) { //constructeur, prend en paramètres le nom du joueur et le terminal avec qui interagir
        this->terminal = terminal;
    }

    virtual vector<Carte *> donneTroisCarte() { //fonction pour donner trois cartes à son voisin suivant dans la liste des joueurs
        vector<int> carteSelectionnable; //index des cartes qui ne sont pas données dans la liste des cartes du joueur
        vector<Carte*> carteSelectJoueur; //liste des cartes à données
        int carteSelect = 0; //index de la carte sélectionner dans la liste des cartes du joueur
        for (int carte = 0;carte < this->cartes.size(); carte++){ //pour chaque carte du joueur
            carteSelectionnable.push_back(carte); //ajouter l'index de la carte à la liste des cartes qui ne sont pas données
        }
        for (int i=1; i<=3; i++){ //répéter 3 fois
            carteSelect = this->selectionCarte(&carteSelectionnable, this->getNom()+" sélectionner 3 trois cartes à donner"); //message pour demander quelle carte donnée et attribue l'index de la carte donnée à la variable carteSelect
            carteSelectJoueur.push_back(this->cartes[carteSelectionnable[carteSelect-1]]); //ajoute la carte à la liste des cartes données
            carteSelectionnable.erase(carteSelectionnable.begin()+carteSelect-1); //supprime l'index de la carte de la liste des cartes qui ne sont pas données → n'est plus sélectionnable par le joueur
        }
        for (int i=0;i<3;i++){ //répéter 3 fois
            this->suppimerCarte(carteSelectJoueur[i]); //supprimer la carte du jeu du joueur → boucle à part afin que la carte s'affiche dans la liste des cartes du joueur lorsqu'il sélectionne les cartes à données bien qu'elle ne soit plus sélectionnable
        }
        return carteSelectJoueur; //retourne la liste des cartes supprimées
    }

    virtual Carte *jouerUneCarte(vector<Carte*> carteJouer) { //jouer une carte, prend en paramètre la liste des cartes jouées dans le pli
        unsigned int couleurCarteJeu = 0; //couleur de la carte qui doit être joué
        Carte* carteJoueurJouer; //carte jouée par le joueur
        if (!carteJouer.empty()){ //si une carte a déjà été joué → le joueur n'a donc pas le choix de la couleur à jouer
            couleurCarteJeu = carteJouer[0]->getCouleur(); //couleur de la première carte qui a été jouer dans le pli → couleur que doit jouer le joueur
        }
        vector<int> carteJouable = this->cartesDispo(couleurCarteJeu); //liste des index des cartes que le joueur peut jouer
        int indexCarteJouer = carteJouable[selectionCarte(&carteJouable,this->getNom()+" sélectionner la carte à jouer")-1]; //sélection de la carte jouer
        carteJoueurJouer = this->cartes[indexCarteJouer]; //carte jouer par le joueur
        this->suppimerCarteIndex(indexCarteJouer); //supprimer la carte jouer des cartes du joueur à partir de l'index de celle-ci
        return carteJoueurJouer; //retourne la carte jouée
    }

    int selectionCarte(vector<int> *indexCartesJouable={},string message="Sélectionner la carte à jouer"){//sélection d'une carte dans le jeu du joueur, prend en paramètre la liste des index des cartes qui peuvent être sélectionnées et le message à afficher lors de la demande de sélection de la carte
        int nbrElementSelect = this->cartes.size(); //nombre de cartes qui peuvent être sélectionnée → par défaut cela correspond aux nombres de cartes dans la liste de cartes du joueur
        if (!indexCartesJouable->empty()){//si la liste des index des cartes sélectionnable alors toutes les cartes du joueur sont sélectionnable
            nbrElementSelect = indexCartesJouable->size();
        }
        int elementSelectJoueur; //index de la carte sélectionner dans la liste des cartes du joueur
        cout << "\n"; //reviens à la ligne
        this->afficherCartes(*indexCartesJouable); //afficher les cartes du joueur
        cout << "\n"; //reviens à la ligne
        cout << message << " (entre 1 et " << nbrElementSelect << "): "; //demander le numéro de la carte à sélectionner
        while (!(cin >> elementSelectJoueur) or elementSelectJoueur<1 or elementSelectJoueur>indexCartesJouable->size()){ //tant que la réponse de l'utilisateur n'est pas valide demander une nouvelle réponse
            cout << "Saisie incorrecte, recommencez: "; //message pour redemander une réponse
            cin.clear(); //effacer ce que contient l'input
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
        this->terminal->clearTerminal(); //effacer le terminal
        return elementSelectJoueur; //retourner l'index de la carte sélectionner dans la liste des cartes du joueur
    }
};