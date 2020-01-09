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
  // void Connect();
  void Server();
  void Client();
  void setName(std::string);
  std::string getName();
  Nave setShips(int, Coordinate);
  bool Check(Coordinate,Coordinate);
  void Mozzo(int, int);
  void PrintRad();
  void PrintFlo();
  void Attack(Player *);
  bool Sunk(int, int);
  void Print();
  void Attack();
  void Down();
  void Attack(Player&);
  void Riempimento();
  int getContatore() const;
  inline bool IsServer() {return _isServer;};
  inline bool IsClient() {return _isClient;};
  inline bool Won() {return _win;}
  void Stats();

private:
  Tabella _Plancia;
  int _n = 5;
  Nave _navi[5];
  int _contatore = 5;
  int colpi_sparati=0;
  int colpi_a_segno=0;
  int navi_affondate=0;
  int _socket;
  bool _isServer = false;
  bool _isClient = false;
  bool _win = false;
  bool _funda = false;

  std::string _nome;

};

#endif
