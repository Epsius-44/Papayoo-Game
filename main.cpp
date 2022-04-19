#include "iostream" // pour cin / cout
#include "vector" // pour time()
#include "stdlib.h"     // srand, rand
#include "cmath" //round
#include "cassert"
#include "algorithm"
#include "random"
#include "windows.h"

using namespace std;

#include "classe/terminalInterface.h"
#include "classe/carte.h"
#include "classe/joueur.h"
#include "classe/humain.h"
#include "classe/bot.h"
#include "classe/pli.h"
#include "classe/jeu.h"


int main(int argc, char **argv)
{
    Jeu test;
    test.manche();
    return 0;
}