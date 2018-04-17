#include "automate.h"
#include <iostream>
#include <fstream>


using namespace std;

/* ----- Constructeurs ----- */

Automate::Automate(){
  //alphabet = NULL;
  alphabet2=NULL;
  ensembleGlobal = NULL;
  etatFinal = NULL;
  etatInitial =NULL;
  ensembleTransitions =NULL;
};

Automate::Automate(char* n_alphabet ,int nbSalles ,int nbLettresAlphabet){
  tailleAlphabet = nbLettresAlphabet;
  tailleEnsemleGlobal = nbSalles;

  alphabet2=n_alphabet;

  Etat* tab= new Etat[nbSalles];
  ensembleGlobal= tab;
  for(int i=0;i<nbSalles;i++){
    ensembleGlobal[i].setEtat(i);
  }
  alphabet = map< char, int>();
  for(int j=0;j< nbLettresAlphabet;j++){  // creation de l'alphabet ayant comme a ==> 0 etc...
    alphabet[n_alphabet[j]]=j;
  }


  ensembleTransitions = new Etat**[nbSalles];
  for (int i =0; i <nbSalles;i++){
    ensembleTransitions[i] = new Etat*[nbLettresAlphabet];
  }

  for(int i = 0; i<nbSalles;i++){
    for(int j=0; j<nbLettresAlphabet;j++){
      ensembleTransitions[i][j]= NULL;
    }
  }
  etatInitial = &ensembleGlobal[0];
  etatFinal = &ensembleGlobal[nbSalles-1];
}

/* ------ Generation aléatoire -----------*/
Automate Automate::generationAleatoire1(int nbSalles , float densite, char* n_alphabet ,int nbLettresAlphabet){
  Automate retour(n_alphabet,nbSalles,nbLettresAlphabet);
  // densité = nbcouloirs/nbsalles => nbcouloirs = nbsalles * densité
  int nbTransitions = nbSalles*densite;
  int etatAleat1 , etatAleat2; int indiceLettre;
  Etat* ensembleGlobalRetour = retour.getEnsembleGlobal();
  srand(time(NULL));
  while(nbTransitions!= 0){
    indiceLettre=rand()%nbLettresAlphabet;
    etatAleat1=rand()%nbSalles; cout <<"etatAleat1 : " << etatAleat1 << endl;
    etatAleat2=rand()%nbSalles; cout <<"etatAleat2 : " << etatAleat2 << endl;

    if(retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre])==NULL && etatAleat2!=0 && etatAleat1!=nbSalles-1 && (etatAleat1!=etatAleat2)){
      retour.setTransition(etatAleat1,n_alphabet[indiceLettre],etatAleat2);
      nbTransitions--;
    }
  }
  return retour;
}

Automate Automate::generationAleatoire2(int nbSalles , float densite, char* n_alphabet,int nbLettresAlphabet){
  Automate retour(n_alphabet,nbSalles,nbLettresAlphabet);
  // densité = nbcouloirs/nbsalles => nbcouloirs = nbsalles * densité
  int nbTransitions = nbSalles*densite;
  int nbTransitionsSortantes, nbTransitionsEntrantes;
  nbTransitionsSortantes = nbTransitions/2;
  nbTransitionsEntrantes= nbTransitions-nbTransitionsSortantes;
  Etat* ensembleGlobalRetour = retour.getEnsembleGlobal();
  int etatAleat1 , etatAleat2; int indiceLettre;
  srand(time(NULL));
  while(nbTransitionsSortantes!= 0 && nbTransitionsEntrantes!=0){
    indiceLettre=rand()%nbLettresAlphabet;
    etatAleat1=rand()%nbSalles;
    etatAleat2=rand()%nbSalles;

    if(retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre])==NULL && (etatAleat1!=etatAleat2)){
      if(etatAleat1>etatAleat2 && etatAleat1!=nbSalles-1 )
      retour.setTransition(etatAleat1,n_alphabet[indiceLettre],etatAleat2);
      nbTransitionsSortantes--;

      if(etatAleat2>etatAleat1 && etatAleat2!=nbSalles-1 )
      retour.setTransition(etatAleat2,n_alphabet[indiceLettre],etatAleat1);
      nbTransitionsEntrantes--;
    }
  }
  return retour;
}


/* ----- Fonctions ----- */

Etat* Automate::fonctionDeTransition( Etat a , char lettre){
  int t = a.getEtat();int idxlettre = alphabet[lettre];
  return ensembleTransitions[t][idxlettre];
}

bool Automate::motReconnu(char* mot,int longeurmot){ //O(longeurmot)
  Etat* actuel = etatInitial;

  for(int i = 0 ;i<longeurmot;i++){

    Etat actuelderef = *actuel;

    Etat* pourVerif = fonctionDeTransition(actuelderef,mot[i]);

    if(i == longeurmot-1){
        if(pourVerif==etatFinal){
          return true;}
        else{return false;}}
    else{
       pourVerif = fonctionDeTransition(actuelderef,mot[i]);
       if(pourVerif != NULL){

        actuel = pourVerif;

      }
      else{return false;}}
  }
  return false;
}

