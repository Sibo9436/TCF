#include <iostream>
#include "array.h"
using std::cout;
using std::cin;
using std::endl;

int main(){
    Array A(7);
    Array B;
    cout << "Dimensione di A= " << A.getSize() << "\n bulabula " << A << endl;
    cout << "Dimensione di B= "  << B.getSize() << "\n bulabula " << B << endl;
    cout << "Dammi 17 interi! ";
    cin >> A >> B;
    cout << "Dopo l'input: " << A << endl << B << endl;
    cout << "Sono uguali?" << endl;
    if (A != B ) {
	cout << "manco pe ril ca***" << endl;
    }
    Array C(A);
    cout << "Dimensione di C= " << C.getSize() << "\nbulabula " <<  C << endl;
    cout << "Mo assegno A=B" << endl;
    A = B;
    cout << A << B;
    cout << " A==B?" << endl;
    if (A == B) cout << "Daje!" << endl;
    cout << "A[5]= " << A[5] << endl;
    cout << " Mo' lo cambio" << endl;
    A[5]=1999;
    cout << A << endl;
    cout << "Provo ad assegnare out of range" << endl;
    A[15] = 10;
    return 0;
}
