#include "Tabella.h"
#include <cmath>
#include <iostream>
using namespace std;

Tabella::~Tabella() //distrugge flotta e radar se creati
{

  for (int i = 0; i < 10 ; i++)
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
    std::cout << "ERRORE IN SETNAVE(Tabella.cpp) \n";
  }
}
void Tabella::createRadar() //crea una matrice radar con puntatori e le riempie di "Sea"
{
  _radarato = true;
  _radar = new Radar*[100];
  for (int i = 0; i < 10; i++)
  {
    _radar[i] = new Radar[10];
    for (int j = 0; j < 10; j++)
    {
      _radar[i][j] = Radar::Sea;
    }
  }
}

void Tabella::createFlotta() //crea una matrice flotta con puntatori e le riempie di "Sea"
{
  _flottato = true;
  _flotta = new Flotta*[10];
  for (int i = 0; i < 10; i++)
  {
    _flotta[i] = new Flotta[10];
    for  (int j = 0; j < 10 ; j++)
    {
      _flotta[i][j] = Flotta::Sea;
    }
  }

}



void Tabella::PrintFlotta() //output della Flotta
{
  cout << "\n\n";
  cout << " \t";
  for (size_t i = 0; i < 10; i++)
  {
    cout <<"  " << (char)(65+i) << "  ";//97
  }
  cout << "\n\n";
  for (int i = 0 ; i < 10 ; i++)
  {
    cout << i+1 << "\t";
    for (int j =0; j < 10; j++)
    {
      if (_radar[i][j]==Radar::Sea)
      {
        if (_flotta[i][j]==Flotta::Sea)
          cout << "\033[35;1;1m  ~  \033[0m";
        if (_flotta[i][j]==Flotta::Ship)
          cout << "\033[31;1;1m  #  \033[0m";
      }else
      {
        if (_radar[i][j]==Radar::Hit)
          cout << "\033[31;1;1m  H  \033[0m";
        if (_radar[i][j]==Radar::Miss)
          cout <<"\033[35;1;1m  M  \033[0m";
      }
    }
    cout <<"\n\n";
  }
}
void Tabella::PrintRadar() // output del radar
{
  cout << "\n\n";
  cout << " \t";
  for (size_t i = 0; i < 10; i++)
  {
    cout <<"  " << (char)(65+i) << "  ";
  }
  cout << "\n\n";

  for (int i=0; i< 10; i++){
    cout << i+1 <<" \t";

    for(int j=0; j<10; j++){
      switch (_radar[i][j]) {
        case Radar::Sea :
          cout <<  "\033[35;1;1m  ~  \033[0m";
          break;
        case Radar::Hit :
          cout << "\033[31;1;1m  H  \033[0m";
          break;
        case Radar::Miss :
          cout << "\033[35;1;1m  M  \033[0m";
          break;
      }
    }
    cout << "\n\n";
  }
}



Flotta * & Tabella::operator[](int i) const // ridefinisce l'operatore [][]
{
  return _flotta[i];
}

bool Tabella::getRadar(int x, int y) //restituisce true se la casella (x,y) è colpibile
{
  if(_radar[y][x] == Radar::Sea) return true;
  if(_radar[y][x] == Radar::Hit || _radar[y][x] == Radar::Miss) return false;
  cout << "ERRORE IN GETRADAR(Tabella.cpp) \n";
  return false; // evitiamo warnings
}

void Tabella::setRadar(int x, int y,Flotta flo) //chiamato dopo un attacco, dichiara il suo risultato e aggiorna il radar dell'attaccante
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
