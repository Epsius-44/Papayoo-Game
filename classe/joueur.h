class Joueur {
private:
    string nom;
protected:
    int unsigned points;
    vector<Carte *> cartes;
public:
    Joueur(string nom) {
        this->nom = nom;
        this->points = 0;
        this->cartes = {};
    }

    void afficherCartes() {
        for (int i = 0; i < this->cartes.size(); ++i) {
            cout << i + 1 << " | ";
            this->cartes[i]->afficherCarte();
        }
    }

    virtual void recoisCartes(vector<Carte *> carteEnPlus) {
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end());
    }

    int unsigned lancerDe() {
        return rand() % 4 + 1;
    }

    virtual vector<Carte *> donneTroisCarte() {
        return {nullptr};
    };

    virtual Carte *jouerUneCarte() {
        return nullptr;
    };

    string getNom() {
        return this->nom;
    }

    int unsigned getPoints() {
        return this->points;
    }

    void addPoints(int unsigned points) {
        this->points += points;
    }

    vector<Carte *> getCartes() {
        return this->cartes;
    }

    void setCartes(vector<Carte *> cartes) {
        this->cartes = cartes;
    }

    vector<int> cartesDispo(int couleurCarteJouer=0) {
        vector<int> indexCartesDispo = {}; //vector avec la liste des index des cartes qui peuvent être joué par le joueur (bot ou humain)
        for (int i = 0; i < this->cartes.size(); i++) { //boucle pour chaque carte présente dans le jeu du joueur
            if (couleurCarteJouer == 0 or this->cartes[i]->getCouleur()==couleurCarteJouer) { //si aucune carte n'a été joué ou que la couleur de la carte correspond à la première carte joué pour le pli
                indexCartesDispo.push_back(i); //ajouter index de la carte à la liste des cartes disponibles
            }
        }
        if (indexCartesDispo.size()==0){ //si le jeu du joueur ne contient aucune carte avec la même couleur que la première carte joué pour le pli
            for (int i = 0; i < this->cartes.size(); i++) {
                    indexCartesDispo.push_back(i); //ajout de chaque carte du joueur dans la liste des cartes dispo
            }
        }
        return indexCartesDispo; //renvoi de la liste des index correspondant aux cartes que le joueur peut jouer
    }
};

class Humain : public Joueur {
public:
    Humain(string nom) : Joueur(nom) {}

    virtual vector<Carte *> donneTroisCarte() {
        //shuffle(this->cartes.begin(), this->cartes.end(), default_random_engine(666));
        // TODO Remove card
        return vector<Carte *>(this->cartes.begin(), this->cartes.begin());
    }

