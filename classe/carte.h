using namespace std;

class Carte {
private:
    unsigned int identifiant[2];
    unsigned int points;
public:
    Carte(unsigned int valeur, unsigned int couleur, unsigned int points){
        this->identifiant[0] = valeur;
        this->identifiant[1] = couleur;
        this->points = points;
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
        string couleur[5] = {"trèfle", "carreau", "pic", "coeur", "payoo"};
        cout << "Carte : " << this->identifiant[0] << " de " << couleur[this->identifiant[1]] << " avec " << this->points << " points " << endl;
    }

    void setPoint(unsigned int points){
        this->points = points;
    }
};