bool Automate::existecheminInter(Etat d){
  int j=0;
  if(existeEF(d)==false){
    Etat* T[tailleAlphabet];
    for(int i=0;i<tailleAlphabet;i++){
      T[i]=fonctionDeTransition(d,alphabet2[i]);
    }
    while(j<2 && (etatFinal->getSalle_Traverse()==false)){
      if(T[j]!=NULL){

	if(T[j]==etatFinal){
	  etatFinal->setSalle_Traverse(true);
	}
	if(T[j]->getSalle_Traverse()==false){
	  T[j]->setSalle_Traverse(true);
	  existecheminInter(*T[j]);
	}
      }
      j++;
    }
  }

  if(etatFinal->getSalle_Traverse())
    return true;

  else
    return false;
}

bool Automate::existechemin(){
  bool res;
  res=existecheminInter(*etatInitial);
  if(res)
    return true;
  else
    return false;
}

bool Automate::existeEF(Etat a){
  bool res=false;
  int i=0;
  while((i<tailleAlphabet) && !res){
    if(etatFinal==fonctionDeTransition(a,alphabet2[i])){
      etatFinal->setSalle_Traverse(true);
      res=true;
    }
    i++;
  }
  return res;
}

void Automate::pluspetitcheminInter(vector<Etat*> depart){
  string petitchemin ="";
  vector<Etat*> etats;

  int k;
  if(etatFinal->getPere()== NULL){
    k =0;
    for(int j =0 ;j<depart.size();j++){
      for(int i =0 ; i<tailleAlphabet;i++){
        //cout << j << "   " << i << endl;

        if(fonctionDeTransition(*depart[j],alphabet2[i]) !=NULL){
          etats.push_back(fonctionDeTransition(*depart[j],alphabet2[i]));
          if(etats[k]!= NULL && etats[k]->getPere()==NULL){
            etats[k]->setPere(depart[j]);
          }
          k++;
        }
      }
    }
    pluspetitcheminInter(etats);
  }
}

string Automate::pluspetitchemin(){
  string petitchemin ="";
  vector<Etat*> initial;initial.push_back(etatInitial);



    cout << " bloque ? " << endl;
  if(existechemin()){
    this->pluspetitcheminInter(initial);
    for(int i =0 ; i < tailleEnsemleGlobal;i++){
      cout << ensembleGlobal[i].getEtat() << " a pour pere : " ;
      if(ensembleGlobal[i].getPere() != NULL){
        cout << ensembleGlobal[i].getPere()->getEtat()<<endl;
      }
      else{
        cout << "Pas de pere" << endl;
      }
    }
    Etat* temp = etatFinal;
    while(etatInitial!=temp){
      for(int i =0 ; i<tailleEnsemleGlobal ;i++){
        for(int j =0 ; j< tailleAlphabet;j++){
          if(fonctionDeTransition(ensembleGlobal[i],alphabet2[j]) == temp && (&ensembleGlobal[i]==temp->getPere())){
            petitchemin.push_back(alphabet2[j]);
            temp = &ensembleGlobal[i];
          }
        }
      }
    }
    reverse(petitchemin.begin(),petitchemin.end());// reverse petit chemin avant de renvoyer
  }

  return petitchemin;

}

/* ----- set & getters -----*/
std::map< char, int> Automate::getAlphabet(){return alphabet;}

int Automate::getId(char a){return alphabet[a];}

void Automate::setTransition(int idxEtat , char lettre , int idxEtatf){ // pb ici ?
  int idxlettre = alphabet[lettre];
  ensembleTransitions[idxEtat][idxlettre] = &(ensembleGlobal[idxEtatf]);
}

Etat* Automate::getEnsembleGlobal(){return ensembleGlobal;}

Etat*** Automate::getEnsembleTransitions(){return ensembleTransitions;}

/* ##########" Fonctions Hors- Methodes ###############*/
/*Automate generationAleatoire1(int nbSalles , float densite, char* n_alphabet ,int nbLettresAlphabet){
 Automate retour(n_alphabet,nbSalles,nbLettresAlphabet);
 // densité = nbcouloirs/nbsalles => nbcouloirs = nbsalles * densité
 int nbTransitions = nbSalles*densite;
 int etatAleat1 , etatAleat2; int indiceLettre;
 Etat* ensembleGlobalRetour = retour.getEnsembleGlobal();
cout<< "nombre transition origine : " << nbTransitions << endl;
 while(nbTransitions!= 0){
   cout<< "nombre transition restantes : " << nbTransitions << endl;
   indiceLettre=rand()%nbLettresAlphabet;
   etatAleat1=rand()%nbSalles;
   etatAleat2=rand()%nbSalles;

   if(retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre])==NULL){
     retour.setTransition(etatAleat1,n_alphabet[indiceLettre],etatAleat2);
     nbTransitions--;
   }
 }
 return retour;
}*/
