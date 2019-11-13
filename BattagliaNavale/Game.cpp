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
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    std::cout << "Premi un tasto qualsiasi" << '\n';
    std::cin >> a;
    std::cout << " -------------- turno "<< _player2.getName() <<" -------------- ";
    _player2.Print();
    _player2.Attack(_player1);
    _player2.Print();

    if(_player1.getContatore() == 0)
    {
      std::cout << "vince il giocatore 2";
      return true;
    }
  }
  return false;
}

bool Game::Endgame()//ancora niente
{

}
