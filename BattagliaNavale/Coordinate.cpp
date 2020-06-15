#include "Coordinate.h"
#include <iostream>
#include <cmath>


// Costruttori
Coordinate::Coordinate()
{

}


Coordinate::Coordinate(int x, int y):_x(x),_y(y)
{

}
// ------- Getters e Setters -------
int Coordinate::getX() const
{
  return _x;
}


int Coordinate::getY() const
{
  return _y;
}


void Coordinate::setX(int x)
{
  _x = x;
}


void Coordinate::setY(int y)
{
  _y = y;
}

// --------------------------

bool Coordinate::getFromPlayer(int N) // include i cin per impostare le coordinate
{
  char k;
  int y;
  bool ok;
  do
  {
    std::cout << "Inserisci x e y (es: A 5):" << '\n';
    std::cin >> k >> y;
    std::cin.ignore(10000,'\n');
    if(std::cin.fail())
    {
      std::cout << "Inserimento non valido, ritenta:\n";
      ok = !std::cin.fail();
      std::cin.clear();
      std::cin.ignore(10000,'\n');
    }else
    {
      _y = y -1;
      _x = ((int)k < 97) ? (int)k -65 : (int)k -97;

      if(_x<0 || _y < 0 ||_x > N-1 || _y > N-1)
      {
        std::cout << "Coordinate fuori range\n";
        ok = false;
      }else
      {
        ok = true;
      }
    }
  }while(!ok);
  return true;
}


void Coordinate::operator=(Coordinate Other) // Operatore di assegnazione
{
  _x = Other.getX();//non sono necessari i get
  _y = Other.getY();
}


Coordinate Coordinate::operator+(Coordinate Other) // Somma di due coordinate
{
  return Coordinate(_x+Other.getX(),_y+Other.getY());
}


int Coordinate::operator-(Coordinate Other) // Distanza verticale o orizzontale tra due coordinate
{
  if (_x == Other.getX())
  {
    return abs(_y - Other.getY())+1;
  }else if (_y==Other.getY())
  {
    return abs(_x - Other.getX())+1;
  }else
  {
    return -1;
  }
}


bool Coordinate::operator==(Coordinate Other) const// Confronto tra due coordinate
{
  if (_x == Other.getX() && _y==Other.getY())
    return true;
  return false;
}


void Coordinate::print()const//stampa le coordinate nel formato scelto
{
  std::cout << "(" << (char)(_x + 65) << ", " << _y+1 << ")";
}


Co Coordinate::getStruct()// Interazione con la struttura Co, inviabile tramite la rete
{
  Co a;
  a._x = _x;
  a._y = _y;
  return a;
}


Coordinate::Coordinate(Co strutt):_x(strutt._x),_y(strutt._y)// Passaggio delle coordinate alla struttura Co
{

}


bool Coordinate::operator!=(Coordinate Other) const // ridefinizione disuguaglianza tra coordinate
{
  return !(*this==Other);
}
