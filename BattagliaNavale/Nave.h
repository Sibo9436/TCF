#ifndef NAVE_H
#define NAVE_H
#include "Coordinate.h"


class Nave
{
public:
  Nave();
  Nave(Coordinate,Coordinate);
  ~Nave();
  bool Hit(int , int );
  bool Hit(Coordinate);
  void Print();
  int getlunghezza();
  Coordinate operator[](int);

private:
  Coordinate * _coords;
  int _lunghezza;
  int _contatore;
  bool _affondato;
};


#endif
