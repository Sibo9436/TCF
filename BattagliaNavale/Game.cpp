#include "Game.h"
#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>
#include <string>



Game::Game(){


  std::cout << """\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBenvenuto! Questo è un gioco di battaglia navale per due giocatori. \n Una volta inseriti i vostri nomi, il primo giocatore inserirà le 5 navi a sua disposizione, seguirà poi il turno del giocatore 2.\nSi susseguiranno poi i rispettivi turni di attacco. Scopo del gioco è annientare la flotta nemica. \nSulla parte alta dell schermo apparirà la plancia di gioco con le proprie navi e i punti in cui l'avversario ha sparato.\nSotto avrete invece il radar, ad indicarvi dove i vostri colpi siano andati a segno o meno.\n\n\t\t\t\t\t\t\t\t \033[43;1;5m Buona Partita \033[0m \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n""" << '\n';

}

bool Game::Generate() //genera il nome dei giocatori e le loro plancie
{
  // _players[0] = new Human();
  // _players[0] = new Bot();
  _players[0] = new Human();

  std::string nome;
  std::cout << "Giocatore 1 inserisci il tuo nome... " << '\n';
  std::cin >> nome;
  _players[0]->setName(nome);
  int scelta;
  do {
    std::cout << "Giocherai da solo(1) o in compagnia(2)?" << '\n';
    std::cin >> scelta;
    if (scelta==1)
    {
      _players[1] = new Bot();

    }else if (scelta == 2)
    {
      _players[1] = new Human();
      std::cout << "Giocatore 2 inserisci il tuo nome... " << '\n';
      std::cin >> nome;
      _players[1]->setName(nome);
    }else if(scelta == 0)
    {
      _players[0] = new Bot();
      _players[1] = new Bot();
    }
  } while(scelta != 1 && scelta != 2 && scelta != 0);
  _players[0]->Riempimento();
  _players[1]->Riempimento();
  return true;
}

bool Game::Start() //contiene il game loop
{

  std::string a;
  while(true)
  {
    _focus = _counter%2;
    _unfocused = (_counter + 1)%2;
//     std::cout << _players[_focus]->getName()<< " premi un tasto qualsiasi per iniziare il tuo turno" << '\n';
//     std::cin >> a;
//     std::cin.ignore(10000,'\n');
//     std::cout << std::string(100,'\n'); //"aggiorna" schermo
//     Print(_players[_focus], _players[_unfocused]);
//     _players[_focus]->Attack(_players[_unfocused]);
//     Print(_players[_focus], _players[_unfocused]);
// //NON CE N'È BISOGNO
// //BASTA USARE FOCUS
//     for (Player i : _players)
//     {
//       if (i->getContatore() == 0)
//       {
//         std::cout << "Ha vinto " << i->getName() << "!\n";
//         return true;
//       }
//     }
//     std::cout << "Premi un tasto qualsiasi e passa il turno a " << _players[_unfocused]->getName() << '\n';
//     std::cin >> a;
//     std::cin.ignore(10000,'\n');
    if (!_players[_focus]->isBot())
    {
      std::cout << std::string(100,'\n'); //"aggiorna" schermo
      if (!_players[_unfocused]->isBot())
      {
        std::cout << _players[_focus]->getName()<< " premi un tasto qualsiasi per iniziare il tuo turno" << '\n';
        std::cin >> a;
        std::cin.ignore(10000,'\n');
      }
      std::cout << std::string(100,'\n'); //"aggiorna" schermo
      Print(_players[_focus], _players[_unfocused]);
    }
    _players[_focus]->Attack(_players[_unfocused]);
    if (!_players[_focus]->isBot())
    {
      Print(_players[_focus], _players[_unfocused]);

      if (!_players[_unfocused]->isBot())
      {
        std::cout << "Premi un tasto qualsiasi e passa il turno a " << _players[_unfocused]->getName() << '\n';
        std::cin >> a;
        std::cin.ignore(10000,'\n');
      }
      std::cout << std::string(100,'\n'); //"aggiorna" schermo

    }
    if(_players[_unfocused]->getContatore() == 0)
    {
      std::cout << "Ha vinto " << _players[1]->getName() << "!\n";
      return true;
    }
    //std::cin >> a;
    std::cout << std::string(1,'\n'); //"aggiorna" schermo
    //std::cin.ignore(10000,'\n');
    _counter++;

  }
  return false;
}

