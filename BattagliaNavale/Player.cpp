#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include "Coordinate.h"
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

bool Player::Check(Coordinate c1, Coordinate c2) //controlla se casella di partenza e di arrivo sono compatibili
{

  if (c2.getX() < 0 || c2.getX() > 9)
    return false;
  if (c2.getY() < 0 || c2.getY() > 9)
    return false;
  if (c1.getX()==c2.getX()) {
    int max = (c2.getY() > c1.getY())? c2.getY() : c1.getY();
    int min = (c2.getY() < c1.getY())? c2.getY() : c1.getY();
    for (int i = min; i <=  max; i++)
    {
      if (_Plancia[i][c1.getX()] != Flotta::Sea)
        return false;
    }
    return true;
  } else if (c1.getY()==c2.getY()) {
    int max = (c2.getX() > c1.getX())? c2.getX() : c1.getX();
    int min = (c2.getX() < c1.getX())? c2.getX() : c1.getX();
    for (int i = min; i <= max; i++)
    {
      if (_Plancia[c1.getY()][i] != Flotta::Sea)
        return false;
    }
    return true;
  } else {
    std::cout << "ERRORE IN CHECK(Player.cpp) \n";
    return false;
  }

}



Nave Player::setShips(int len, Coordinate coord){ //crea e pone le navi
    int l = len - 1;
    Coordinate U,D,R,L;
    U = coord + Coordinate(0,-l);
    D = coord + Coordinate(0,+l);
    R = coord + Coordinate(+l,0);
    L = coord + Coordinate(-l,0);

    bool u = Check(coord, U);
    bool d = Check(coord, D);
    bool r = Check(coord, R);
    bool le = Check(coord, L);

    //bool le = Check(x1,y1,x1-l,y1);
    //bool u = Check(x1,y1,x1,y1-l);
    //bool d = Check(x1,y1,x1,y1+l);

    if(!u && !d && !r && !le){
      std::cout << "not valid\n Prova coordinate valide\n";

      Coordinate A;
      A.getFromPlayer();
      return setShips(len,A);


    }
    if (u)
    {
      std::cout << "Premi u per mettere la nave in ";
      U.print();
      std::cout << "\n";

    }
    if (d)
    {
      std::cout << "Premi d per mettere la nave in ";
      D.print();
      std::cout << "\n";
    }
    if (le)
    {
      std::cout << "Premi l per mettere la nave in ";
      L.print();
      std::cout << "\n";
    }
    if (r)
    {
      std::cout << "Premi r per mettere la nave in ";
      R.print();
      std::cout << "\n";
    }
    std::string direzione;
    std::cin >> direzione;
    if (direzione == "u" && u )
    {
      _Plancia.setNave(coord, U);
      return Nave(coord, U);
    } else if (direzione == "d" && d)
    {
      _Plancia.setNave(coord,D);
      return Nave(coord,D);
    } else if (direzione == "l" && le)
    {
      _Plancia.setNave(coord,L);
      return Nave(coord,L);
    } else if (direzione == "r" && r)
    {
      _Plancia.setNave(coord,R);
      return Nave(coord,R);
    } else
    {
      std::cout << "not valid \n Prova direzione valida\n";
      return setShips(len,coord);
    }
}


void Player::Mozzo(int i, int lunghezza) //chiede le coordinate delle navi da creare
{

  Coordinate A;
  if(A.getFromPlayer())
  {
    _navi[i] = setShips(lunghezza, A);
    Print();

  }else
  {
    std::cout << "Qualcosa è andato storto in Mozzo!" << '\n';
  }

}

void Player::Print() //stampa lo schermo di un giocatore
{
  _Plancia.PrintFlotta();
  _Screen.PrintRadar();

}
void Player::Attack(Player &Other) //dichiara un attacco
{
  Coordinate A;

  if(!A.getFromPlayer())
  {
    std::cout << "Coordinate fuori range \n";
    Attack(Other);
  }

  int x = A.getX();
  int y = A.getY();
  if (!_Screen.getRadar(x,y))
  {
    std::cout << "Quadrante già colpito" << '\n';
    Attack(Other);
  }else
  {
    Other.Sunk(x,y);
    Other._Plancia.setRadar(x,y); //Possibilità di fare overload di setradar per non prendere necessariamente flotta
    //Spostiamo Other._Plancia.setRadar in Hit()?
    if(_Screen.setRadar(x,y,Other._Plancia[y][x]))
      colpi_a_segno++;
    colpi_sparati++;

  }
}

//Eliminiamo Player::Hit e mettiamo direttamente il for in Attack?
void Player::Sunk(int x, int y) // Dichiara se l'attacco ha Affondato una nave
{
  Coordinate A(x,y);
  for (int i = 0; i < _n; i++)
  {

    if(_navi[i].Hit(A))
    {
      std::cout << "Affondata nave di "<<_nome << '\n';



      _contatore--;
    }
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
  std::cout << "Inserisci la tua corazzata" << '\n';
  Mozzo(1,4);
  std::cout << "Inserisci i tuoi incrociatori" << '\n';
  Mozzo(2,3);
  Mozzo(3,3);
  std::cout << "Inserisci i tuoi cacciatorpedinieri" << '\n';
  Mozzo(4,2);
  std::string a;
  std::cout << "Premi un tasto qualsiasi" << '\n';
  std::cin >> a;
  _Plancia.Greta();
  std::cout << std::string(100,'\n');

}
void Player::Stats()
{
  std::cout << _nome << ":" << '\n';
  std::cout << "\tNumero di colpi sparati: " << colpi_sparati<< '\n';
  std::cout << "\tNumero di colpi a segno: " << colpi_a_segno<< '\n';
  std::cout << "\tPrecisione: " << 100*(float)colpi_a_segno/(float)colpi_sparati<< "%\n\n\n";
}
