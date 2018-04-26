#include "automate.h"
using namespace std ;

int main(int argc, char const *argv[]) {

cout << "  ---------  automate 1 :  ---------  " << endl;
cout << "   |    a    |   b   | "<<endl <<
        " 0 | {1,2,3} |   {1} | "<<endl <<
        " 1 |   {}    | {1,2} | "<<endl <<
        " 2 |   {3}   |   {3} | "<<endl <<
        " 3 |   {}    |   {}  | "<<endl;

char alphabet1[] = {'a','b'};
Automate automate1(alphabet1 ,4,2);

automate1.setTransition(0,'a',1);automate1.setTransition(0,'a',2);automate1.setTransition(0,'a',3);
automate1.setTransition(0,'b',1);automate1.setTransition(1,'b',1);automate1.setTransition(1,'b',2);
automate1.setTransition(2,'a',3);automate1.setTransition(2,'b',3);

string mot1 = "ab"; string mot2 = "abc";
cout << " le mot ab est il reconnu : " <<automate1.motReconnu(mot1)<<endl;
cout << " le mot abc est il reconnu : " <<automate1.motReconnu(mot2)<<endl;
cout << " existe t'il un chemin ? : " <<automate1.existechemin() << endl;
cout << "son plus petitchemin est alors : " << automate1.pluspetitchemin() << endl;
string motaleat1 = automate1.motAleatoire(3);
cout << "generons aleatoirement le mot suivant : " << motaleat1 << endl;

cout << "  ---------  automate 1 :  ---------  " << endl;
Automate testAleatoire1;
testAleatoire1 = testAleatoire1.generationAleatoire1(10,4.0,alphabet1,2);
cout << " existe t'il un chemin ? : " <<testAleatoire1.existechemin() << endl;
cout << "son plus petitchemin est alors : " << testAleatoire1.pluspetitchemin() << endl;

cout << "  ---------  automate 2 :  ---------  " << endl;
Automate testAleatoire2;
testAleatoire2 = testAleatoire2.generationAleatoire2(10,4.0,alphabet1,2);
cout << " existe t'il un chemin ? : " <<testAleatoire2.existechemin() << endl;
cout << "son plus petitchemin est alors : " << testAleatoire2.pluspetitchemin() << endl;

cout << "  ---------  automate 3 :  ---------  " << endl;
Automate testAleatoire3;
testAleatoire3 = testAleatoire3.generationAleatoire3(10,4.0,alphabet1,2);
cout << " existe t'il un chemin ? : " <<testAleatoire3.existechemin() << endl;
cout << "son plus petitchemin est alors : " << testAleatoire3.pluspetitchemin() << endl;


  return 0;
}
