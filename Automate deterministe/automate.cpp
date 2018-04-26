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
    etatAleat1=rand()%nbSalles; //cout <<"etatAleat1 : " << etatAleat1 << endl;
    etatAleat2=rand()%nbSalles; //cout <<"etatAleat2 : " << etatAleat2 << endl;

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

    if(etatAleat1!=etatAleat2){

      if(etatAleat1<etatAleat2 && retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre])==NULL){
        if(etatAleat2!=0 && etatAleat1!=nbSalles-1){
          retour.setTransition(etatAleat1,n_alphabet[indiceLettre],etatAleat2);
          nbTransitionsSortantes--;
        }
      }

      if(etatAleat2>etatAleat1 && retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat2],n_alphabet[indiceLettre])==NULL){
        if(etatAleat2!=(nbSalles-1) && etatAleat1!=0){
          retour.setTransition(etatAleat2,n_alphabet[indiceLettre],etatAleat1);
          nbTransitionsEntrantes--;
        }
      }

    }
  }
  return retour;
}

Automate Automate::generationAleatoire3(int nbSalles , float densite, char* n_alphabet ,int nbLettresAlphabet){ // a ameliorer
  Automate retour(n_alphabet,nbSalles,nbLettresAlphabet);
  // densité = nbcouloirs/nbsalles => nbcouloirs = nbsalles * densité
  int nbTransitions = nbSalles*densite;
  int etatAleat1 , etatAleat2; int indiceLettre;
  Etat* ensembleGlobalRetour = retour.getEnsembleGlobal();
  srand(time(NULL));

  while(nbTransitions!= 0){
    indiceLettre=rand()%nbLettresAlphabet;
    etatAleat1=rand()%nbSalles; //cout <<"etatAleat1 : " << etatAleat1 << endl;
    etatAleat2=rand()%nbSalles; //cout <<"etatAleat2 : " << etatAleat2 << endl;
    if(nbTransitions == 1){
      if(retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre])==NULL && etatAleat2!=0 && etatAleat1!=nbSalles-1 && (etatAleat1!=etatAleat2)){
        retour.setTransition(etatAleat1,n_alphabet[indiceLettre],nbSalles-1);
        nbTransitions--;
      }
    }
    else{
      if(retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre])==NULL && etatAleat2!=0 && etatAleat1!=nbSalles-1 && (etatAleat1!=etatAleat2)){
        retour.setTransition(etatAleat1,n_alphabet[indiceLettre],etatAleat2);
        nbTransitions--;
      }
    }
  }

  return retour;
}

string Automate::motAleatoire(int longeurmot){
  srand(time(NULL));
  string mot = "";
  int nb;
  while(mot.size()<=longeurmot){
    nb = rand()%tailleAlphabet;
    mot.append(1,alphabet2[nb]);
  }
  return mot;
}

/* ----- Fonctions ----- */

Etat* Automate::fonctionDeTransition( Etat a , char lettre){
  int t = a.getEtat();int idxlettre = alphabet[lettre];
  return ensembleTransitions[t][idxlettre];
}

bool Automate::motReconnu(string mot){ //O(longeurmot) char* mot,int longeurmot
  Etat* actuel = etatInitial;
  int longeurmot = mot.size();
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


  if(existechemin()){
    this->pluspetitcheminInter(initial);
    /*
    for(int i =0 ; i < tailleEnsemleGlobal;i++){
      cout << ensembleGlobal[i].getEtat() << " a pour pere : " ;
      if(ensembleGlobal[i].getPere() != NULL){
        cout << ensembleGlobal[i].getPere()->getEtat()<<endl;
      }
      else{
        cout << "Pas de pere" << endl;
      }
    }
    */
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

void Automate::afficherAutomate(){

  ofstream monFlux("AfficherAutomate.tex",ios::trunc);

  if(monFlux){

    monFlux << "\\documentclass[12pt]{article}" << endl;
    monFlux << "\\usepackage[english]{babel}" << endl;
    monFlux << "\\usepackage[utf8x]{inputenc}" << endl;
    monFlux << "\\usepackage{amsmath}" << endl;
    monFlux << "\\usepackage{tikz}" << endl;
    monFlux << "\\usetikzlibrary{arrows,automata}" << endl;
    monFlux << "\\begin{document}" << endl;
    monFlux << "\\begin{tikzpicture}[->,>=stealth',shorten >=1pt,auto,node distance=4cm, scale = 1.1,transform shape]" << endl;

    string T[3]={"below right","below left","below"};
    if(tailleEnsemleGlobal <= 10){
      // faut parcourir l'ensemble des etats initiaux
      monFlux << "\\node[state,initial] ("<<etatInitial->getEtat()<<")   {$1$};" << endl;
      // le reste des etats
      int j = 2; int m = 0;
      for(int i = 1; i < (tailleEnsemleGlobal-1); i++){
        if(m < 2){
          if(i%2 != 0){
          monFlux << "\\node[state]  ("<<ensembleGlobal[i].getEtat()<<") ["<<T[m]<<" of = "<<ensembleGlobal[i].getEtat()-1 <<"] {$"<<j<<"$};" << endl;
          j++;
          m++; }
         else{ monFlux << "\\node[state]  ("<<ensembleGlobal[i].getEtat()<<") ["<<T[m]<<" of = "<<ensembleGlobal[i].getEtat()-2 <<"] {$"<<j<<"$};" << endl;
        j++; m++;  } }
        else {monFlux << "\\node[state]  ("<<ensembleGlobal[i].getEtat()<<") ["<<T[m]<<" of = "<<ensembleGlobal[i].getEtat()-2 <<"] {$"<<j<<"$};" << endl;
       j++;}

            // if {monFlux << "\\node[state]  ("<<ensembleGlobal[i].getEtat()<<") ["<<T[m]<<" of = "<<ensembleGlobal[i].getEtat()-2 <<"] {$"<<j<<"$};" << endl;
            // j++; }
      }

      monFlux <<"\\node[state,accepting] ("<<etatFinal->getEtat()<<") [below right of = "<<ensembleGlobal[tailleEnsemleGlobal-2].getEtat()<<"] {$"<<tailleEnsemleGlobal<<"$};" << endl;


      // faut parcourir l'ensemble des etats finaux.
      int supercool = 0;
      // faire les transitions.
      for(int k = 0; k < tailleEnsemleGlobal; k++){ //Parcourir l'ensemble des transitions.
        for(int j=0 ; j < tailleAlphabet;j++){
          if(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]) != NULL && supercool==0){
            monFlux <<"\\path ("<<ensembleGlobal[k].getEtat()<< ") edge node {$" <<alphabet2[j]<<"$}("<<fonctionDeTransition(ensembleGlobal[k],alphabet2[j])->getEtat()<<")" << endl;
            supercool++;
          }
          else if(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]) != NULL && supercool!=0){
            monFlux <<"   ("<<ensembleGlobal[k].getEtat()<< ") edge [bend left] node {$" <<alphabet2[j]<<"$}("<<fonctionDeTransition(ensembleGlobal[k],alphabet2[j])->getEtat()<<")" << endl;

          }

        }
      }
      monFlux << ";" << endl;
      monFlux << "\\end{tikzpicture}" << endl;
      monFlux << "\\end{document}" << endl;
      monFlux.close();
      system("pdflatex AfficherAutomate.tex");
    }
  else {
    monFlux << "le nombre de salles doit etre inferieur à 10" << endl;
    monFlux.close();}

  }
  else { cout << "ERREUR: Impossible d'ouvrir le fichier." << endl; }
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
