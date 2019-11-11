#include "Nave.h"
#include <iostream>

Nave::Nave()
{

}

Nave::~Nave()
{

}

Nave::Nave(const int l, int x1, int y1, int x2, int y2):_lunghezza(l),_contatore(l)
{

  if (x1 == x2)
  {
    for (int k = 0 ; k < l; k++)
    {
      _coordinates[k][0] = x1;
    }
    if (y1 < y2)
    {
      for (int i = 0; i < l ; i++)
      {
        _coordinates[i][1] = y1 + i;
      }
    }else if(y1 > y2)
    {
      for (int i = 0; i < l ; i++)
      {
        _coordinates[i][1] = y2 + i;
      }
    }
  }else if (y1 == y2)
  {
    for (int k =0; k < l; k++)
    {
      _coordinates[k][1] = y1;
    }
    if (x1 < x2)
    {
      for (int i = 0 ; i < l ; i++)
      {
        _coordinates[i][0] = x1 + i;
      }
    }else if(x1 > x2)
    {
      for (int i = 0; i < l ; i++)
      {
        _coordinates[i][0] = x2 + i;
      }
    }
  }

}



void Nave::Hit(int x, int y)
{
  for (int i = 0 ; i < _lunghezza; i++)
  {
    if (x == _coordinates[0][i]&&y == _coordinates[1][i])
    {
      --_contatore;
      if (_contatore==0)
      {
        _affondato = true;
      }
    }
  }

}
