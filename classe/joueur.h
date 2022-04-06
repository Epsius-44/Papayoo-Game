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

    void recoisCartes(vector<Carte*> carteEnPlus){
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());
    }
    int unsigned lancerDe(){
        return rand() % 5 + 1;
    }

    //virtual Carte*[3] donneTroisCarte(){};
    //virtual Carte* jouerUneCarte(){}

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
    //virtual Carte*[3] donneTroisCarte(){}
    //virtual Carte* jouerUneCarte(){}
};

class Bot : public Joueur{
public:
    //virtual Carte*[3] donneTroisCarte(){}
    //virtual Carte* jouerUneCarte(){}
};