void Game::Print(Player *giocatore, Player *avversario)
{
//  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "\n\n --------------------- Turno " << giocatore->getName() <<" -------------------- \n";
  avversario->PrintRad();
  giocatore->PrintFlo();
}

bool Game::Endgame()//ancora niente
{
  std::string a;
  char go;

  std::cout << "\nPremi un tasto qualsiasi per terminare la partita\n";
  std::cin >> a;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "Congratulazioni! Ecco alcune statistiche sulla vostra partita:\n\n\n"<< '\n';
  _players[0]->Stats();
  std::cout << std::string(5,'\n');
  _players[1]->Stats();

  std::cout << std::string(10,'\n');
  std::cout << "\n\t\t\tVuoi giocare ancora?\n\n\t\t(Premi y per giocare ancora, qualsiasi altro tasto per uscire)";
  std::cout << std::string(10,'\n');
  std::cin >> go;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo

  if(go=='y')
  {
    std::cout << "\t\tD'accordo!\n\n\tAllora premi un tasto qualsiasi per ricominciare\n";
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    return true;
  }

  std::cout << "Grazie per avere giocato al nostro gioco!\n" << '\n';
  std::cout << "Autori (in ordine di altezza): \n\tDamiano Cabiati\n\tAndrea Sibona\n\tDaniel Siciliano\n" << '\n';
  std::cout << "Si ringraziano inoltre per il loro supporto e per il playtesting: \n\tRiccardo Riente, Marco Mosagna, Lidia Albera e Paolo Maria Oreste Carlo Cabiati" << '\n';
  std::cout << std::string(25,'\n'); //"aggiorna" schermo
  return false;
}
bool OnlineGame::Generate() //genera il nome dei giocatori e le loro plancie
{
  std::string nome;
  std::cout << "Inserisci il tuo nome... " << '\n';
  std::cin >> nome;
  _player.setName(nome);
  int scelta;
  std::cout << "Sarai server(1) o client(2)?" << '\n';
  std::cin >> scelta;
  if (scelta == 1)
  {
    _player.Server();
  } else if(scelta == 2)
  {
    _player.Client();
  }
  _player.Riempimento();
  return true;
}
bool OnlineGame::Start()
{
  while(true)
  {
    if (_player.IsServer())
    {
      _player.Attack();
      if (_player.Won())
      {
        return true;
      }
      _player.Down();
      if (_player.getContatore() == 0 )
      {
        std::cout << "Sorry bro" << '\n';
        return true;
      }
      // _player.Print();
    }else if(_player.IsClient())
    {
      _player.Down();
      if (_player.getContatore() == 0 )
      {
        std::cout << "Sorry bro" << '\n';
        return true;
      }
      _player.Attack();
      if (_player.Won())
      {
        return true;
      }
      // _player.Print();
    }
  }

}
bool OnlineGame::Endgame()
{
  std::string a;
  char go;

  std::cout << "\nPremi un tasto qualsiasi per terminare la partita\n";
  std::cin >> a;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "Congratulazioni! Ecco alcune statistiche sulla vostra partita:\n\n\n"<< '\n';
  _player.Stats();

  std::cout << std::string(10,'\n');
  std::cout << "\n\t\t\tVuoi giocare ancora?\n\n\t\t(Premi y per giocare ancora, qualsiasi altro tasto per uscire)";
  std::cout << std::string(10,'\n');
  std::cin >> go;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo

  if(go=='y')
  {
    std::cout << "\t\tD'accordo!\n\n\tAllora premi un tasto qualsiasi per ricominciare\n";
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    return true;
  }

  std::cout << "Grazie per avere giocato al nostro gioco!\n" << '\n';
  std::cout << "Autori (in ordine di altezza): \n\tDamiano Cabiati\n\tAndrea Sibona\n\tDaniel Siciliano\n" << '\n';
  std::cout << "Si ringraziano inoltre per il loro supporto e per il playtesting: \n\tRiccardo Riente, Marco Mosagna, Lidia Albera e Paolo Maria Oreste Carlo Cabiati" << '\n';
  std::cout << std::string(25,'\n'); //"aggiorna" schermo
  return false;
}
