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

/* Generations Aleatoires */

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

    vector<Etat*> transition = *retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre]);

    if(etatAleat2!=0 && etatAleat1!=nbSalles-1 && (etatAleat1!=etatAleat2) && !estDansTransition(transition,&ensembleGlobalRetour[etatAleat2])) {
      cout<< "teeest" << endl;
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

  vector<Etat*> transition;
  while(nbTransitionsSortantes!= 0 && nbTransitionsEntrantes!=0){
    indiceLettre=rand()%nbLettresAlphabet;
    etatAleat1=rand()%nbSalles;
    etatAleat2=rand()%nbSalles;

    if(etatAleat1!=etatAleat2){

      if(etatAleat1<etatAleat2){
         transition = *retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre]);
        if(etatAleat2!=0 && etatAleat1!=nbSalles-1 && !estDansTransition(transition,&ensembleGlobalRetour[etatAleat2]) ){
          retour.setTransition(etatAleat1,n_alphabet[indiceLettre],etatAleat2);
          nbTransitionsSortantes--;
        }
      }

      if(etatAleat2>etatAleat1){
        transition = *retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat2],n_alphabet[indiceLettre]);
        if(etatAleat2!=(nbSalles-1) && etatAleat1!=0 && !estDansTransition(transition,&ensembleGlobalRetour[etatAleat1])){
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

    vector<Etat*> transition = *retour.fonctionDeTransition(ensembleGlobalRetour[etatAleat1],n_alphabet[indiceLettre]);

    if(nbTransitions == 1){
      if(etatAleat1!=nbSalles-1 && !estDansTransition(transition,&ensembleGlobalRetour[etatAleat2])){
        retour.setTransition(etatAleat1,n_alphabet[indiceLettre],nbSalles-1);
        nbTransitions--;
      }
    }
    else{
      if(etatAleat2!=0 && etatAleat1!=nbSalles-1 && (etatAleat1!=etatAleat2) && !estDansTransition(transition,&ensembleGlobalRetour[etatAleat2])){
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
  while(mot.size()<longeurmot){
    nb = rand()%tailleAlphabet;
    mot.append(1,alphabet2[nb]);
  }
  return mot;
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

bool Automate::motReconnu(string mot){ //O(longeurmot)

  vector<Etat*> actuel(0); actuel.push_back(etatInitial); // set a etat initial;
  vector<Etat*> pourVerif;

  int i =0 ;
  int longeurmot = mot.size();
  while(i<longeurmot){
    //cout << mot[i]<<endl;
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
    return false;
}

void Automate::pluspetitcheminInter(vector<Etat*> depart){
  string petitchemin ="";
  vector<Etat*> etats;
  vector<Etat*> temp;
  vector<Etat*> transitionTemp;


  if(etatFinal->getPere()== NULL){
    for(int j =0 ;j<depart.size();j++){
      for(int i =0 ; i<tailleAlphabet;i++){

        if(fonctionDeTransition(*depart[j],alphabet2[i])->size() !=0){
          transitionTemp = *fonctionDeTransition(*depart[j],alphabet2[i]);
          for(int k= 0 ;k< transitionTemp.size();k++){
            if(transitionTemp[k]->getPere()==NULL){
              transitionTemp[k]->setPere(depart[j]);
            }
            temp.push_back(transitionTemp[k]);
          }
        }
      }
    }
    //elimination des doublons
    sort( temp.begin(), temp.end() );
    temp.erase(unique(temp.begin(), temp.end()) , temp.end());
    pluspetitcheminInter(temp);
  }
}

string Automate::pluspetitchemin(){
  string petitchemin ="";
  vector<Etat*> initial;initial.push_back(etatInitial);
  vector<Etat*> ensPar;


    //cout << " bloque ? " << endl;
  if(existechemin()){
    this->pluspetitcheminInter(initial);
    Etat* temp = etatFinal;
    while(etatInitial!=temp){
      for(int i =0 ; i<tailleEnsemleGlobal ;i++){
        for(int j =0 ; j< tailleAlphabet;j++){
          if(fonctionDeTransition(ensembleGlobal[i],alphabet2[j])->size()!= 0){
            ensPar = *fonctionDeTransition(ensembleGlobal[i],alphabet2[j]);

            for(int k =0;k<ensPar.size();k++){
              if(ensPar[k]== temp && (&ensembleGlobal[i]==temp->getPere())){
                petitchemin.push_back(alphabet2[j]);
                temp = &ensembleGlobal[i];
              }
            }
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
    monFlux << "\\begin{tikzpicture}[->,>=stealth',shorten >=0.5pt,auto,node distance=3cm, scale = 1,transform shape]" << endl;

    string T[3]={"below right","below left","below"};
    if(sizeof(ensembleGlobal)<= 10){
      // faut parcourir l'ensemble des etats initiaux
      monFlux << "\\node[state,initial] ("<<etatInitial->getEtat()<<")   {$1$};" << endl;
      // le reste des etats
      int j = 2; int m = 0;
      for(int i = 1; i < tailleEnsemleGlobal-1; i++){
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

      monFlux <<"\\node[state,accepting] ("<<etatFinal->getEtat()<<") [below right of = "<<ensembleGlobal[tailleEnsemleGlobal-2].getEtat()<<"] {$"<< tailleEnsemleGlobal<<"$};" << endl;


      // faut parcourir l'ensemble des etats finaux.
      int supercool = 0;
      // faire les transitions.
      for(int k = 0; k < tailleEnsemleGlobal; k++){ //Parcourir l'ensemble des transitions.
        for(int j=0 ; j < tailleAlphabet;j++){
          if(fonctionDeTransition(ensembleGlobal[k],alphabet2[j])->size() != 0 ){
            for(unsigned int i=0; i< fonctionDeTransition(ensembleGlobal[k],alphabet2[j])->size(); i++){

              if(supercool == 0){
                monFlux <<"\\path ("<<ensembleGlobal[k].getEtat()<< ") edge [bend right] node {$" <<alphabet2[j]<<"$}("<<(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]))->at(i)->getEtat()<<")" << endl;
                supercool++;

            }
          else { monFlux <<"   ("<<ensembleGlobal[k].getEtat()<< ") edge [bend left] node {$" <<alphabet2[j]<<"$}("<<(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]))->at(i)->getEtat()<<")" << endl; i++;}
        }
          // else if(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]) != NULL){
          //   for(unsigned int i=0; i<(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]))->size(); i++){
          //   monFlux <<"   ("<<ensembleGlobal[k].getEtat()<< ") edge [bend left] node {$" <<alphabet2[j]<<"$}("<<(fonctionDeTransition(ensembleGlobal[k],alphabet2[j]))->at(i)->getEtat()<<")" << endl;

        }}}



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

bool Automate::estDansTransition(vector<Etat*> transition , Etat* eval){
  for (int i = 0; i < transition.size(); i++) {
    if(transition[i]==eval){
      return true;
    }
  }
  return false;

}
