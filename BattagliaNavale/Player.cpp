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

bool Player::Check(int x1, int y1, int x2, int y2) //controlla se casella di partenza e di arrivo sono compatibili
{

  if (x2 < 0 || x2 > 9)
    return false;
  if (y2 < 0 || y2 > 9)
    return false;
  if (x1==x2) {
    int max = (y2 > y1)? y2 : y1;
    int min = (y2 < y1)? y2 : y1;
    for (int i = min; i <=  max; i++)
    {
      if (_Plancia[i][x1] != Flotta::Sea)
        return false;
    }
    return true;
  } else if (y1==y2) {
    int max = (x2 > x1)? x2 : x1;
    int min = (x2 < x1)? x2 : x1;
    for (int i = min; i <= max; i++)
    {
      if (_Plancia[y1][i] != Flotta::Sea)
        return false;
    }
    return true;
  } else {
    std::cout << "ERRORE IN CHECK(Player.cpp) \n";
    return false;
  }

}



Nave Player::setShips(int len, int x1, int y1){ //crea e pone le navi

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
      std::cout << "Premi u per mettere la nave in " << (char)(x1+65) << ", " << y1-l+1 << "\n";
    }
    if (d)
    {
      std::cout << "Premi d per mettere la nave in " << (char)(x1+65) << ", " << y1+l+1 << "\n";
    }
    if (le)
    {
      std::cout << "Premi l per mettere la nave in " << (char)(x1-l+65) << ", " << y1+1 << "\n";
    }
    if (r)
    {
      std::cout << "Premi r per mettere la nave in " << (char)(x1+l+65) << ", " << y1+1 << "\n";
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


void Player::Mozzo(int i, int lunghezza) //chiede le coordinate delle navi da creare
{
  char k;
  int y;
  bool err;
  do
  {
    std::cout << "Inserisci x e y (es A 5):" << '\n';
    std::cin >> k >> y;
    if(std::cin.fail())
    {
      std::cout << "Inserimento non valido\n Ritenta\n";
      err = !std::cin.fail();
      std::cin.clear();
    }else
    {
      err = true;
    }
  }while(!err);
  y--;
  int x = (int)k -65;

  if((x<0 || y < 0 )||(x >9 || y > 9))
  {
    std::cout << "Coordinate fuori range \n";
    Mozzo(i, lunghezza);

  }else
  {
  _navi[i] = setShips(lunghezza,x,y);
  Print();
  }

}

void Player::Print() //stampa lo schermo di un giocatore
{
  _Plancia.PrintFlotta();
  _Screen.PrintRadar();

}
void Player::Attack(Player &Other) //dichiara un attacco
{
  int x, y;
  std::cout << "Coordinate di attacco (x,y): ";
  std::cin >> x >> y;
  if((x>9 || y>9) || (x < 0 || y <0))
  {
    std::cout << "Coordinate fuori range \n";
    Attack(Other);
  }
  if (!_Screen.getRadar(x,y))
  {
    std::cout << "Quadrante già colpito" << '\n';
    Attack(Other);
  }else
  {
    Other.Hit(x,y);
    Other._Plancia.setRadar(x,y,Other._Plancia[y][x]); //Possibilità di fare overload di setradar per non prendere necessariamente flotta
    //Spostiamo Other._Plancia.setRadar in Hit()?
    _Screen.setRadar(x,y,Other._Plancia[y][x]);

  }
}

//Eliminiamo Player::Hit e mettiamo direttamente il for in Attack?
void Player::Hit(int x, int y) // Dichiara se l'attacco ha Affondato una nave
{
  for (int i = 0; i < _n; i++)
  {
    if(_navi[i].Hit(x,y))
      std::cout << "AFFONDATO" << '\n';;
  }
}


int Player::getContatore() const //restituisce il numero delle navi sopravvissute
{
  return _contatore;
}

void Player::Riempimento() //Riempie la plancia chiamando mozzo nNavi volte
{
  std::cout << _nome << ", inizia la fase di creazione..."<< '\n';
  std::cout << "Inserisci la tua portaerei" << '\n';
  Mozzo(0,5);
  std::cout << "Inserisci le tue corazzate" << '\n';
  Mozzo(1,4);
  Mozzo(2,4);
  std::cout << "Inserisci i tuoi incrociatori" << '\n';
  Mozzo(3,3);
  Mozzo(4,3);
  Mozzo(5,3);
  std::cout << "Inserisci i tuoi cacciatorpedinieri" << '\n';
  for (int i =6 ; i < 10; i++)
  {
    Mozzo(i,2);
  }
  std::string a;
  std::cout << "Premi un tasto qualsiasi" << '\n';
  std::cin >> a;
  std::cout << std::string(100,'\n');

}
