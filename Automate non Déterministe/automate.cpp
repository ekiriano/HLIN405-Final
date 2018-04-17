#include "automate.h"

#include <iostream>

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
  //int nbLettresAlphabet = 2;//sizeof(n_alphabet[0])/sizeof(n_alphabet);
  tailleAlphabet = nbLettresAlphabet;
  tailleEnsemleGlobal = nbSalles;
  
  alphabet2=n_alphabet;

  Etat* tab= new Etat[nbSalles];
  ensembleGlobal= tab;
  //string a ="";
  for(int i=0;i<nbSalles;i++){
    //a =  to_string(i);
    //ensembleGlobal[i]= Etat(i);
    ensembleGlobal[i].setEtat(i);
    //cout << ensembleGlobal[i].getEtat() << endl; // affiche la bonne chose 0,1,2...
  }
  alphabet = map< char, int>();
  for(int j=0;j< nbLettresAlphabet;j++){  // creation de l'alphabet ayant comme a ==> 0 etc...
    alphabet[n_alphabet[j]]=j;
  }

  //initialisation ensemble transitions
  ensembleTransitions = new vector<Etat*>**[nbSalles];
  for (int i =0; i <nbSalles;i++){
    ensembleTransitions[i] = new vector<Etat*>*[nbLettresAlphabet];
  }

  for(int i = 0; i<nbSalles;i++){
    for(int j=0; j<nbLettresAlphabet;j++){
      ensembleTransitions[i][j]= new vector<Etat*>(0); // tableau a NULL
    }
  }


  etatInitial = &ensembleGlobal[0];
  etatFinal = &ensembleGlobal[nbSalles-1];
}

/* ----- Fonctions ----- */

vector<Etat*>* Automate::fonctionDeTransition( Etat a , char lettre){
  int t = a.getEtat();int idxlettre = alphabet[lettre];
  return ensembleTransitions[t][idxlettre];
}

vector<Etat*> Automate::unionEtats(vector<Etat*> ensembleDepart, char lettre){
  vector<Etat*> inter; // vecteur a renvoyer contenant l'union
  vector<Etat*>* temp; // variable temp ou l'on stocke
  vector<Etat*> tempderef ;

  for(int i =0 ;i<ensembleDepart.size();i++){ // parcours de l'ensemble des états de l'ensemble de départ
    if(fonctionDeTransition(*ensembleDepart[i],lettre)->size() != 0){ // parcours des transitions existante si la trransition avec la lettre existe
      temp = fonctionDeTransition(*ensembleDepart[i],lettre);
      tempderef = *temp;
      for(int j = 0 ; j<tempderef.size();j++){ // on a joute les elements a inter si existe transition temp est donc une adresse d'un vector
        inter.push_back(tempderef[j]);
      }
    }
  }

  // tout les elements ateignables sont dans inter , supprimons maintenant les éléments en double
  sort( inter.begin(), inter.end() );
  inter.erase(unique(inter.begin(), inter.end()) , inter.end());
  //nous obtenons alors l'ensemble
  return inter;
}


bool Automate::motReconnu(char* mot,int longeurmot){ //O(longeurmot)

  vector<Etat*> actuel(0); actuel.push_back(etatInitial); // set a etat initial;
  vector<Etat*> pourVerif;

  int i =0 ;
  while(i<longeurmot){
    cout << mot[i]<<endl;
    if(longeurmot == 1){
      actuel = unionEtats(actuel,mot[i]);
      for(int k= 0;k<actuel.size();k++){
        if(actuel[k]==etatFinal){
          return true;
        }
      }
      return false;
    }
    if(i==longeurmot-1){ // verification de la dernière transition
      for(int k= 0;k<actuel.size();k++){
        if(actuel[k]==etatFinal){
          return true;
        }
      }
      return false;
    }
    else{
      pourVerif = unionEtats(actuel,mot[i]);
      if(pourVerif.size()!=0){
        actuel = pourVerif;
      }
      else{return false;}}
      i++;
    }
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

void Automate::setTransition(int idxEtat , char lettre , int idxEtatf){
  int idxlettre = alphabet[lettre];
  ensembleTransitions[idxEtat][idxlettre]->push_back(&(ensembleGlobal[idxEtatf]));
}

Etat* Automate::getEnsembleGlobal(){return ensembleGlobal;}

vector<Etat*>*** Automate::getEnsembleTransitions(){return ensembleTransitions;}


void Automate::existechemininter(vector<Etat*> ensembleDepart){
  int tailleAlphabet = sizeof(alphabet2)/sizeof(char);
  vector<Etat*> ensembletemp; vector<Etat*>* pourVerif;
  vector<Etat*> pourVerifderef;
  vector<Etat*> ensembleNonTraverse;

  for(int i=0 ; i<ensembleDepart.size();i++){
    for(int j = 0 ; j<tailleAlphabet;j++){
      pourVerif = fonctionDeTransition(*ensembleDepart[i],alphabet2[j]);
      pourVerifderef = *pourVerif;
      if(pourVerifderef.size() != 0){
        for(int k=0;k<pourVerifderef.size();k++){
          ensembletemp.push_back(pourVerifderef[k]);
        }
      }
    }
    /*######## on supprime les doubles afin d'obtenir l'union ########*/
    sort( ensembletemp.begin(), ensembletemp.end() );
    ensembletemp.erase(unique(ensembletemp.begin(), ensembletemp.end()) , ensembletemp.end());
    for(int x =0 ;x<ensembletemp.size();x++){
      if(ensembletemp[x]==etatFinal){
        ensembletemp[x]->setSalle_Traverse(true);
      }
      else{
        if(ensembletemp[x]->getSalle_Traverse()==false){
          ensembleNonTraverse.push_back(ensembletemp[x]);
          ensembletemp[x]->setSalle_Traverse(true);
        }
      }
    }
    existechemininter(ensembleNonTraverse);
  }
}

bool Automate::existechemin(){
  vector<Etat*> initial(0); initial.push_back(etatInitial);
  existechemininter(initial);
  return etatFinal->getSalle_Traverse();
}

void Automate::resetTraverseeFalse(){ //O(nbetats)
  int tailleEnsembleGlobal = sizeof(ensembleGlobal)/sizeof(Etat*);
  for(int i=0;i<tailleEnsembleGlobal;i++){
    ensembleGlobal[i].setSalle_Traverse(false);
  }
}
