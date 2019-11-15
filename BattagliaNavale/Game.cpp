#include "Game.h"
#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>
#include <string>




Game::Game(){
  std::cout << """Benvenuto! Questo è un gioco di battaglia navale per due giocatori. \n Una volta inseriti i vostri nomi, il primo giocatore inserirà le 10 navi a sua disposizione, seguirà poi il turno del giocatore 2.\nSi susseguiranno poi i rispettivi turni di attacco. Scopo del gioco è annientare la flotta nemica. \nSulla parte alta dell schermo apparirà la plancia di gioco con le proprie navi e i punti in cui l'avversario ha sparato.\nSotto avrete invece il radar, ad indicarvi dove i vostri colpi siano andati a segno o meno.\n\n\t\t\t\tBuona Partita!\n""" << '\n';

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
    std::cout << "Premi un tasto qualsiasi" << '\n';
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n');//"aggiorna" schermo
    std::cout << " -------------- turno "<< _player1.getName()<<" -------------- ";
    _player1.Print();
    _player1.Attack(_player2);
    _player1.Print();


    if(_player2.getContatore() == 0)
    {
      std::cout << "vince il giocatore 2";
      return true;
    }
    std::cout << "Premi un tasto qualsiasi" << '\n';
    std::cin >> a;
    std::cin.ignore(10000,'\n');
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << "Premi un tasto qualsiasi" << '\n';
    std::cin >> a;
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << " -------------- turno "<< _player2.getName() <<" -------------- ";
    _player2.Print();
    _player2.Attack(_player1);
    _player2.Print();

    if(_player1.getContatore() == 0)
    {
      std::cout << "vince il giocatore 2";
      return true;
    }
    std::cout << "Premi un tasto qualsiasi" << '\n';
    std::cin >> a;
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cin.ignore(10000,'\n');

  }
  return false;
}

bool Game::Endgame()//ancora niente
{

}
