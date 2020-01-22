#include "Tabella.h"
#include "Nave.h"
#include "Player.h"
#include "Game.h"
#include <iostream>


int main()
{
  int scelta;
  AbstractGame *partita;

  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout <<"""\t\t\t    ____        __  __              ___      """ <<std::endl;
  std::cout <<"""\t\t\t   / __ )____ _/ /_/ /_____ _____ _/ (_)___ _""" <<std::endl;
  std::cout <<"""\t\t\t  / __  / __ `/ __/ __/ __ `/ __ `/ / / __ `/""" <<std::endl;
  std::cout <<"""\t\t\t / /_/ / /_/ / /_/ /_/ /_/ / /_/ / / / /_/ / """ <<std::endl;
  std::cout <<"""\t\t\t/_____/\\__,_/\\__/\\__/\\__,_/\\__, /_/_/\\__,_/  """ <<std::endl;
  std::cout <<"""\t\t\t    _   __                /____/             """ <<std::endl;
  std::cout <<"""\t\t\t   / | / /___ __   ______ _/ /__             """ <<std::endl;
  std::cout <<"""\t\t\t  /  |/ / __ `/ | / / __ `/ / _ \\            """ <<std::endl;
  std::cout <<"""\t\t\t / /|  / /_/ /| |/ / /_/ / /  __/            """ <<std::endl;
  std::cout <<"""\t\t\t/_/ |_/\\__,_/ |___/\\__,_/_/\\___/             """ <<std::endl;
  std::cout <<"""\t\t\t                                             """ <<std::endl;
  std::cout << """\n\n\t\t\t\t \033[43;1;5m Buona Partita \033[0m""" << std::endl;
  std::cout << std::string(25,'\n'); //"aggiorna" schermo

  do {
    // std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << "Vuoi giocare solo su questo computer(1) o online?(2)" << '\n';
    // std::cout << std::string(25,'\n'); //"aggiorna" schermo
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
