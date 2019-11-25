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

// Nave::Nave(Coordinate begin,Coordinate end) //costruisce una nave riempiendo la matrice _coordinates delle sue coordinate
// {
//   int x1 = begin.getX();
//   int x2 = end.getX();
//   int y1 = begin.getY();
//   int y2 = end.getY();
//   _lunghezza=abs(x1-x2+y1-y2)+1;
//
//   _contatore = _lunghezza;
//
//   _coordinates = new int*[_lunghezza];
//   for (int i = 0 ; i < _lunghezza; i++)
//   {
//     _coordinates[i] = new int[2];
//   }
//   if (x1 == x2) // nave verticale
//   {
//     for (int k = 0 ; k < _lunghezza; k++)
//     {
//       _coordinates[k][0] = x1;
//     }
//     if (y1 < y2)
//     {
//       for (int i = 0; i < _lunghezza ; i++)
//       {
//         _coordinates[i][1] = y1 + i;
//       }
//     }else if(y1 > y2)
//     {
//       for (int i = 0; i < _lunghezza ; i++)
//       {
//         _coordinates[i][1] = y2 + i;
//       }
//     }
//   }else if (y1 == y2) //nave orizzontale
//   {
//     for (int k =0; k < _lunghezza; k++)
//     {
//       _coordinates[k][1] = y1;
//     }
//     if (x1 < x2)
//     {
//       for (int i = 0 ; i < _lunghezza ; i++)
//       {
//         _coordinates[i][0] = x1 + i;
//       }
//     }else if(x1 > x2)
//     {
//       for (int i = 0; i < _lunghezza ; i++)
//       {
//         _coordinates[i][0] = x2 + i;
//       }
//     }
//   }
//
// }



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
        std::cout << "Affondato" << '\n';
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

//
//
// CacciaTorpediniere::CacciaTorpediniere(int x1, int x2, int y1, int y2) : Nave(x1,x2,y1,y2)
// {
//   _contatore = _lunghezza;
//   _coordinates = new int*[_lunghezza];
//   l = _lunghezza;
//   _coordinates[0] = new int[2];
//   _coordinates[1] = new int[2];
// }
// //
// Portaerei::Portaerei(int x1, int x2, int y1, int y2) : Nave(x1,x2,y1,y2)
// {
//   _contatore = _lunghezza;
// }
//
// Incrociatore::Incrociatore(int x1, int x2, int y1, int y2) : Nave(x1,x2,y1,y2)
// {
//   _contatore = _lunghezza;
// }
//
// Corazzata::Corazzata(int x1, int x2, int y1, int y2) : Nave(x1,x2,y1,y2)
// {
//   _contatore = _lunghezza;
// }
