#include <cmath>
#include <iostream>
#include "Tabella.h"
using namespace std;

// Distruttore
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
    }
  }
}

int Tabella::getN()
{
  return n;

}

void Tabella::setNave(Nave boat)//Posizionamento di una nave sulla plancia
{
  for (int i = 0 ; i < boat.getlunghezza() ; i++ )
  {
    _flotta[boat[i].getY()][boat[i].getX()] = Flotta::Ship;
  }
}

void Tabella::setNave(Coordinate begin, Coordinate end) //riempie le caselle di flotta con "Ship"
{
  int x1 = begin.getX();
  int y1 = begin.getY();
  int x2 = end.getX();
  int y2 = end.getY();

  if (x1==x2)
  {
    int max = (y2 > y1)? y2 : y1;
    int min = (y2 < y1)? y2 : y1;
    for (int i = min; i <= max; i++)
    {
      _flotta[i][x1] = Flotta::Ship;
      for(int h = i-1; h <= i+1; h++)
      {
        for(int k = x1-1; k <= x1+1; k++)
        {
          if((h > -1) && (h < n) && (k > -1) && (k < n) && (_flotta[h][k] == Flotta::Sea))
          {
            _flotta[h][k] = Flotta::Near;
          }
        }
      }
    }
  } else if (y1==y2)
   {
    int max = (x2 > x1)? x2 : x1;
    int min = (x2 < x1)? x2 : x1;
    for (int i = min; i <= max; i++)
    {
      _flotta[y1][i] = Flotta::Ship;
      for(int h = y1-1; h <= y1+1; h++)
      {
        for(int k = i-1; k <= i+1; k++)
        {
          if((h > -1) && (h < n) && (k > -1) && (k < n) && (_flotta[h][k] == Flotta::Sea))
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
  cout << "\t ";
  for (int i = 0; i < n; i++)
  {
    cout <<"  " << (char)(65+i) << "  ";//97
  }
  cout <<"\n";
  cout << "\t┌";
  for (int k=0; k<n;k++)
  {
    cout << "─────";
  }
  cout << "┐\n";
  for (int i = 0 ; i < n ; i++)
  {
    cout << "       "<<i+1 << "│";
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
          cout << "\033[35;1;1m  @  \033[0m";
      }
    }
    cout << "│";
    if (i != n-1)
    {
      cout <<"\n\t│";
      for (int k = 0 ; k < n-3; k++)
      {
        cout << "\t";
      }
      cout <<" │";
    }
    cout << "\n";
  }
  cout << "\t└";
  for (int k=0; k<n;k++)
  {
    cout << "─────";
  }
  cout << "┘\n";
}

void Tabella::PrintRadar() // output del radar
{
  cout << "\t ";
  for (int i = 0; i < n; i++)
  {
    cout <<"  " << (char)(65+i) << "  ";//97
  }
  cout <<"\n";
  cout << "\t┌";
  for (int k=0; k<n;k++)
  {
    cout << "─────";
  }
  cout << "┐\n";

  for (int i=0; i< n; i++){
    cout << "       "<<i+1 << "│";
    for(int j=0; j<n; j++){
      switch (_radar[i][j]) {
        case Radar::Sea :
          cout << "\033[35;1;1m  ~  \033[0m";
          break;
        case Radar::Hit :
          cout << "\033[31;1;1m  X  \033[0m";
          break;
        case Radar::Miss :
          cout << "\033[35;1;1m  @  \033[0m";
          break;
      }
    }
    cout << "│";
    if (i != n-1)
    {
      cout <<"\n\t│";
      for (int k = 0 ; k < n-3; k++)
      {
        cout << "\t";
      }
      cout <<" │";
    }
    cout << "\n";
  }
  cout << "\t└";
  for (int k=0; k<n;k++)
  {
    cout << "─────";
  }
  cout << "┘\n";
}

Flotta * & Tabella::operator[](int i) const // ridefinisce l'operatore [][]
{
  return _flotta[i];
}

bool Tabella::getRadar(int x, int y) //restituisce true se la casella (x,y) è colpibile
{
  if(y<0 || y>n-1) return false; //soluzione debole
  if(x<0 || x>n-1) return false;
  if(_radar[y][x] == Radar::Sea) return true;
  if(_radar[y][x] == Radar::Hit || _radar[y][x] == Radar::Miss) return false;
  cout << "ERRORE IN GETRADAR(Tabella.cpp) \n";
  return false; // evitiamo warnings
}

bool Tabella::setRadar(int x, int y) //chiamato dopo un attacco, dichiara il suo risultato e aggiorna il radar dell'attaccante
{
  if (_flotta[y][x] == Flotta::Ship)
  {
    _radar[y][x] = Radar::Hit;
    return true;
  }
  else
  {
    _radar[y][x] = Radar::Miss;
    return false;
  }
}

bool Tabella::setRadar(int x, int y,Flotta flo) //chiamato dopo un attacco, dichiara il suo risultato e aggiorna il radar dell'attaccante
{
  if (flo == Flotta::Ship)
  {
    _radar[y][x] = Radar::Hit;
    return true;
  }
  else
  {
    _radar[y][x] = Radar::Miss;
    return false;
  }
}

void Tabella::Greta()//Pulisce il mare
{
  for (int i=0; i<n; i++)
  {
    for (int j=0; j<n; j++)
    {
      if (_flotta[i][j]==Flotta::Near)
      {
        _flotta[i][j]=Flotta::Sea;
      }
    }
  }
}
