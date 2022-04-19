class Pli {
private:
    unsigned int idJoueurDebute; //numéro de l'index du joueur qui commence dans la liste des joueurs
    vector<Carte*> cartesJouer; //liste des cartes jouées pendant le pli
    vector<Joueur *> joueurs; //liste des joueurs
    TerminalInterface* terminal; //interaction avec le terminal
public:
    Pli(vector<Joueur*> &listeJoueurs, TerminalInterface* terminal){ //constructeur, prend en paramètre la liste des joueurs et le terminal
        this->joueurs = listeJoueurs;
        this->terminal=terminal;
    }

    unsigned int getIdJoueurDebute() { //index du joueur qui commence dans la liste des joueurs
        return this->idJoueurDebute;
    }

    void setIdJoueurDebute(unsigned int id) { //modifie le numéro du joueur qui commence
        this->idJoueurDebute = id;
    }

    void ajouterCarteJouer(Carte* carte) { //ajoute une carte à la liste des cartes jouées pendant le pli et la met en dernière position
        this->cartesJouer.insert(this->cartesJouer.end(), carte);
    }

    unsigned int calculPointPli() { //calcul le nombre de points dans le pli
        unsigned int totalPoint = 0;
        for (int i = 0; i < this->cartesJouer.size(); i++) { //pour chaque carte jouée dans le pli
            totalPoint += this->cartesJouer[i]->getPoints(); //ajouter à total point le nombre de point que vaut la carte
        }
        return totalPoint; //retourne le nombre de points obtenu
    }

    unsigned int trouveGagnantPli() { //trouve le gagnant du pli
        unsigned int nombreJoueur = this->cartesJouer.size();
        unsigned int couleurDebut = this->cartesJouer[0]->getCouleur(); //couleur de la première carte jouée dans le pli
        unsigned int idJoueurGagnant = this->idJoueurDebute; //par défaut le joueur qui a commencé est le gagnant du pli
        unsigned int valeurCarteGagnant = this->cartesJouer[0]->getValeur(); //valeur de la première carte jouée dans le pli
        for (int i = 0; i < this->cartesJouer.size(); i++) { //pour chaque carte posée dans l'ordre du tour
            if (this->cartesJouer[i]->getCouleur() == couleurDebut and this->cartesJouer[i]->getValeur() > valeurCarteGagnant){ //vérifier si la carte est de la même couleur que la première carte posée et si sa valeur est supérieur à la carte avec la plus grande valeur trouvée
                idJoueurGagnant = this->idJoueurDebute+i; //joueur qui a posé la carte avec le plus de valeur (peut dépasser le nombres de joueurs)
                valeurCarteGagnant = this->cartesJouer[i]->getValeur(); //nouvelle carte avec plus de valeur que la précédente
            }
        }
        return idJoueurGagnant%nombreJoueur; //remet le numéro du joueur par rapport aux nombres de joueurs total (ex: si idJoueurGagnant = 5 | nombreJoueur = 4 → retourne 5%4=1)
    }

    void nouveauPli(unsigned int idJoueurDebute) { //initialisation d'un nouveau pli
        this->cartesJouer.erase(this->cartesJouer.begin(), this->cartesJouer.end()); //supprime les cartes jouer précédemment
        this->setIdJoueurDebute(idJoueurDebute); //modifie le numéro de l'index du joueur qui commence
    }

    unsigned int commencerPli(unsigned int papayoo, unsigned int indexJoueurDebute){ //commencer un pli
        this->nouveauPli(indexJoueurDebute); //initialisation d'un pli
        unsigned int pointsPli=0; //points gagnés dans le pli
        unsigned int joueurGagnePli = 0; //joueur qui gagne le pli
        for (int j = 0; j < this->joueurs.size(); j++){ //pour chaque joueur
            this->terminal->clearTerminal(); //effacer le terminal
            this->affichagePapayoo(papayoo); //afficher le papayoo
            this->affichageCartePli(); //afficher les cartes jouer dans le pli
            this->ajouterCarteJouer(this->joueurs[(this->getIdJoueurDebute()+j)%this->joueurs.size()]->jouerUneCarte(this->cartesJouer)); //demander la carte que souhaite jouer le joueur à qui c'est le tour et l'ajouter à la liste des cartes jouée
        }
        this->terminal->clearTerminal();//effacer le terminal
        this->affichageCartePli();//afficher les cartes jouer dans le pli
        joueurGagnePli=this->trouveGagnantPli();//afficher le gagnant du pli
        pointsPli=this->calculPointPli();//calculer le nombre de points gagner par le joueur qui a gagné le pli
        this->joueurs[joueurGagnePli]->addPoints(pointsPli); //ajouter les points gagnés au joueur qui a gagné le pli
        this->affichageResultatPli(); //afficher le gagnant et le nombre de points gagné dans le pli
        return joueurGagnePli; //retourner le numéro de l'index du gagnant dans la liste des joueurs
    }

    void affichagePapayoo(unsigned int papayoo){ //affiche la carte sélectionnée en tant que papayoo
        int couleurs[4] = {2, 14, 9, 12}; //liste des couleurs dans le terminal par rapport à la couleur des cartes
        cout << "\nle papayoo est: ";
        this->terminal->carteCouleurTerminal(papayoo);//change la couleur de ce qui va être affiché dans le terminal par la couleur de la carte du papayoo
        cout << " 7 "; //affiche le 7 désigné comme le papayoo
        this->terminal->resetCouleurTerminal(); //remet à 0 la couleur de ce qui va être affiché dans le terminal
        cout << "\n"; //reviens à la ligne
    }

    void affichageCartePli(){//afficher les cartes jouées dans le pli
        for (int carte = 0; carte < this->cartesJouer.size(); carte++){ //pour chaque carte jouée
            cout << "\n" <<this->joueurs[(this->getIdJoueurDebute()+carte)%this->joueurs.size()]->getNom() << " à joué la carte "; //afficher le nom du joueur
            this->cartesJouer[carte]->afficherCarteCouleur();//afficher la carte jouée par le joueur
            cout << "\n";//retour à la ligne dans le terminal
        }
    }
    void affichageResultatPli(){//afficher le gagnant du pli et son nombre de points
        unsigned int joueurGagnePli=this->trouveGagnantPli();
        cout << "\n\n"<< this->joueurs[joueurGagnePli]->getNom() << " remporte le pli et gagne " << this->calculPointPli() << " points \n";
    }
};