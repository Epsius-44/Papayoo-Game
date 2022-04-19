class Carte {
private:
    unsigned int identifiant[2];
    unsigned int points;
    TerminalInterface* terminal;
public:
    Carte(unsigned int valeur, unsigned int couleur, unsigned int points, TerminalInterface* terminal){
        this->identifiant[0] = valeur;
        this->identifiant[1] = couleur;
        this->points = points;
        this->terminal = terminal;
    }
    unsigned int getValeur(){
        return this->identifiant[0];
    }

    unsigned int getCouleur(){
        return this->identifiant[1];
    }

    unsigned int getPoints(){
        return this->points;
    }

    void afficherCarte(){
        string couleur[5] = {"trefle", "carreau", "pic", "coeur", "payoo"};
        cout << "Carte : " << this->identifiant[0] << " de " << couleur[this->identifiant[1] - 1] << " avec " << this->points << " point(s)\n";
    }

    void afficherCarteCouleur(bool jouable = true){
        this->terminal->carteCouleurTerminal(this->getCouleur(),jouable);
        cout << " " << this->getValeur() << " ";
        this->terminal->resetCouleurTerminal();
        cout << " ";
    }

    void setPoint(unsigned int points){
        this->points = points;
    }
};