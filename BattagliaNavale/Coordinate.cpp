#include "Coordinate.h"
#include <iostream>


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

bool Coordinate::getfromPlayer() // include i cin per impostare le coordinate
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
      _y = y--;
      _x = ((int)k < 97) ? (int)k -65 : (int)k -97;

      if((x<0 || y < 0 )||(x >9 || y > 9))
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


Coordinate &Coordinate::operator=(Coordinate &Other)
{
  _x = Other._x;
  _y = Other._y;
  return *this;
}

Coordinate Coordinate::operator+(Coordinate Other)
{
  return Coordinate(_x+Other._x,_y+Other._y);
}

void Coordinate::print()const
{
  std::cout << "(" << (char)(_x + 65) << " , " << _y << ")";
}
