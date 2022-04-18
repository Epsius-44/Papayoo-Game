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
    unsigned int commencerPli(){
        unsigned int pointsPli=0;
        unsigned int joueurGagnePli = 0;
        for (int j = 0; j < this->joueurs.size(); j++){
            this->affichageCartePli();
            this->ajouterCarteJouer(this->joueurs[(this->getIdJoueurDebute()+j)%this->joueurs.size()]->jouerUneCarte(this->cartesJouer));
        }
        cout << this->joueurs.size() << endl;
        joueurGagnePli=this->trouveGagnantPli();
        pointsPli=this->calculPointPli();
        this->joueurs[joueurGagnePli]->addPoints(pointsPli);
        this->affichageResultatPli();
        return joueurGagnePli;
    }

    void affichageCartePli(){
        for (int carte = 0; carte < this->cartesJouer.size(); carte++){
            cout << endl;
            cout << this->joueurs[(this->getIdJoueurDebute()+carte)%this->joueurs.size()]->getNom() << "à joué la carte ";
            this->cartesJouer[carte]->afficherCarteCouleur();
            cout << endl;
        }
    }
    void affichageResultatPli(){
        unsigned int joueurGagnePli=this->trouveGagnantPli();
        cout << endl;
        cout << endl;
        cout << this->joueurs[joueurGagnePli]->getNom() << " remporte le pli et gagne " << this->calculPointPli() << " points" << endl;
    }
};