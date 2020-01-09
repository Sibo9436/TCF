#include "Coordinate.h"
#include <iostream>
#include <cmath>

Coordinate::Coordinate()
{

}

Coordinate::Coordinate(int x, int y):_x(x),_y(y)
{

}

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

bool Coordinate::getFromPlayer() // include i cin per impostare le coordinate
{
  char k;
  int y;
  bool ok;
  do
  {
    std::cout << "Inserisci x e y (es A 5):" << '\n';
    std::cin >> k >> y;
    if(std::cin.fail())
    {
      std::cout << "Inserimento non valido\n Ritenta\n";
      ok = !std::cin.fail();
      std::cin.clear();
      std::cin.ignore(10000,'\n');

    }else
    {
      _y = y -1;
      _x = ((int)k < 97) ? (int)k -65 : (int)k -97;

      if((_x<0 || _y < 0 )||(_x >9 || _y > 9))
      {
        std::cout << "Coordinate fuori range \n";

        ok = false;
      }else
      {
        ok = true;
      }
    }
  }while(!ok);
  return true;
}


void Coordinate::operator=(Coordinate Other)
{
  _x = Other._x;
  _y = Other._y;
}

Coordinate Coordinate::operator+(Coordinate Other)
{
  return Coordinate(_x+Other._x,_y+Other._y);
}

void Coordinate::print()const
{
  std::cout << "(" << (char)(_x + 65) << " , " << _y+1 << ")";
}
int Coordinate::operator-(Coordinate Other) //NON SONO SICURO CHE IL MENO SIA IL MIGLIOR OPERATORE POSSIBILE PER STA COSA
{
  if (_x == Other._x)
  {
    return abs(_y - Other._y)+1;
  }else if (_y==Other._y)
  {
    return abs(_x - Other._x)+1;
  }else
  {
    return -1;
  }
}

bool Coordinate::operator==(Coordinate Other) const
{
  if (_x == Other._x && _y==Other._y)
    return true;
  return false;
}

bool Coordinate::operator!=(Coordinate Other) const
{
  if (_x != Other._x || _y!=Other._y)
    return true;
  return false;
}
