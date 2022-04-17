class Humain : public Joueur {
public:
    Humain(string nom) : Joueur(nom) {}

    virtual vector<Carte *> donneTroisCarte() {
        //shuffle(this->cartes.begin(), this->cartes.end(), default_random_engine(666));
        // TODO Remove card
        return vector<Carte *>(this->cartes.begin(), this->cartes.begin());
    }

    virtual Carte *jouerUneCarte(vector<Carte *> carteJouer) {
        unsigned int idCarteChoisi;
        this->afficherCartes();
        cout << "Choisir une carte entre 1 et " << this->cartes.size() << " : ";
        cin >> idCarteChoisi;
        Carte *carteChoisi = this->cartes[idCarteChoisi - 1];
        cout << "Le joueur " << this->getNom() << " joue : ";
        carteChoisi->afficherCarte();
        this->cartes.erase(this->cartes.begin() + idCarteChoisi - 1);
        return carteChoisi;
    }
};