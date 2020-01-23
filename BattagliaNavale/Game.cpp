#include "Game.h"
#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>
#include <string>


Game::Game()
{

}


bool Game::Generate() //genera il nome dei giocatori e le loro plancie
{
  _turno = 0;
  _players[0] = new Human();

  std::string nome;
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "Giocatore 1 inserisci il tuo nome: " << '\n';
  std::cout << std::string(25,'\n'); //"aggiorna" schermo
  std::cin >> nome;
  _players[0]->setName(nome);
  std::cin.ignore(10000,'\n');
  int scelta;
  do {
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << "\t\t\tBenvenuto " << _players[0]->getName() << "!\n\nPer giocare contro un bot\t\t->\t \033[43;1;5m PREMI 1 \033[0m \nPer giocare contro un tuo amico\t\t->\t \033[43;1;5m PREMI 2 \033[0m" << '\n';
    std::cout << std::string(25,'\n'); //"aggiorna" schermo
    std::cin >> scelta;
    std::cin.ignore(10000,'\n');
    if (scelta==1)
    {
      _players[1] = new Bot();
      // std::cout << std::string(100,'\n'); //"aggiorna" schermo
      // std::cout << "Battezza il tuo avversario: " << '\n';
      // std::cout << std::string(25,'\n'); //"aggiorna" schermo
      // std::cin >> nome;
      _players[1]->setName();
      // std::cin.ignore(10000,'\n');
    }else if (scelta == 2)
    {
      _players[1] = new Human();
      std::cout << std::string(100,'\n'); //"aggiorna" schermo
      std::cout << "Giocatore 2 inserisci il tuo nome: " << '\n';
      std::cout << std::string(25,'\n'); //"aggiorna" schermo
      std::cin >> nome;
      _players[1]->setName(nome);
      std::cin.ignore(10000,'\n');
    }else if(scelta == 0)
    {
      _players[0] = new Bot();
      _players[1] = new Bot();
    }
  } while(scelta != 1 && scelta != 2 && scelta != 0);
  _players[0]->Riempimento();
  _players[1]->Riempimento();
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  return true;
}


bool Game::Start() //contiene il game loop
{
  std::string a;
  while(true)
  {


    _focus = _counter%2;
    if (_focus==0)
    {
      _turno++;
    }
    _unfocused = (_counter + 1)%2;

    if (!_players[_focus]->isBot())
    {
      if (!_players[_unfocused]->isBot())
      {
        std::cout << std::string(100,'\n'); //"aggiorna" schermo
        std::cout << _players[_focus]->getName()<< " premi un tasto qualsiasi e poi invio per iniziare il tuo turno" << '\n';
        std::cout << std::string(25,'\n'); //"aggiorna" schermo
        std::cin >> a;
        std::cin.ignore(10000,'\n');
        std::cout << std::string(100,'\n'); //"aggiorna" schermo
      }
      Print(_players[_focus], _players[_unfocused]);
    }
    _players[_focus]->Attack(_players[_unfocused]);
    if(_players[_unfocused]->getContatore() == 0)
    {
      Print(_players[_focus], _players[_unfocused]);
      std::cout << "Ha vinto " << _players[_focus]->getName() << "!\n";
      return true;
    }
    if (!_players[_focus]->isBot())
    {
      if (!_players[_unfocused]->isBot())
      {
        Print(_players[_focus], _players[_unfocused]);
        std::cout << "Premi un tasto qualsiasi e poi invio e passa il turno a " << _players[_unfocused]->getName() << '\n';
        std::cin >> a;
        std::cin.ignore(10000,'\n');
        std::cout << std::string(100,'\n'); //"aggiorna" schermo
      }
    }
    _counter++;
  }
  return false;
}


void Game::Print(Player *giocatore, Player *avversario)
{
  std::cout << "\n\n ---------------- Turno " << _turno << " di " << giocatore->getName() << " ---------------- \n";
  avversario->PrintRad();
  giocatore->PrintFlo();
}

bool OnlineGame::Generate() //genera il nome dei giocatori e le loro plancie
{
  _turno = 0;
  _player = new Locale();
  std::string nome;
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "Inserisci il tuo nome:" << '\n';
  std::cout << std::string(25,'\n'); //"aggiorna" schermo
  std::cin >> nome;
  _player->setName(nome);
  std::cin.ignore(10000,'\n');
  int scelta;
  bool connected=false;
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  do
  {
    std::cout << "Per usare il tuo computer come server\t\t->\t \033[43;1;5m PREMI 1 \033[0m \nPer connetterti al computer del tuo avversario\t\t->\t \033[43;1;5m PREMI 2 \033[0m" << '\n';
    std::cout << std::string(25,'\n'); //"aggiorna" schermo
    std::cin >> scelta;
    std::cin.ignore(10000,'\n');
    if (scelta == 1)
    {
      connected = _player->Server();
    } else if(scelta == 2)
    {
      connected = _player->Client();
    }else
    {
      std::cout << std::string(100,'\n'); //"aggiorna" schermo
      std::cout << "Ritenta, sarai più fortunato\n" << '\n';
    }
  } while(!connected);
  _player->Riempimento();
  return true;
}
void OnlineGame::Print()
{
//  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "\n\n ---------------- Turno " << _turno << " ---------------- \n";
  _player->PrintRad();
  _player->PrintFlo();
}


