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
  bool Endgame();


private:
  Player _player1;
  Player _player2;

};



#endif
