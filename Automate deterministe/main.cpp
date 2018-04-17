#include "automate.h"
#include "Etat.h"
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Execution"<< endl;
cout << "---------------- test1-------------------" << endl;
/*
      0 1
    / a b
    0 1 *      // reconnait le mot ab
    1 * 2
    2 * *
*/
 char tab[]={'a','b','c'};
 Automate a(tab,6,3);

 a.setTransition(0,'a',1);
 a.setTransition(0,'b',2);
 a.setTransition(0,'c',3);

 a.setTransition(1,'a',2);
 a.setTransition(1,'c',4);

 a.setTransition(2,'a',5);

 a.setTransition(3,'b',2);
 a.setTransition(3,'a',4);

 a.setTransition(4,'a',5);

/*
a.setTransition(0,'a',1);
a.setTransition(0,'b',2);
a.setTransition(1,'a',3);
a.setTransition(2,'a',4);
a.setTransition(3,'a',4);
a.setTransition(4,'c',5);
*/


//Etat* tabEnsemble =a.getEnsembleGlobal();
//a.pluspetitcheminInter(&tabEnsemble[0]);
cout << "##############################" << endl;
 cout << a.pluspetitchemin() << endl;


 Automate bal;
 bal=bal.generationAleatoire1(10,2,tab,3);

 Etat* balGlob = bal.getEnsembleGlobal();
 for (int i=0;i<10;i++){
   cout << balGlob[i].getEtat() << endl;
 }
 for(int i =0;i<10;i++){
   for(int j=0;j<3;j++){
     cout << balGlob[i].getEtat()<<"  " ;
     if(bal.fonctionDeTransition(balGlob[i],tab[j])!=NULL){
       cout << tab[j]<<"  " << bal.fonctionDeTransition(balGlob[i],tab[j])->getEtat() << endl;
     }
     else{
       cout << "pas transition" << endl;
     }
   }
 }
 cout << bal.existechemin() << endl;
 cout << bal.pluspetitchemin() << endl;



cout << "---------------- test2-------------------" << endl;
 /*
       0 1 2 3
     / a b c d
     0 1 * * *     // reconnait le mot ad , aba , abc , aca
     1 * 2 2 3      aca : 0a1c2a3
     2 3 * 3 *
     3 * * * *
 */
/*
char alphabet1[]={'a','b','c','d'};

Automate test(alphabet1,4,4);

cout << "Affichage indice lette alphabet" << endl;
cout << test.getId('a') << endl;
cout << test.getId('b') << endl;
cout << test.getId('c') << endl;// pb indice mauvais
cout << test.getId('d') << endl; // pb indice mauvais

 // indices c et d a 0 pourquoi ?
test.setTransition(0,'a',1);
test.setTransition(1,'b',2);
test.setTransition(1,'c',2);
test.setTransition(1,'d',3);
test.setTransition(2,'a',3);
test.setTransition(2,'c',3);

char mot1[] = {'a','d'}; char mot2[] = {'a','b','c'}; char mot3[] =  {'a','b','b'};
cout << "------- Mot 1 ------" << endl;
//cout <<test.motReconnu(mot1,2)<<endl; // vrai

cout << "------- Mot 2 ------" << endl;
//cout <<test.motReconnu(mot2,3)<<endl; // vrai

cout << "------- Mot 3 ------" << endl;
//cout <<test.motReconnu(mot3,3)<<endl; // faux? // pourquoi et ou est l'erreur;*/
  return 0;
}
