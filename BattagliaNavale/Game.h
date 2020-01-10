#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>


class AbstractGame
{
public:
  virtual bool Generate() = 0;
  virtual bool Start() = 0;
  virtual bool Endgame() = 0;
};
class Game : public AbstractGame
{
public:
  Game();
  bool Generate();
  bool Start();
  void Print(Player*, Player*);
  bool Endgame();

private:
  Player * _player1;
  Player * _player2;

};

class OnlineGame : public AbstractGame
{
public:
  bool Generate();
  bool Start();
  bool Endgame();

private:
  Locale _player;
};


#endif
