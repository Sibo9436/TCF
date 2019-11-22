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
<<<<<<< HEAD
  Coordinate operator[](int i);

=======
  Coordinate operator[](int);
  
>>>>>>> b3436ff8a04ecaf8727678c3a37439e257c10d89
private:
  Coordinate * _coords;
  int _lunghezza;
  int _contatore;
  bool _affondato;
};

// class CacciaTorpediniere : public Nave
// {
// public:
//   CacciaTorpediniere(int,int,int,int);
// private:
//   const int _lunghezza = 2;
//
// };
//
//
// class Corazzata : public Nave
// {
// public:
//   Corazzata(int,int,int,int);
// private:
//   const int _lunghezza = 4;
//
// };
//
//
// class Incrociatore : public Nave
// {
// public:
//   Incrociatore(int,int,int,int);
// private:
//   const int _lunghezza = 3;
//
// };
//
//
// class Portaerei : public Nave
// {
// public:
//   Portaerei(int,int,int,int);
// private:
//   const int _lunghezza = 5;
//
// };

#endif
