#ifndef ETAT_H
#define ETAT_H

//class Transition;
#include <iostream>
#include <string>
//#include "transition.h"



class Etat{
private:
  int etat;
  bool salle_traverse;
  Etat* pere;
public:
  Etat();
  Etat(int nom);

  void setEtat(int a);
  int getEtat();

  void setSalle_Traverse(bool b);
  bool getSalle_Traverse();

  void setPere(Etat* n_pere);
  Etat* getPere();
};

#endif
