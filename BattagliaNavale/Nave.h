#ifndef NAVE_H
#define NAVE_H

class Nave
{
public:
  Nave();
  Nave(int, int, int, int);
  ~Nave();
  bool Hit(int , int );
  void Print();


private:
  int **_coordinates;
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
