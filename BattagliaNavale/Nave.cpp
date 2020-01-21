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


Nave::Nave(Coordinate begin, Coordinate end)
{
  _lunghezza = begin - end;
  _contatore = _lunghezza;
  _coords = new Coordinate[_lunghezza];
  if (begin.getX()==end.getX())
  {
    for (int i =0; i < _lunghezza; i++)
    {
      _coords[i] =(begin.getY() < end.getY())? begin + Coordinate(0, i): end + Coordinate(0,i);//L'ERRORE STA IN MIN(penso)!! NON DIMENTICARLOOOOOO MI SA CHE DEVI METTERE I
    }
  }else if (begin.getY() == end.getY())
  {
    for (int i =0; i < _lunghezza; i++)
    {
      _coords[i] = (begin.getX() < end.getX())? begin + Coordinate(i,0):end +Coordinate(i,0);//L'ERRORE STA IN MIN(penso)!! NON DIMENTICARLOOOOOO MI SA CHE DEVI METTERE I
    }
  }
}


bool  Nave::Hit(Coordinate A)
{
  for (int i = 0 ; i < _lunghezza; i++)
  {
    if (A  == _coords[i])
    {
       //std::cout << _contatore << '\n';
      _contatore--;
       //std::cout << _contatore << '\n';
      if (_contatore==0)
      {
        _affondato = true;
        // std::cout << "Affondato!" << '\n';
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
