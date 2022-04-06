using namespace std;

class Joueur{
private:
    string nom;
protected:
    int unsigned points;
    vector<Carte*> cartes;
public:
    Joueur(string nom){
        this->nom = nom;
        this->points = 0;
        this->cartes = {};
    }

    void afficherCartes(){
        for (int i = 0; i < this->cartes.size() ; ++i) {
            cout << i + 1 << " | ";
            this->cartes[i]->afficherCarte();
        }
    }

    void recoisCartes(vector<Carte*> carteEnPlus){
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());
    }
    int unsigned lancerDe(){
        return rand() % 4 + 1;
    }

    virtual vector<Carte*> donneTroisCarte(){
        return {nullptr};
    };
    virtual Carte* jouerUneCarte(){
        return nullptr;
    };

    string getNom(){
        return this->nom;
    }
    int unsigned getPoints(){
        return this->points;
    }
    void setPoints(int unsigned points){
        this->points = points;
    }
    vector<Carte*> getCartes(){
        return this->cartes;
    }
    void setCartes(vector<Carte*> cartes){
        this->cartes = cartes;
    }
};

class Humain : public Joueur{
public:
    Humain(string nom) : Joueur(nom) {}
    virtual vector<Carte*> donneTroisCarte(){
        shuffle(this->cartes.begin(), this->cartes.end(), default_random_engine(666));
        return vector<Carte*>(this->cartes.begin(), this->cartes.begin()+2);
    }
    virtual Carte* jouerUneCarte(){
        unsigned int idCarteChoisi;
        this->afficherCartes();
        cout << "Choisir une carte entre 1 et " << this->cartes.size() << " : ";
        cin >> idCarteChoisi;
        Carte* carteChoisi = this->cartes[idCarteChoisi - 1];
        cout << "Le joueur " << this->getNom() << "joue : ";
        carteChoisi->afficherCarte();
        this->cartes.erase(this->cartes.begin() + idCarteChoisi);
        return carteChoisi;
    }
};

class Bot : public Joueur{
public:
    Bot(string nom) : Joueur(nom) {}
    virtual vector<Carte*> donneTroisCarte(){
        shuffle(this->cartes.begin(), this->cartes.end(), default_random_engine(666));
        return vector<Carte*>(this->cartes.begin(), this->cartes.begin()+2);
    }
    virtual Carte* jouerUneCarte(){
        return this->cartes[rand() % this->cartes.size()];
    }
};