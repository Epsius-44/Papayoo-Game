class Pli {
private:
    unsigned int idJoueurDebute{};
    vector<Carte*> cartesJouer;
    vector<Joueur *> joueurs;
public:
    Pli(vector<Joueur*> &listeJoueurs){
        this->joueurs = listeJoueurs;
    }

    void ajouterCarteJouer(Carte* carte) {
        this->cartesJouer.insert(this->cartesJouer.end(), carte);
        cout << "point: " << carte->getPoints() << "\n";
    }

    unsigned int calculPointPli() {
        unsigned int totalPoint = 0;
        for (int i = 0; i < this->cartesJouer.size(); i++) {
            totalPoint += this->cartesJouer[i]->getPoints();
        }
        return totalPoint;
    }

    unsigned int trouveGagnantPli() {
        unsigned int nombreJoueur = this->cartesJouer.size();
        unsigned int couleurDebut = this->cartesJouer[0]->getCouleur();
        unsigned int idJoueurGagnant = this->idJoueurDebute;
        unsigned int valeurCarteGagnant = this->cartesJouer[0]->getValeur();
        for (int i = 0; i < nombreJoueur; i++) {
            if (this->cartesJouer[i]->getCouleur() == couleurDebut and this->cartesJouer[i]->getValeur() > valeurCarteGagnant){
                idJoueurGagnant = this->idJoueurDebute+i;
                valeurCarteGagnant = this->cartesJouer[i]->getValeur();
            }
        }
        return idJoueurGagnant%nombreJoueur;
    }

    unsigned int getIdJoueurDebute() {
        return this->idJoueurDebute;
    }

    void setIdJoueurDebute(unsigned int id) {
        this->idJoueurDebute = id;
    }

    vector<Carte *> getCarteJoueur() {
        return this->cartesJouer;
    }

    void nouveauPli(unsigned int idJoueurDebute) {
        this->cartesJouer.erase(this->cartesJouer.begin(), this->cartesJouer.end());
        this->setIdJoueurDebute(idJoueurDebute);
    }

    void affichagePapayoo(unsigned int papayoo){
            int couleurs[4] = {2, 14, 9, 12};
            cout << "\nle papayoo est: ";
            couleurTerminal(0, couleurs[papayoo-1]);
            cout << " 7 ";
            resetCouleurTerminal();
            cout << "\n";
    }

    unsigned int commencerPli(unsigned int papayoo){
        unsigned int pointsPli=0;
        unsigned int joueurGagnePli = 0;
        for (int j = 0; j < this->joueurs.size(); j++){
            clearTerminal();
            this->affichagePapayoo(papayoo);
            this->affichageCartePli();
            this->ajouterCarteJouer(this->joueurs[(this->getIdJoueurDebute()+j)%this->joueurs.size()]->jouerUneCarte(this->cartesJouer));
        }
        clearTerminal();
        this->affichageCartePli();
        joueurGagnePli=this->trouveGagnantPli();
        pointsPli=this->calculPointPli();
        this->joueurs[joueurGagnePli]->addPoints(pointsPli);
        this->affichageResultatPli();
        return joueurGagnePli;
    }

    void affichageCartePli(){
        for (int carte = 0; carte < this->cartesJouer.size(); carte++){
            cout << "\n";
            cout << this->joueurs[(this->getIdJoueurDebute()+carte)%this->joueurs.size()]->getNom() << " à joué la carte ";
            this->cartesJouer[carte]->afficherCarteCouleur();
            cout << "\n";
        }
    }
    void affichageResultatPli(){
        unsigned int joueurGagnePli=this->trouveGagnantPli();
        cout << "\n";
        cout << "\n";
        cout << this->joueurs[joueurGagnePli]->getNom() << " remporte le pli et gagne " << this->calculPointPli() << " points \n";
    }
};