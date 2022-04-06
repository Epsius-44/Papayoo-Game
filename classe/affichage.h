class affichage{
private:
    string couleurCarte[5] = {"trefle", "carreau", "pic", "coeur", "payoo"};
public:
    void afficheCarteJoueur(vector<Carte*> cartes){
        for (int i = 0; i < cartes.size() ; ++i) {
            cout << i + 1 << " | ";
            cartes[i]->afficherCarte();
        }
        cout << "Choisir une carte entre 1 et " << cartes.size() << " : ";
    }
};