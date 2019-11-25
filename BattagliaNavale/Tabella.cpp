#include "Tabella.h"
#include <cmath>
#include <iostream>
using namespace std;

Tabella::~Tabella() //distrugge flotta e radar se creati
{

  for (int i = 0; i < n ; i++)
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
void Tabella::setNave(Nave boat)
{
  for (int i = 0 ; i < boat.getlunghezza() ; i++ )
  {
    _flotta[boat[i].getY()][boat[i].getX()] = Flotta::Ship;
  }
}
void Tabella::setNave(Coordinate begin, Coordinate end) //Nome provvisorio, riempie le caselle di flotta con" "Ship"
{
  if (begin.getX()==end.getX())
  {
    int max = (end.getY() > begin.getY())? end.getY() : begin.getY();
    int min = (end.getY() < begin.getY())? end.getY() : begin.getY();
    for (int i = min; i <= max; i++)
    {
      _flotta[i][begin.getX()] = Flotta::Ship;
      for(int h = i-1; h <= i+1; h++)
      {
        for(int k = begin.getX()-1; k <= begin.getX()+1; k++)
        {
          if((h > -1) && (h < 10) && (k > -1) && (k < 10) && (_flotta[h][k] == Flotta::Sea))
          {
            _flotta[h][k] = Flotta::Near;
          }
        }
      }
    }
  } else if (begin.getY()==end.getY())
   {
    int max = (end.getX() > begin.getX())? end.getX() : begin.getX();
    int min = (end.getX() < begin.getX())? end.getX() : begin.getX();
    for (int i = min; i <= max; i++)
    {
      _flotta[begin.getY()][i] = Flotta::Ship;
      for(int h = begin.getY()-1; h <= begin.getY()+1; h++)
      {
        for(int k = i-1; k <= i+1; k++)
        {
          if((h > -1) && (h < 10) && (k > -1) && (k < 10) && (_flotta[h][k] == Flotta::Sea))
          {
            _flotta[h][k] = Flotta::Near;
          }
        }
      }
    }
  } else
  {
    std::cout << "ERRORE IN SETNAVE(Tabella.cpp) \n";
  }
}

void Tabella::createRadar() //crea una matrice radar con puntatori e le riempie di "Sea"
{
  _radarato = true;
  _radar = new Radar*[n];
  for (int i = 0; i < n; i++)
  {
    _radar[i] = new Radar[n];
    for (int j = 0; j < n; j++)
    {
      _radar[i][j] = Radar::Sea;
    }
  }
}

void Tabella::createFlotta() //crea una matrice flotta con puntatori e le riempie di "Sea"
{
  _flottato = true;
  _flotta = new Flotta*[n];
  for (int i = 0; i < n; i++)
  {
    _flotta[i] = new Flotta[n];
    for  (int j = 0; j < n ; j++)
    {
      _flotta[i][j] = Flotta::Sea;
    }
  }

}



void Tabella::PrintFlotta() //output della Flotta
{
  cout << " \t";
  for (int i = 0; i < n; i++)
  {
    cout <<"  " << (char)(65+i) << "  ";//97
  }
  cout << "\n\n";
  for (int i = 0 ; i < n ; i++)
  {
    cout << i+1 << "\t";
    for (int j =0; j < n; j++)
    {
      if (_radar[i][j]==Radar::Sea)
      {
        if (_flotta[i][j]==Flotta::Sea)
          cout << "\033[35;1;1m  ~  \033[0m";
        if (_flotta[i][j]==Flotta::Near)
          cout << "\033[35;1;1m  0  \033[0m";
        if (_flotta[i][j]==Flotta::Ship)
          cout << "\033[31;1;1m  #  \033[0m";
      }else
      {
        if (_radar[i][j]==Radar::Hit)
          cout << "\033[31;1;1m  X  \033[0m";
        if (_radar[i][j]==Radar::Miss)
          cout <<"\033[35;1;1m  @  \033[0m";
      }
    }
    cout <<"\n\n";
  }
}
void Tabella::PrintRadar() // output del radar
{
  cout << " \t";
  for (int i = 0; i < n; i++)
  {
    cout <<"  " << (char)(65+i) << "  ";
  }
  cout << "\n\n";

  for (int i=0; i< n; i++){
    cout << i+1 <<" \t";

    for(int j=0; j<n; j++){
      switch (_radar[i][j]) {
        case Radar::Sea :
          cout <<  "\033[35;1;1m  ~  \033[0m";
          break;
        case Radar::Hit :
          cout << "\033[31;1;1m  X  \033[0m";
          break;
        case Radar::Miss :
          cout << "\033[35;1;1m  @  \033[0m";
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

bool Tabella::setRadar(int x, int y,Flotta flo) //chiamato dopo un attacco, dichiara il suo risultato e aggiorna il radar dell'attaccante
{
  if (flo == Flotta::Ship)
  {
    cout << "Colpito!\n";
    _radar[y][x] = Radar::Hit;
    return true;
  }
  else
  {
    cout << "Mancato!\n";
    _radar[y][x] = Radar::Miss;
    return false;
  }
}


void Tabella::setRadar(int x, int y) //chiamato dopo un attacco, dichiara il suo risultato e aggiorna il radar dell'attaccante
{
  Radar rad;
  if (_flotta[y][x]==Flotta::Sea || _flotta[y][x] == Flotta::Near)
  {
    // cout << "Mancato!\n";
    rad= Radar::Miss;
  }
  if (_flotta[y][x] == Flotta::Ship)
  {
    // cout << "Colpito!\n";
    rad= Radar::Hit;
  }
  _radar[y][x] = rad;
}

void Tabella::Greta()
{
  for (int i=0; i<10; i++)
  {
    for (int j=0; j<10; j++)
    {
      if (_flotta[i][j]==Flotta::Near)
      {
        _flotta[i][j]=Flotta::Sea;
      }
    }
  }
}
