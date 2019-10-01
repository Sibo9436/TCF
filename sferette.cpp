#include <iostream>
#include <cmath>
#include "sfera.h"
using namespace std;
int main(){
    double massaTerra=5.972e24;
    double massaLuna=7.342e22;
    double raggioTerra=6371000;
    double raggioLuna=1737100;
    double distanzaTL=384400000;
    Sfera A(0,0,raggioTerra,massaTerra);
    Sfera B(distanzaTL,0,0,500,raggioLuna,massaLuna);
    Sfera C(distanzaTL,0,1737100,7.342e22);
    Sfera U(raggioTerra + 10, 0,7.07106781187,0, 0.01, 1);
    Sfera sferette[2] = {A,U}; 
    //for (int i = 0; i < 11; i++)
    float contatore = 0;
    float din = sferette[0].dist(sferette[1]);
    float tempo = 1e-6;
    while (not sferette[0].Overlap(sferette[1])){
    	contatore += tempo;
	
	for (int i = 0; i < 2; i++){
//	    cout << "Corpo n: " << i << endl;
	    sferette[i].Update(tempo);
	}
	for (int i = 0; i < 2 ; i++){
	    for (int j = 0; j< 2; j++){
	        if (j != i ) {
		    sferette[i].Forze(sferette[j]);
		}
	    }	
	}
	cout  << sferette[1].getx() - raggioTerra << "  ,   " << sferette[1].gety() << endl;
    }
    cout << endl << contatore << " secondi!" << endl;
    return 0;
}
