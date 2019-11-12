#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include <iostream>


Player::Player()
{

  _Plancia.createFlotta();
  _Plancia.createRadar();
  _Screen.createRadar();
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

  if (x2 < 0 || x2 > 7)
    return false;
  if (y2 < 0 || y2 > 7)
    return false;
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
    return false;
  }

}



Nave Player::setShips(int len, int x1, int y1){

    int l = len - 1;
    bool r = Check(x1,y1,x1+l,y1);
    bool le = Check(x1,y1,x1-l,y1);
    bool u = Check(x1,y1,x1,y1-l);
    bool d = Check(x1,y1,x1,y1+l);
    if(!u && !d && !r && !le){
      std::cout << "not valid\n Prova coordinate valide\n";
      int x,y;
      std::cin >> x >> y;
      return setShips(len,x,y);
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
      _Plancia.setNave(x1,y1,x1,y1-l);
      return Nave(x1,y1,x1,y1-l);
    } else if (direzione == "d" && d)
    {
      _Plancia.setNave(x1,y1,x1,y1+l);
      return Nave(x1,y1,x1,y1+l);
    } else if (direzione == "l" && le)
    {
      _Plancia.setNave(x1,y1,x1-l,y1);
      return Nave(x1,y1,x1-l,y1);
    } else if (direzione == "r" && r)
    {
      _Plancia.setNave(x1,y1,x1+l,y1);
      return Nave(x1,y1,x1+l,y1);
    } else
    {
      std::cout << "not valid \n Prova direzione valida\n";
      return setShips(len,x1,y1);
    }
}


void Player::Mozzo(int i, int lunghezza)
{
  int x,y;
  std::cout << "Inserisci x e y:" << '\n';
  std::cin >> x>>y;
  _navi[i] = setShips(lunghezza,x,y);
}

void Player::Print()
{
  _Plancia.PrintFlotta();
  _Plancia.PrintRadar();
}
