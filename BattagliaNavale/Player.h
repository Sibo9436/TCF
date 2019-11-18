#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Tabella.h"
#include "Nave.h"
#include "Coordinate.h"


class Player
{
public:
  Player();
  void setName(std::string);
  std::string getName();
  Nave setShips(int, int, int);
  Nave setShips(int, Coordinate);
  bool Check(int, int, int, int);
  bool Check(Coordinate,Coordinate);
  void Mozzo(int, int);
  Nave pushNave(int,int,int,int);
  void Print();
  void Attack(Player&);
  void Hit(int, int);
  void Riempimento();
  int getContatore() const;



private:
  Tabella  _Screen;
  Tabella _Plancia;
  int _n = 1;
  Nave _navi[1];
  int _contatore = 1;

  std::string _nome;

};




#endif
