using namespace std;

class Carte {
private:
    unsigned int identifiant[2];
    unsigned int points;
public:
    Carte(unsigned int identifiant[2], unsigned int points){
        this->points = points;
        for (int i=0 ; i < 2 ; i++)
        {
            this->identifiant[i] += identifiant[i];
        }
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

    void setPoint(unsigned int points){
        this->points = points;
    }
};