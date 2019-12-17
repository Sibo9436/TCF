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
  std::string nome;
  std::cout << "Giocatore 1 inserisci il tuo nome... " << '\n';
  std::cin >> nome;
  _player1.setName(nome);
  std::cout << "Giocatore 2 inserisci il tuo nome... " << '\n';
  std::cin >> nome;
  _player2.setName(nome);
  _player1.Riempimento();
  _player2.Riempimento();
  return true;
}

bool Game::Start() //contiene il game loop
{
  std::string a;
  while(true)
  {
    std::cout << _player1.getName()<< " premi un tasto qualsiasi per iniziare il tuo turno" << '\n';
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n');//"aggiorna" schermo
    std::cout << " -------------------- Turno "<< _player1.getName()<<" -------------------- ";
    _player1.Print();
    _player1.Attack(_player2);
    _player1.Print();


    if(_player2.getContatore() == 0)
    {
      std::cout << "Ha vinto " << _player1.getName() <<"\n";
      return true;
    }
    std::cout << "Premi un tasto qualsiasi e passa il turno a " << _player2.getName() << '\n';
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << _player2.getName()<< " premi un tasto qualsiasi per iniziare il tuo turno" << '\n';
    std::cin >> a;
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << " --------------------- Turno "<< _player2.getName() <<" -------------------- ";
    _player2.Print();
    _player2.Attack(_player1);
    _player2.Print();

    if(_player1.getContatore() == 0)
    {
      std::cout << "Ha vinto " << _player2.getName()<<"\n";
      return true;
    }
    std::cout << "Premi un tasto qualsiasi e passa il turno a " << _player1.getName() << '\n';
    std::cin >> a;
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cin.ignore(10000,'\n');

  }
  return false;
}

void Game::Endgame()//ancora niente
{
  std::cout << "Conygratulazioni! Ecco alcune statistiche sulla vostra partita:\n"<< '\n';
  _player1.Stats();
  _player2.Stats();

  std::cout << "Grazie per avere giocato al nostro gioco!" << '\n';
  std::cout << "Autori (in ordine di altezza): \n\tDaniel Ladaniuc\n\tDamiano Cabiati\n\tAndrea Sibona\n\tDaniel Siciliano" << '\n';
  std::cout << "Si ringraziano inoltre per il loro supporto e per il playtesting: \n\tRiccardo Riente e Marco Mosagna" << '\n';
  std::cout << "" << '\n';
  std::cout << "" << '\n';
  std::cout << "" << '\n';
  std::cout << "" << '\n';
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
void OnlineGame::Endgame()
{
  std::cout << "Conygratulazioni! Ecco alcune statistiche sulla vostra partita:\n"<< '\n';
  _player.Stats();

  std::cout << "Grazie per avere giocato al nostro gioco!" << '\n';
  std::cout << "Autori (in ordine di altezza): \n\tDaniel Ladaniuc\n\tDamiano Cabiati\n\tAndrea Sibona\n\tDaniel Siciliano" << '\n';
  std::cout << "Si ringraziano inoltre per il loro supporto e per il playtesting: \n\tRiccardo Riente e Marco Mosagna" << '\n';
  std::cout << "" << '\n';
  std::cout << "" << '\n';
  std::cout << "" << '\n';
  std::cout << "" << '\n';
}
