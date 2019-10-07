#include<iostream>
#include"punto.h"
using namespace std;
int main(){
    Punto A(1,2,3);
    Punto B(10,20,30);
    cout << A << B << endl;
    cout << A.dist(B) << endl;
    return 0;
}

