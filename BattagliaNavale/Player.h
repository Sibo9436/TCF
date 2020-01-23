#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Tabella.h"
#include "Nave.h"
#include "Coordinate.h"

class Human;
class Bot;

class Player
{
  friend class Human;
  friend class Bot;

public:
  Player();
  std::string getName();
  void PrintRad();
  void PrintFlo();
  void Attack(Player&);
  bool Sunk(int, int);
  bool Check(Coordinate, Coordinate);
  void Stats();
  int getColpi_sparati();
  virtual void setName(std::string)=0;
  virtual bool isBot()=0;
  virtual Nave setShips(int, Coordinate) =0;
  virtual void Mozzo(int, int) =0;
  virtual void Attack(Player *) =0;
  virtual void Riempimento() =0;
  virtual int getContatore() const =0;

protected:
  Tabella _Plancia;
  int _n = 5;
  Nave _navi[5];
  int _contatore = 5;
  int colpi_sparati=0;
  int colpi_a_segno=0;
  int navi_affondate=0;
  Nave _funda;

  std::string _nome;

};

class Human: public Player
{
  public:
    void setName(std::string);
    Nave setShips(int, Coordinate);
    void Mozzo(int, int);
    void Attack(Player *);
    void Riempimento();
    int getContatore() const;
    inline bool isBot(){return _isBot;}

  private:
    bool _isBot=false;
};


class Bot: public Player
{
public:
  Coordinate random();
  void setName(std::string);
  Nave setShips(int, Coordinate);
  void Mozzo(int, int);
  void Print();
  void Attack(Player *);
  void Riempimento();
  int getContatore() const;
  inline bool isBot(){return _isBot;}

private:
  Coordinate target;
  Coordinate isAcquired;
  Coordinate firstStrike;
  bool targetAcquired = false;
  Coordinate targetDirection[4] = {Coordinate(0,1),Coordinate(1,0),Coordinate(0,-1),Coordinate(-1,0)};
  int i=0;
  int j=0;
  bool _isBot=true;
};


class Locale : public Human
{
public:
  void PrintRad();
  bool Server();
  bool Client();
  void sunk(Nave);
  inline bool IsServer() {return _isServer;};
  inline bool IsClient() {return _isClient;};
  inline bool Won() {return _win;}
  void Stats();
  void Attack();
  void Down();

private:
  Tabella _Screen;
  int _socket;
  bool _isServer = false;
  bool _isClient = false;
  bool _win = false;
  std::string _oppo;

};


#endif
