class TerminalInterface {
private:
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE); //gestion du terminal
    const int couleurCarte[5] = {2, 14, 9, 12,7};
public:
    void couleurTerminal(int textColor, int backgroundColor) {
        /*couleur: 0: noir
        1: bleu foncé
        2: vert
        3: bleu-gris
        4: marron
        5: pourpre
        6: kaki
        7: gris clair
        8: gris
        9: bleu
        10: vert fluo
        11: turquoise
        12: rouge
        13: rose fluo
        14: jaune fluo
        15: blanc*/
        SetConsoleTextAttribute(H, backgroundColor * 16 + textColor); //modifier la couleur du fond et du texte du texte qui va être affiché dans la console
    }

    void carteCouleurTerminal(unsigned int couleurCarteAfficher, bool jouable=true){ //affichage des couleurs pour les cartes
        if (jouable){
            this->couleurTerminal(0,this->couleurCarte[couleurCarteAfficher-1]); //si la carte peut être jouée / sélectionné
        }else{
            this->couleurTerminal(this->couleurCarte[couleurCarteAfficher-1],0); //si la carte ne peut pas être jouée / sélectionné
        }
    }

    void resetCouleurTerminal() {
        couleurTerminal(15, 0); //couleur d'arrière-plan du texte noir et couleur du texte blanc
    }

    void clearTerminal() {
        system("cls"); //effacer le terminal
    }

    void attendre() { //attendre que l'utilisateur appuie sur entrée
        cin.clear(); //effacer ce que contient l'entrée
        cin.sync();
        cout << "Appuyez sur entrée pour continuer..."; //message afficher à l'attention de l'utilisateur
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //attendre jusqu'à ce qu'entrée soit appuyé
    }
};