#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>


Player::Player()
{

}
std::string Player::getName()
{
  return _nome;
}
void Player::setName(std::string Nome)
{
  _nome = Nome;
}

bool Player::Check(int x1, int y1, int x2, int y2)
{

  if (x1==x2) {
    int max = (y2 > y1)? y2 : y1;
    int min = (y2 < y1)? y2 : y1;
    for (int i = min; i < max; i++)
    {
      if (_Plancia[x1][i] != Flotta::Sea)
        return false;
    }
    return true;
  } else if (y1==y2) {
    int max = (x2 > x1)? x2 : x1;
    int min = (x2 < x1)? x2 : x1;
    for (int i = min; i < max; i++)
    {
      if (_Plancia[i][y1] != Flotta::Sea)
        return false;
    }
    return true;
  } else {
    std::cout << "hai cazziato";
  }

}



Nave Player::setShips(int l, int x1, int y1){


    bool r = Check(x1,y1,x1+l,y1);
    bool le = Check(x1,y1,x1-l,y1);
    bool u = Check(x1,y1,x1,y1-l);
    bool d = Check(x1,y1,x1,y1+l);
    if(!(u && d && r && l)){
      std::cout << "not valid\n Prova coordinate valide\n";
      int x,y;
      std::cin >> x >> y;
      return setShips(l,x,y);
    }
    if (u)
    {
      std::cout << "Premi u per mettere la nave in " << x1 << ", " << y1-l << "\n";
    }
    if (d)
    {
      std::cout << "Premi d per mettere la nave in " << x1 << ", " << y1+l << "\n";
    }
    if (le)
    {
      std::cout << "Premi l per mettere la nave in " << x1-l << ", " << y1 << "\n";
    }
    if (r)
    {
      std::cout << "Premi r per mettere la nave in " << x1+l << ", " << y1 << "\n";
    }
    std::string direzione;
    std::cin >> direzione;
    if (direzione == "u" && u )
    {
      return Nave(x1,y1,x1,y1-l);
    } else if (direzione == "d" && d)
    {
      return Nave(x1,y1,x1,y1+l);
    } else if (direzione == "l" && le)
    {
      return Nave(x1,y1,x1-l,y1);
    } else if (direzione == "r" && r)
    {
      return Nave(x1,y1,x1+l,y1);
    } else
    {
      std::cout << "not valid \n Prova direzione valida\n";
      return setShips(l,x1,y1);
    }
}



void Player::Mozzo(int i, int lunghezza)
{
  int x,y;
  std::cout << "Inserisci x e y:" << '\n';
  std::cin >> x>>y;
  _navi[i] = setShips(lunghezza,x,y);
}
