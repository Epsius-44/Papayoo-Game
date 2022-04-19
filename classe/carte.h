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
        int couleur = 0;
        if (this->getCouleur()==1){
            couleur = 2;
        } else if (this->getCouleur()==2){
            couleur = 14;
        } else if (this->getCouleur()==3){
            couleur = 9;
        } else if (this->getCouleur()==4){
            couleur = 12;
        }else{
            couleur = 7;
        }
        if (jouable){
            this->terminal->couleurTerminal(0,couleur);
        }else{
            this->terminal->couleurTerminal(couleur,0);
        }
        cout << " " << this->getValeur() << " ";
        this->terminal->resetCouleurTerminal();
        cout << " ";
    }

    void setPoint(unsigned int points){
        this->points = points;
    }
};