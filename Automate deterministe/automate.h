#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "Etat.h"
#include <map>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>

/*
  Automate représenté sous forme de quintuplet
  A = alphabet
  Q = enseble des etats
  D = ensemble etats de dédepart
  F = ensemble des etats etatsFinaux
  T = ensembleDesTransitions

*/

class Automate{
private:
  //quintuplet
  std::map< char, int> alphabet ;
  //char* alphabet; /*A*/
  char* alphabet2;
  Etat* ensembleGlobal; //A
  Etat* etatFinal; //A
  Etat* etatInitial; //A
  Etat*** ensembleTransitions; //A

  int tailleEnsemleGlobal;
  int tailleAlphabet;

public:
/* Constructeurs */
  Automate();
  Automate(char* n_alphabet ,int nbSalles,int nbLettresAlphabet);

/*Algorithmes générations aléatoire */
Automate generationAleatoire1(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet);
Automate generationAleatoire2(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet);
/* Fonctions */
  Etat* fonctionDeTransition( Etat a,char lettre);
  bool motReconnu(char* mot,int longeurmot);

  bool existecheminInter(Etat a);
  bool existechemin();
  bool existeEF(Etat a);

/* set & getters */
  std::map< char, int> getAlphabet();
  int getId(char a);
  void setTransition(int etat , char lettre , int etatf);
  Etat* getEnsembleGlobal();
  Etat*** getEnsembleTransitions();

/* Fonctions a finir */

  //std::string
  void pluspetitcheminInter(std::vector<Etat*> depart);
  std::string pluspetitchemin();


  /*
  void generationAleatoire3(int nbSalles , float densité, char* n_alphabet);*/


};
//Automate generationAleatoire1(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet);

#endif