bool Game::Endgame()//ancora niente
{
  std::string a;
  char go;

  std::cout << "\nPremi un tasto qualsiasi e poi invio per terminare la partita\n";
  std::cin >> a;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "Ecco alcune statistiche sulla vostra partita:\n\n\n"<< '\n';
  _players[0]->Stats();
  std::cout << std::string(5,'\n');
  _players[1]->Stats();
  std::cout << std::string(10,'\n');
  std::cout << "\n\t\t\tVuoi giocare ancora?\n\nPer giocare ancora\t\t->\t \033[43;1;5m PREMI y \033[0m \n\n(Premi un tasto qualsiasi e poi invio per uscire)";
  std::cout << std::string(10,'\n');
  std::cin >> go;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo

  if(go=='y')
  {
    std::cout << "\t\tD'accordo!\n\n\tAllora premi un tasto qualsiasi e poi invio per ricominciare\n";
    std::cout << std::string(25,'\n'); //"aggiorna" schermo
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n'); //"aggiorna" schermo

    return true;
  }

  std::cout << "Grazie per avere giocato al nostro gioco!\n" << '\n';
  std::cout << "Autori (in ordine di altezza): \n\tDamiano Cabiati\n\tAndrea Sibona\n\tDaniel Siciliano\n" << '\n';
  std::cout << "Si ringraziano inoltre per il loro supporto e per il playtesting: \n\tRiccardo Riente, Marco Mosagna, Lidia Albera e Michele Risino aka Toras" << '\n';
  std::cout << std::string(25,'\n'); //"aggiorna" schermo

  return false;
}




bool OnlineGame::Start()
{
  while(true)
  {
    _turno++;
    if (_player->IsServer())
    {
      // std::cout << std::string(100,'\n'); //"aggiorna" schermo
      Print();
      _player->Attack();
      if (_player->Won())
      {
        Print();
        std::cout << "\033[43;1;5m HAI VINTO! \033[0m" << '\n';
        return true;
      }
      Print();
      _player->Down();
      if (_player->getContatore() == 0 )
      {
        Print();
        std::cout << "Hai perso..." << '\n';
        return true;
      }
      // _player->Print();
    }else if(_player->IsClient())
    {
      Print();
      _player->Down();
      if (_player->getContatore() == 0 )
      {
        Print();
        std::cout << "Hai perso..." << '\n';
        return true;
      }
      Print();
      _player->Attack();
      if (_player->Won())
      {
        Print();
        return true;
      }
      // _player->Print();
    }
  }
}


bool OnlineGame::Endgame()
{
  std::string a;
  char go;

  std::cout << "\nPremi un tasto qualsiasi e poi invio per terminare la partita\n";
  std::cin >> a;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << "Ecco alcune statistiche sulla vostra partita:\n\n\n"<< '\n';
  _player->Stats();

  std::cout << std::string(10,'\n');
  std::cout << "\n\t\t\tVuoi giocare ancora?\n\nPer giocare ancora\t\t->\t \033[43;1;5m PREMI y \033[0m \n\n(Premi un tasto qualsiasi e poi invio per uscire)";
  std::cout << std::string(10,'\n');
  std::cin >> go;
  std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo

  if(go=='y')
  {
    std::cout << "\t\tD'accordo!\n\n\tAllora premi un tasto qualsiasi e poi invio per ricominciare\n";
    std::cout << std::string(25,'\n'); //"aggiorna" schermo
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    return true;
  }

  std::cout << "Grazie per avere giocato al nostro gioco!\n" << '\n';
  std::cout << "Autori (in ordine di altezza): \n\tDamiano Cabiati\n\tAndrea Sibona\n\tDaniel Siciliano\n" << '\n';
  std::cout << "Si ringraziano inoltre per il loro supporto e per il playtesting: \n\tRiccardo Riente, Marco Mosagna, Lidia Albera e Michele Risino aka Toras" << '\n';
  std::cout << std::string(25,'\n'); //"aggiorna" schermo
  return false;
}
