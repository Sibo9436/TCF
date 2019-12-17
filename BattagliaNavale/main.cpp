#include "Tabella.h"
#include "Nave.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
//mi sento nel posto sbagliato
//Al momento giusto <3
int main()
{

//

  // Player Andrea;
  // Player Daniel;
  int scelta;
  std::cout << "Vuoi giocare in single player(1) o in multiplayer online?(2)" << '\n';
  std::cin >> scelta;
  if (scelta == 1)
  {
    Game partita;
    if(partita.Generate())
    {
      if(partita.Start())
      {
        partita.Endgame();
      }
    } else
    {
      std::cout << "Qualcosa è andato storto" << '\n';
    }
  }
  else if(scelta==2)
  {
    OnlineGame partita;
    if(partita.Generate())
    {
      if(partita.Start())
      {
        partita.Endgame();
      }
    } else
    {
      std::cout << "Qualcosa è andato storto" << '\n';
    }
  }


  return 0;
}
