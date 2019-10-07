#ifndef PUNTO_H
#define PUNTO_H
#include<iostream>
using std::ostream;
using std::istream;
class Punto {
    friend ostream &operator<<(ostream&, const Punto&);
    
    public:
	Punto();
	Punto(float, float,float);
	float getx();
	float gety();
	float getz();
	void setx(float);
	void sety(float);
	void setz(float);
	float dist(Punto);




    private:
	float x, y, z;

};
#endif
