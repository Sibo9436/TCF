#include "Tabella.h"
#include <cmath>
#include <iostream>
using namespace std;
Tabella::~Tabella() //distrugge flotta e radar se creati
{

  for (int i = 0; i < 8 ; i++)
  {
    if (_flottato)
    {
      delete[] _flotta[i];
    }
    if (_radarato)
    {
    delete[] _radar[i];
    }
  }
  // delete[] _radar;
  // std::cout << "RODARORADA" << '\n';
  // delete[] _flotta;

}
void Tabella::setNave(int x1, int y1, int x2, int y2) //Nome provvisorio, riempie le caselle di flotta con" "Ship"
{
  if (x1==x2)
  {
    int max = (y2 > y1)? y2 : y1;
    int min = (y2 < y1)? y2 : y1;
    for (int i = min; i <= max; i++)
    {
      _flotta[i][x1] = Flotta::Ship;
    }
  } else if (y1==y2)
   {
    int max = (x2 > x1)? x2 : x1;
    int min = (x2 < x1)? x2 : x1;
    for (int i = min; i <= max; i++)
    {
      _flotta[y1][i] = Flotta::Ship;

    }
  } else
  {
    std::cout << "hai cazziato";
  }
}
void Tabella::createRadar() //crea una matrice radar con puntatori e le riempie di "Sea"
{
  _radarato = true;
  _radar = new Radar*[8];
  for (int i = 0; i < 8; i++)
  {
    _radar[i] = new Radar[8];
    for (int j = 0; j < 8; j++)
    {
      _radar[i][j] = Radar::Sea;
    }
  }
}

void Tabella::createFlotta()
{
  _flottato = true;
  _flotta = new Flotta*[8];
  for (int i = 0; i < 8; i++)
  {
    _flotta[i] = new Flotta[8];
    for  (int j = 0; j < 8 ; j++)
    {
      _flotta[i][j] = Flotta::Sea;
    }
  }

}



void Tabella::PrintFlotta()
{
  for (size_t i = 0; i < 8; i++)
  {
    cout << (char)(97+i);
  }
  cout << "\n";
  for (int i = 0 ; i < 8 ; i++)
  {
    for (int j =0; j < 8; j++)
    {
      if (_flotta[i][j]==Flotta::Sea)
        cout << "Star";
      if (_flotta[i][j]==Flotta::Ship)
        cout << "Ship";
    }
    cout <<"\n";
  }
}
void Tabella::PrintRadar()
{
  for (int i=0; i< 8; i++){
    for(int j=0; j<8; j++){
      switch (_radar[i][j]) {
        case Radar::Sea :
          cout << 0;
          break;
        case Radar::Hit :
          cout << "H";
          break;
        case Radar::Miss :
          cout << "M";
          break;
      }
    }
    cout << "\n";
  }
}



Flotta * & Tabella::operator[](int i) const
{
  return _flotta[i];
}

bool Tabella::getRadar(int x, int y)
{
  if(_radar[y][x] == Radar::Sea) return true;
  if(_radar[y][x] == Radar::Hit || _radar[y][x] == Radar::Miss) return false;
}

void Tabella::setRadar(int x, int y,Flotta flo)
{
  Radar rad;
  if (flo==Flotta::Sea)
  {
    cout << "Mancato!\n";
    rad= Radar::Miss;
  }
  if (flo == Flotta::Ship)
  {
    cout << "Colpito!\n";
    rad= Radar::Hit;
  }
  _radar[y][x] = rad;
}
