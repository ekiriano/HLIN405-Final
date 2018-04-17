#include "Etat.h"
using namespace std;

Etat::Etat(int etat):etat(etat),salle_traverse(false),pere(NULL){};

Etat::Etat():etat(0),salle_traverse(false),pere(NULL){};

void Etat::setEtat(int a){
  this->etat = a;
}

int Etat::getEtat(){
  return etat;
}

void Etat::setSalle_Traverse(bool b){
  this->salle_traverse=b;
}

bool Etat::getSalle_Traverse(){
  return salle_traverse;
}

void Etat::setPere(Etat* n_pere){
  this->pere = n_pere;
}
Etat* Etat::getPere(){
  return pere;
}
