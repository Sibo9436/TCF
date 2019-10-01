#include <iostream>
#include <cmath>
#include "sfera.h"
using namespace std;

Sfera::Sfera(const double posx, const double posy, const double radius,const double
massa):xo(posx),yo(posy),r(radius),m(massa),x(posx),y(posy){};

Sfera::Sfera(const double posx, const double posy, const double velx, const double vely, const
double radius,const double
massa):xo(posx),yo(posy),vx(velx),vy(vely),r(radius),m(massa),x(posx),y(posy){};

Sfera::~Sfera(){ }

double Sfera::getx(){return x;}
double Sfera::gety(){return y;}
double Sfera::getr(){return r;}
double Sfera::getm(){return m;}
double Sfera::dist(Sfera Other){
    double distx =x-Other.getx();
    double disty = y -Other.gety();
    double dist = sqrt(pow(distx,2)+pow(disty,2));
    return dist;
}

bool Sfera::Overlap(Sfera Other){
/*    double distx =x-Other.getx();
    double disty = y -Other.gety();
    double dist = sqrt(pow(distx,2)+pow(disty,2));
*/
    double dista = dist(Other);
    if (dista > r+Other.getr()) return false;
    else cout << "Overlap";
    return true;
}
void Sfera::Forze(Sfera Other){
    if (not Overlap(Other)){
	double distx = Other.getx() - x ;
	double disty = Other.gety() - y ;
	double dist = sqrt(pow(distx,2)+pow(disty,2));
	double forza = G*m*Other.getm()/pow(dist,2);
	double sint = distx/dist;
	double cost = disty/dist;
	double fx = forza*sint;
	double fy = forza*cost;
	ax += fx/m;
	ay += fy/m;
    }else{
	ax = 0;
	ay = 0;
	vx = 0;
	vy = 0;
    }
}
    
void Sfera::Update(float t){
    vx += ax*t;
    vy += ay*t;
    x += vx*t;
    y += vy*t;
    
    
    
    
    
    /*
    vx += ax;
    vy += ay;
    x += vx;
    y += vy;
    
    cout << "x: "<< x << endl << " y: " << y << endl;
    cout << "vx: "<<vx << endl << " vy: " << vy << endl;
    cout << "ax: "<<ax << endl << " ay: " << ay << endl;
    */
}
