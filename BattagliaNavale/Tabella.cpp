#include "Tabella.h"
#include <iostream>
using namespace std;
Tabella::~Tabella()
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
  delete[] _radar;
  delete[] _flotta;

}

void Tabella::createRadar()
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
