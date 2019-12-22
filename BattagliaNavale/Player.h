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
  Nave setShips(int, Coordinate);
  bool Check(Coordinate,Coordinate);
  void Mozzo(int, int);
  void PrintRad();
  void PrintFlo();
  void Attack(Player *);
  bool Sunk(int, int);
  void Riempimento();
  int getContatore() const;
  void Stats();

private:
  Tabella _Plancia;
  int _n = 5;
  Nave _navi[5];
  int _contatore = 5;
  int colpi_sparati=0;
  int colpi_a_segno=0;
  int navi_affondate=0;

  std::string _nome;

};

#endif
