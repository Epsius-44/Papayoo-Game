class Humain : public Joueur {
public:
    Humain(string nom) : Joueur(nom) {}

    virtual vector<Carte *> donneTroisCarte() {
        vector<int> carteSelectionnable;
        vector<Carte*> carteSelectJoueur;
        int carteSelect = 0;
        for (int carte = 0;carte < this->cartes.size(); carte++){
            carteSelectionnable.push_back(carte);
        }
        for (int i=1; i<=3; i++){
            carteSelect = this->selectionCarte(&carteSelectionnable, this->getNom()+" sélectionner 3 trois cartes à donner");
            carteSelectJoueur.push_back(this->cartes[carteSelectionnable[carteSelect-1]]);
            carteSelectionnable.erase(carteSelectionnable.begin()+carteSelect-1);
        }
        for (int i=0;i<3;i++){
            this->suppimerCarte(carteSelectJoueur[i]);
        }
        return carteSelectJoueur;
    }

    virtual Carte *jouerUneCarte(vector<Carte*> carteJouer) {
        unsigned int couleurCarteJeu = 0;
        Carte* carteJoueurJouer;
        if (!carteJouer.empty()){
            couleurCarteJeu = carteJouer[0]->getCouleur();
        }
        vector<int> carteJouable = this->cartesDispo(couleurCarteJeu);
        int indexCarteJouer = carteJouable[selectionCarte(&carteJouable,this->getNom()+" sélectionner la carte à jouer")-1];
        carteJoueurJouer = this->cartes[indexCarteJouer];
        cout << "Le joueur " << this->getNom() << " joue : ";
        carteJoueurJouer->afficherCarteCouleur();
        this->suppimerCarteIndex(indexCarteJouer);
        return carteJoueurJouer;
    }

    int selectionCarte(vector<int> *indexCartesJouable={},string message="Sélectionner la carte à jouer"){
        int nbrElementSelect = this->cartes.size();
        if (!indexCartesJouable->empty()){
            nbrElementSelect = indexCartesJouable->size();
        }
        int elementSelectJoueur;
        cout << endl;
        this->afficherCartes(*indexCartesJouable);
        cout << endl;
        cout << message << " (entre 1 et " << nbrElementSelect << "): ";
        while (!(cin >> elementSelectJoueur) or elementSelectJoueur<1 or elementSelectJoueur>indexCartesJouable->size()){
            cout << "Saisie incorrecte, recommencez: ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
        clearTerminal();
        return elementSelectJoueur;
    }
};