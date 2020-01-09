#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>


class Game
{
public:
  Game();
  bool Generate();
  bool Start();
  void Print(Player*, Player*);
  bool Endgame();

private:
  Bot _player1;
  Bot _player2;

  Player *_p1 = &_player1;
  Player *_p2 = &_player2;

};

class OnlineGame : public Game
{
public:
  bool Generate();
  bool Start();
  void Endgame();

private:
  Player _player;
};


#endif
