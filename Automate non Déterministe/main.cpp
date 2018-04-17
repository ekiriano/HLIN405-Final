#include "automate.h"
using namespace std ;

int main(int argc, char const *argv[]) {
/* ############# Tests Unitaires #############

Representation de l'automate :
  |    a    |   b
0 | {1,2,3} |   {1}
1 |   {}    |   {1,2}
2 |   {3}   |     {3}
3 |   {}    |   {}

Reconnait les mots : a,aa,aba,ab ...
*/

 char alphabet[2] = {'a','b'};
 Automate test(alphabet ,4,2);

 test.setTransition(0,'a',1);test.setTransition(0,'a',2);test.setTransition(0,'a',3);
 test.setTransition(0,'b',1);test.setTransition(1,'b',1);test.setTransition(1,'b',2);
 test.setTransition(2,'a',3);test.setTransition(2,'b',3);

 Etat* ensembleEtats = test.getEnsembleGlobal();
 //vector<Etat*> testensemble = {&ensembleEtats[0]};
 vector<Etat*> uniondestransitions0a = test.unionEtats(testensemble,'a');

/*
 cout << "affichage de l'union" << endl; // 3
 for(int i=0 ;i<uniondestransitions0a.size();i++){
  cout << uniondestransitions0a[i]->getEtat() << endl;
}
*/


cout << "########## Test des Mots Reconnus ##########" << endl;
cout<< "---------------------------" << endl;
//cout << " aba " <<endl;
char mot1[3]= {'a','b','a'};
cout <<test.motReconnu(mot1,3)<<endl;
cout<< "---------------------------" << endl;
//cout << " a " <<endl;
char mot2[1]= {'b'};
cout << test.motReconnu(mot2,1)<<endl;
cout<< "---------------------------" << endl;

vector<Etat*> initial ; initial.push_back(&ensembleEtats[0]);
cout << test.existechemin()<< endl;

/*
 for(int i= 0; i< 4 ;i++){
   cout << ensembleEtats[i].getEtat();
 }
 */
/*
vector<Etat*>* transition0a = test.fonctionDeTransition(ensembleEtats[0] ,'a');
vector<Etat*> transition0aderef = *transition0a;
cout << "taille du nombre d'etat pour la transition 0a* :"<< transition0a->size()<< endl;
 for(int i=0 ; i<transition0aderef.size();i++){
   cout<<transition0aderef[i]->getEtat() <<endl;
 }*/
  return 0;
}
