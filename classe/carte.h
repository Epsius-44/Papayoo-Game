class Carte {
private:
    unsigned int identifiant[2];
    unsigned int points;
public:
    unsigned int getValeur(){
        return this->identifiant[0];
    }

    unsigned int getCouleur(){
        return this->identifiant[1];
    }

    unsigned int getPoint(){
        return this->points;
    }

    void setPoint(unsigned int points){
        this->points = points;
    }
};