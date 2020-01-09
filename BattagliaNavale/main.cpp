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

  return 0;
}
