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
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << "Vuoi giocare solo su questo computer(1) o online?(2)" << '\n';
    std::cout << std::string(25,'\n'); //"aggiorna" schermo
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
