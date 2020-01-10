#include "Tabella.h"
#include "Nave.h"
#include "Player.h"
#include "Game.h"
#include <iostream>


int main()
{


  int scelta;
  AbstractGame *partita;
  do {
    std::cout << "Vuoi giocare in single player(1) o in multiplayer online?(2)" << '\n';
    std::cin >> scelta;
    if (scelta == 1)
    {
      partita = new Game();
    }else if ( scelta == 2)
    {
      partita = new OnlineGame();
    }
  } while(scelta != 1 && scelta != 2);
  bool again = false;

  do{
    if(partita->Generate())
    {
      if(partita->Start())
      {
        again = partita->Endgame();
      }
    } else
    {
      std::cout << "Qualcosa è andato storto" << '\n';
    }
  }while (again == true);

  return 0;
}
