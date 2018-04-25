#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "Etat.h"
#include <map>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

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
  std::vector<Etat*>*** ensembleTransitions; //A tableau a deux dimensions de pointeurs de vector contenant des pointeurs d'etats

  int tailleEnsemleGlobal;
  int tailleAlphabet;
public:
/* Constructeurs */
  Automate();
  Automate(char* n_alphabet ,int nbSalles,int nbLettresAlphabet);

  /*Algorithmes générations aléatoire */
  Automate generationAleatoire1(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet);
  Automate generationAleatoire2(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet);
  Automate generationAleatoire3(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet);

  std::string motAleatoire(int longeurmot);

/* Fonctions */
  std::vector<Etat*>* fonctionDeTransition(Etat a,char lettre);
  bool motReconnu(char* mot,int longeurmot);
  std::vector<Etat*> unionEtats(std::vector<Etat*> ensembleDepart, char lettre);

  void existechemininter(std::vector<Etat*> ensembleDepart);
  bool existechemin();

  void pluspetitcheminInter(std::vector<Etat*> depart);
  std::string pluspetitchemin();

/* set & getters */
  std::map< char, int> getAlphabet();
  int getId(char a);
  void setTransition(int etat , char lettre , int etatf);
  Etat* getEnsembleGlobal();
  std::vector<Etat*>*** getEnsembleTransitions();
  void resetTraverseeFalse();


};

#endif
