#include "iostream" // pour cin / cout
#include "vector" // pour time()
#include "stdlib.h"     /* srand, rand */
#include "cassert"
#include "algorithm"
#include "random"

using namespace std;

#include "classe/carte.h"
#include "classe/joueur.h"
#include "classe/pli.h"
#include "classe/jeu.h"

int main(int argc, char **argv)
{
    Jeu test(1,1);
    test.manche();
    return 0;
}