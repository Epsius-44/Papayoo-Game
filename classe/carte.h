class Carte {
private:
    unsigned int identifiant[2]; //valeur et coculeur de la carte
    unsigned int points; //nombre de points rapporté par la carte
    TerminalInterface* terminal; //interaction avec le terminal
public:
    Carte(unsigned int valeur, unsigned int couleur, unsigned int points, TerminalInterface* terminal){  //initialisation de la carte
        this->identifiant[0] = valeur; //valeur de la carte
        this->identifiant[1] = couleur; //couleur de la carte
        this->points = points; //nombre de points de la carte
        this->terminal = terminal; //interaction terminal
    }
    unsigned int getValeur(){  //retourne la valeur de la carte
        return this->identifiant[0];
    }

    unsigned int getCouleur(){   //retourne la couleur de la carte
        return this->identifiant[1];
    }

    unsigned int getPoints(){   //retourne les points de la carte
        return this->points;
    }

    void afficherCarte(){   //affichage de la carte, sa valeur et sa couleur
        string couleur[5] = {"trefle", "carreau", "pic", "coeur", "payoo"};
        cout << "Carte : " << this->identifiant[0] << " de " << couleur[this->identifiant[1] - 1] << " avec " << this->points << " point(s)\n";
    }

    void afficherCarteCouleur(bool jouable = true){ //affiche la carte avec ses couleurs dans le terminal
        this->terminal->carteCouleurTerminal(this->getCouleur(),jouable); //le texte et l'arrière-plan du texte aura la couleur de la carte
        cout << " " << this->getValeur() << " ";//affichage du nombre de la carte
        this->terminal->resetCouleurTerminal(); //couleurs par défaut du terminal
        cout << " "; //ajouter un espace après la carte
    }

    void setPoint(unsigned int points){   //donne les points que vaut la carte a celle-ci
        this->points = points;
    }
};