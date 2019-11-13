#include "Nave.h"
#include <iostream>
#include<cmath>
Nave::Nave()
{

}

Nave::~Nave()
{

}

Nave::Nave(int x1, int y1, int x2, int y2):_lunghezza(abs(x1-x2+y1-y2)+1) //costruisce una nave riempiendo la matrice _coordinates delle sue coordinate
{

  _contatore = _lunghezza;

  _coordinates = new int*[_lunghezza];
  for (int i = 0 ; i < _lunghezza; i++)
  {
    _coordinates[i] = new int[2];
  }
  if (x1 == x2) // nave verticale
  {
    for (int k = 0 ; k < _lunghezza; k++)
    {
      _coordinates[k][0] = x1;
    }
    if (y1 < y2)
    {
      for (int i = 0; i < _lunghezza ; i++)
      {
        _coordinates[i][1] = y1 + i;
      }
    }else if(y1 > y2)
    {
      for (int i = 0; i < _lunghezza ; i++)
      {
        _coordinates[i][1] = y2 + i;
      }
    }
  }else if (y1 == y2) //nave orizzontale
  {
    for (int k =0; k < _lunghezza; k++)
    {
      _coordinates[k][1] = y1;
    }
    if (x1 < x2)
    {
      for (int i = 0 ; i < _lunghezza ; i++)
      {
        _coordinates[i][0] = x1 + i;
      }
    }else if(x1 > x2)
    {
      for (int i = 0; i < _lunghezza ; i++)
      {
        _coordinates[i][0] = x2 + i;
      }
    }
  }

}



bool  Nave::Hit(int x, int y)
{
  for (int i = 0 ; i < _lunghezza; i++)
  {
    if (x == _coordinates[i][0]&&y == _coordinates[i][1])
    {
      std::cout << "OPLITO" << '\n';
      std::cout << _contatore << '\n';
      _contatore--;
      std::cout << _contatore << '\n';
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
    std::cout << _coordinates[i][0] << " " << _coordinates[i][1] << "\n";
  }
  std::cout << _lunghezza << '\n';

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
