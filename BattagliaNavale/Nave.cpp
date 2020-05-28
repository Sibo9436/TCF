#include "Nave.h"
#include <iostream>
#include<cmath>
#include "Coordinate.h"


Nave::Nave()
{

}


Nave::~Nave()
{

}


Nave::Nave(Coordinate begin, Coordinate end) //Crea le coordinate di una nave date le coordinate della poppa e della prua
{
  _lunghezza = begin - end;
  _contatore = _lunghezza;
  _coords = new Coordinate[_lunghezza];
  if (begin.getX()==end.getX())
  {
    for (int i =0; i < _lunghezza; i++)
    {
      _coords[i] =(begin.getY() < end.getY())? begin + Coordinate(0, i): end + Coordinate(0,i);
    }
  }else if (begin.getY() == end.getY())
  {
    for (int i =0; i < _lunghezza; i++)
    {
      _coords[i] = (begin.getX() < end.getX())? begin + Coordinate(i,0):end +Coordinate(i,0);
    }
  }
}


bool  Nave::Hit(Coordinate A) //Verifica se una nave è stata colpita e, in tal caso, chiede se è stata affondata
{
  for (int i = 0 ; i < _lunghezza; i++)
  {
    if (A  == _coords[i])
    {
      _contatore--;
      if (_contatore==0)
      {
        _affondato = true;
        return true;
      }
    }
  }

  return false;
}

void Nave::Print()
{
  for (int i = 0; i < _lunghezza; i++)
  {
    _coords[i].print();
  }
  std::cout << _lunghezza << '\n';
}

int Nave::getlunghezza()
{
  return _lunghezza;
}

Coordinate Nave::operator[](int i)
{
  return _coords[i];
}