    virtual Carte *jouerUneCarte() {
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

class Bot : public Joueur {
private:
    unsigned int nombreCartesCouleur[5] = {0,0,0,0,0}; //nombre de cartes par couleur
    unsigned int sommeCartesCouleur[5] = {0,0,0,0,0}; //somme des valeurs des cartes par couleur
    float valeurCartesCouleur[5] = {0,0,0,0,0}; //calcul pour savoir quelle couleur il faut éliminer en premier ou donner
    int couleurDe = 0; //couleur du dé
public:
    Bot(string nom) : Joueur(nom) {}

    void setCouleurDe(int couleurDe){ //définition de la couleur du dé
        this->couleurDe = couleurDe;
    };

    void calculValeurCartes(){ //calcul de la valeur d'une couleur
        for (int i=0;i<5;i++){ //pour chaque couleur
            if (this->couleurDe==i+1){ //couleur correspondante au dé
                this->valeurCartesCouleur[i] = round(this->sommeCartesCouleur[i]/ this->nombreCartesCouleur[i] * (1+(float(this->nombreCartesCouleur[i]+2)/10))*10)/10; // =x/y*((1.x)+0.2) | x→ nombre de cartes d'une couleur    y→ somme des valeurs des cartes d'une couleur | arrondi au dixième près
            } else if (this->couleurDe!=4) { //couleur ne correspondant pas au payoo
                this->valeurCartesCouleur[i] = round((this->sommeCartesCouleur[i]/ this->nombreCartesCouleur[i] * (1+(float(this->nombreCartesCouleur[i])/10)))*10)/10; // =x/y*(1.x) | x→ nombre de cartes d'une couleur    y→ somme des valeurs des cartes d'une couleur |arrondi au dixième près
            } else{ //couleur correspondante au payoo
                this->valeurCartesCouleur[i] = round((this->sommeCartesCouleur[i]/ this->nombreCartesCouleur[i] * (1+(float(this->nombreCartesCouleur[i])/10)))*5)/10; // =(x/y*(1.x))/2 | x→ nombre de cartes d'une couleur    y→ somme des valeurs des cartes d'une couleur |arrondi au dixième près

            }
        }
    }

    virtual void recoisCartes(vector<Carte *> carteEnPlus) {
        unsigned int couleurCarte = 0;
        this->cartes.insert(this->cartes.end(), carteEnPlus.begin(), carteEnPlus.end()); //insertion des cartes dans la liste des cartes du joueur
        for (int i=0;i<carteEnPlus.size();i++){ //boucle pour chaque carte reçue par le joueur
            couleurCarte=carteEnPlus[i]->getCouleur()-1; //couleur de la carte
            this->nombreCartesCouleur[couleurCarte]+=1; //ajoute +1 aux nombres de carte de cette couleur
            this->sommeCartesCouleur[couleurCarte]+=carteEnPlus[i]->getValeur(); //ajoute la valeur de cette carte à la somme de cette couleur
        }
        this->calculValeurCartes(); //calcul score par couleur
    }

    virtual vector<Carte *> donneTroisCarte() {
        vector<Carte*> carteDonne; //vector avec les cartes qui seront données
        for (int i=0;i<3;i++){//boucle pour sélectionner 3 cartes
            int couleurCarteDonne = 0; //couleur de la carte qui sera données
            int carteIndexSelect = -1; //position de la carte dans la liste des cartes du joueur
            vector<int> couleursPossible = this->couleursAvecLePlusDeValeurs(); //liste des couleurs avec le plus de valeurs
            srand (time(NULL));
            couleurCarteDonne = couleursPossible[rand() % couleursPossible.size()]; //choisis une couleur au hasard parmi la liste des couleurs possibles
            for (int indexCarte = 0; indexCarte < this->cartes.size(); indexCarte++){
                if (this->cartes[indexCarte]->getCouleur()==couleurCarteDonne and (carteIndexSelect== -1 or this->cartes[indexCarte]->getValeur()) > this->cartes[carteIndexSelect]->getValeur()){
                    carteIndexSelect = indexCarte; //sélectionne la carte avec la plus grande valeur et de la même couleur que la couleur sélectionner
                }
            }
            carteDonne.push_back(this->cartes[carteIndexSelect]); //ajoute la carte à la liste des cartes données
            nombreCartesCouleur[couleurCarteDonne-1]-=1; //ajoute -1 au nombre de cartes de la couleur de la carte données
            sommeCartesCouleur[couleurCarteDonne-1]-=this->cartes[carteIndexSelect]->getValeur(); //enlève la valeur de la carte donnée au nombre de points des cartes de la couleur de la carte données
            this->cartes.erase(this->cartes.begin()+carteIndexSelect); //supprime la carte donnée de la liste des cartes du joueur
            this->calculValeurCartes(); //recalcule la valeur des couleurs des cartes du joueur
        }
        return carteDonne;
    }

    vector<int> couleursAvecLePlusDeValeurs(){
        float valeurCarteCouleurSelect = 0; //valeur de la plus grosse valeur
        vector<int> couleurPossible; //liste des couleurs possible avec les plus grosses valeurs
        for (int couleur=0;couleur<5;couleur++){ //récupère la plus grande valeur de couleurs dans le jeu du joueur
            if (this->valeurCartesCouleur[couleur]>valeurCarteCouleurSelect){
                valeurCarteCouleurSelect = this->valeurCartesCouleur[couleur];
            }
        }
        for (int couleur=0;couleur<5;couleur++){ //ajoute toutes les couleurs qui ont la plus grande valeur de couleurs
            if (this->valeurCartesCouleur[couleur]==valeurCarteCouleurSelect){
                couleurPossible.push_back(couleur+1);
            }
        }
        return couleurPossible;
    }

    virtual Carte *jouerUneCarte() { //TODO
        return this->cartes[rand() % this->cartes.size()];
    }
};