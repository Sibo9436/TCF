#include "Tabella.h"
#include "Nave.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

// Qui il giocatore sceglie se giocare online o in locale
// il gioco viene quindi generato e lanciato, con la possibilità di fare più partite dello stesso tipo

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


  std::cout << "Premi 'r' per conoscere le regole del gioco ";
  char rulez;
  std::cin >> rulez;

  std::cin.ignore(10000,'\n');
  if (rulez == 'r')
  {
    std::cout << std::string(25,'\n'); //"aggiorna" schermo
    std::cout << "A inizio partita ad entrambi i giocatori sarà chiesto di posizionare la propia flotta sulla plancia di gioco;" << '\n';
    std::cout << "le restrizioni riguardanti il posizionamento della nave sono le seguenti:" << '\n';
    std::cout << "\t · le navi possono essere disposte solo verticalmente o orizzontalmente;"<< '\n';
    std::cout << "\t · le navi devono essere interamente incluse nella plancia di gioco;" << '\n';
    std::cout << "\t · le navi non possono sovrapporsi o toccarsi." << '\n';
    std::cout << "" << '\n';
    std::cout << "Una volta terminata la prima fase, inizia la partita vera e propria." << '\n';
    std::cout << "Lo scopo di ogni giocatore sarà quello di affondare la flotta dell'avversario." << '\n';
    std::cout << "Ogni turno bisognerà inserire le coorinate corrispondenti al quadrante che si desidera colpire." << '\n';
    std::cout << "\n" << '\n';
    std::cout << "Sono disponibili le seguenti modalità di gioco:" << '\n';
    std::cout << "\t · in locale, con la possibilità di giocare:" << '\n';
    std::cout << "\t\t · contro un amico;" << '\n';
    std::cout << "\t\t · contro la CPU;" << '\n';
    std::cout << "\t · in condivisione su rete locale; in questo caso:" << '\n';
    std::cout << "\t\t · un giocatore assume il ruolo di server e comunica all'altro il proprio indirizzo IP;" << '\n';
    std::cout << "\t\t · l'altro giocatore assume il ruolo di client e si collega all'indirizzo IP del server." << '\n';
    std::cout << std::string(15,'\n'); //"aggiorna" schermo
  }
  do {
    std::cout << "Per giocare su questo computer\t\t->\t \033[43;1;5m PREMI 1 \033[0m \nPer giocare online\t\t\t->\t \033[43;1;5m PREMI 2 \033[0m" << '\n';
    std::cin >> scelta;
    std::cin.ignore(10000,'\n');
    if (scelta == 1)
    {
      partita = new Game();
    }else if ( scelta == 2)
    partita = new OnlineGame();
    {
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
