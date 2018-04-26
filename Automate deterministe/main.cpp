#include "automate.h"
#include "Etat.h"
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Execution"<< endl;


cout << "  ---------  automate 1 :  ---------  " << endl;
cout << "       0 1  "<<endl <<
        "    /  a b  "<<endl <<
        "    0  1 *  "<<endl <<
        "    1  * 2  "<<endl <<
        "    2  * *  "<<endl;

char alphabet1[]={'a','b'};
Automate automate1(alphabet1,3,2);
automate1.setTransition(0,'a',1);
automate1.setTransition(1,'b',2);
automate1.afficherAutomate();
string mot1 = "ab"; string mot2 = "abc";
cout << " le mot ab est il reconnu : " <<automate1.motReconnu(mot1)<<endl;
cout << " le mot abc est il reconnu : " <<automate1.motReconnu(mot2)<<endl;
cout << " existe t'il un chemin ? : " <<automate1.existechemin() << endl;
cout << "son plus petitchemin est alors : " << automate1.pluspetitchemin() << endl;
string motaleat1 = automate1.motAleatoire(3);
cout << "generons aleatoirement le mot suivant : " << motaleat1 << endl;


cout << "  ---------  automate 2 :  ---------  " << endl;
cout << "       0  1  2  "<<endl <<
        "    /  a  b  c  "<<endl <<
        "    0  1  2  3  "<<endl <<
        "    1  2  *  4  "<<endl <<
        "    2  5  *  *  "<<endl <<
        "    3  4  2  *  "<<endl <<
        "    4  5  *  *  "<<endl <<
        "    5  *  *  *  "<<endl;

 char alphabtet2[]={'a','b','c'};
 Automate automate2(alphabtet2,6,3);

 automate2.setTransition(0,'a',1);
 automate2.setTransition(0,'b',2);
 automate2.setTransition(0,'c',3);

 automate2.setTransition(1,'a',2);
 automate2.setTransition(1,'c',4);

 automate2.setTransition(2,'a',5);

 automate2.setTransition(3,'b',2);
 automate2.setTransition(3,'a',4);

 automate2.setTransition(4,'a',5);

 automate2.afficherAutomate();
 string motaleat2 = automate2.motAleatoire(4);

 cout << "generons aleatoirement le mot suivant : " << motaleat2 << endl;
 cout << " le mot genere est il reconnu ?  : " <<automate2.motReconnu(motaleat2)<<endl;
 cout << " existe t'il un chemin ? : " <<automate2.existechemin() << endl;
 cout << "si oui ,son plus petitchemin est alors : " << automate2.pluspetitchemin() << endl;

cout << "  ---------  automate 3 :  ---------  " << endl;
cout << "       0  1  2  3  "<<endl <<
        "    /  a  b  c  d   "<<endl <<
        "    0  1  *  *  *   "<<endl <<
        "    1  *  2  2  3   "<<endl <<
        "    2  3  *  3  *   "<<endl <<
        "    3  *  *  *  *   "<<endl ;


char alphabet3[]={'a','b','c','d'};
Automate automate3(alphabet3,4,4);

automate3.setTransition(0,'a',1);
automate3.setTransition(1,'b',2);
automate3.setTransition(1,'c',2);
automate3.setTransition(1,'d',3);
automate3.setTransition(2,'a',3);
automate3.setTransition(2,'c',3);

string mot3 ="ad"; string mot4="abc"; string mot5 ="abb";
cout << " le mot ad est il reconnu : " <<automate3.motReconnu(mot3)<<endl;
cout << " le mot abc est il reconnu : " <<automate3.motReconnu(mot4)<<endl;
cout << " le mot abb est il reconnu : " <<automate3.motReconnu(mot5)<<endl;
cout << " existe t'il un chemin ? : " <<automate3.existechemin() << endl;
cout << "son plus petitchemin est alors : " << automate3.pluspetitchemin() << endl;


cout << "testons les algorithmes de génération aléatoires :" << endl;
Automate testGenAleat;
int rep=1;
while (rep!=0) {
  cout << "0 : quitter"<< endl;
  cout << "1 : genAleat1"<< endl;
  cout << "2 : genAleat2"<< endl;
  cout << "3 : genAleat3"<< endl;
  cin>> rep;
  switch (rep) {
    case 1:
  }
}


cout << "##############################" << endl;
 cout << a.pluspetitchemin() << endl;


 Automate bal;
 bal=bal.generationAleatoire3(10,2,tab,3);

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

  return 0;
}
