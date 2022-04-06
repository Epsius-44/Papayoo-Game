using namespace std;

class Pli {
private:
    unsigned int idJoueurDebute;
    vector<Carte*> cartesJouer = {};

public:
    void ajouterCarteJouer(Carte *carte) {
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
        for (int i = 1; i < nombreJoueur; i++) {
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
};