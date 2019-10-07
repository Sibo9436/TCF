#include<iostream>
#include"punto.h"
#include<cmath>
using std::cout;
using std::cin;
using std::endl;

Punto::Punto(){
    x=0;
    y=0;
    z=0;
}
Punto::Punto(float gx,float gy,float gz):x(gx),y(gy),z(gz){}
float Punto::getx(){
    return x;
}
float Punto::gety(){
    return y;
}
float Punto::getz(){
    return z;
}
void Punto::setx(float gx){
    x=gx;
}
void Punto::sety(float gy){
    y=gy;
}
void Punto::setz(float gz){
    z=gz;
}

float Punto::dist(Punto Other){
    return sqrt(pow(Other.x-x,2)+pow(Other.y-y,2)+pow(Other.z-z,2));
}



ostream &operator<<(ostream &output, const Punto &Other){
    output << "[" << Other.x << ", " << Other.y << ", " << Other.z << "]" << endl;
    return output;
}
