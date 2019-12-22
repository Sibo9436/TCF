#include "Tabella.h"
#include "Nave.h"
#include "Player.h"
#include "Game.h"
#include <iostream>


int main()
{
  Game partita;
  bool again = false;

  do{
    if(partita.Generate())
    {
      if(partita.Start())
      {
        again = partita.Endgame();
      }
    } else
    {
      std::cout << "Qualcosa è andato storto" << '\n';
    }
  }while (again == true);

  return 0;
}
