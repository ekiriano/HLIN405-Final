#include "automate.h"
#include "Etat.h"
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Execution"<< endl;
  bool fin = false;
  int question;

while (fin != true) {
  cout << "Veuillez entrer le numero de la question , Entrez 0 pour quitter"<<endl;
  cin >> question;
  switch (question) {
    case 0 :
    fin = true;
    break;

    // Premières trois questions
    case 1:
    {
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
    }
    continue;

    case 2 :
    {
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
    }
     continue;


    case 3 :
    {
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

      automate3.afficherAutomate();
      string mot3 ="ad"; string mot4="abc"; string mot5 ="abb";
      cout << " le mot ad est il reconnu : " <<automate3.motReconnu(mot3)<<endl;
      cout << " le mot abc est il reconnu : " <<automate3.motReconnu(mot4)<<endl;
      cout << " le mot abb est il reconnu : " <<automate3.motReconnu(mot5)<<endl;
      cout << " existe t'il un chemin ? : " <<automate3.existechemin() << endl;
      cout << "son plus petitchemin est alors : " << automate3.pluspetitchemin() << endl;
    }
    continue;

    // 3 dernières questions

    case 4:
    {
      cout << "    ---------- generationAleatoire1 ----------     " << endl << endl;
      char alphabet1[]={'a','b'};
      Automate testGenAleat1;
      testGenAleat1= testGenAleat1.generationAleatoire1(10,1.8,alphabet1,2);
      testGenAleat1.afficherAutomate();
      cout << " existe t'il un chemin ? : " <<testGenAleat1.existechemin() << endl;
      cout << "son plus petitchemin est alors : " << testGenAleat1.pluspetitchemin() << endl;
    }
    continue;

    case 5:
    {
      cout << "    ---------- generationAleatoire2 ----------     " << endl<< endl;
      char alphabet1[]={'a','b'};
      Automate testGenAleat2;
      testGenAleat2= testGenAleat2.generationAleatoire2(10,2,alphabet1,2);
      testGenAleat2.afficherAutomate();
      cout << " existe t'il un chemin ? : " <<testGenAleat2.existechemin() << endl;
      cout << "son plus petitchemin est alors : " << testGenAleat2.pluspetitchemin() << endl;
    }

    continue;

    case 6:
    {
      cout << "    ---------- generationAleatoire3 ----------     " << endl <<endl;
      char alphabet1[]={'a','b'};
      Automate testGenAleat3;
      testGenAleat3= testGenAleat3.generationAleatoire3(10,1.8,alphabet1,2);
      testGenAleat3.afficherAutomate();
      cout << " existe t'il un chemin ? : " <<testGenAleat3.existechemin() << endl;
      cout << "son plus petitchemin est alors : " << testGenAleat3.pluspetitchemin() << endl;
    }

    continue;

  }
}
  return 0;
}
