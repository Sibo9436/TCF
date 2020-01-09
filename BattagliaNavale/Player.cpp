#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include "Coordinate.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(0,9);
  std::uniform_int_distribution<int> i_dist(0,3);

//---------------------------------------------------------------Comuni a player
Player::Player()
{
  //srand(time(NULL));
  _Plancia.createFlotta();
  _Plancia.createRadar();
  _Screen.createRadar();
}

void Player::Stats()
{
  std::cout << _nome << ":" << '\n';
  std::cout << "\tNumero di colpi sparati: " << colpi_sparati<< '\n';
  std::cout << "\tNumero di colpi a segno: " << colpi_a_segno<< '\n';
  std::cout << "\tPrecisione: " << 100*(float)colpi_a_segno/(float)colpi_sparati<< "%\n\n\n";
}

std::string Player::getName()
{
  return _nome;
}

bool Player::Check(Coordinate c1, Coordinate c2) //controlla se casella di partenza e di arrivo sono compatibili
{
  if (c2.getX() < 0 || c2.getX() > 9)
  return false;
  if (c2.getY() < 0 || c2.getY() > 9)
  return false;
  if (c1.getX()==c2.getX())
  {
    int max = (c2.getY() > c1.getY())? c2.getY() : c1.getY();
    int min = (c2.getY() < c1.getY())? c2.getY() : c1.getY();
    for (int i = min; i <=  max; i++)
    {
      if (_Plancia[i][c1.getX()] != Flotta::Sea)
      return false;
    }
    return true;
  } else if (c1.getY()==c2.getY())
  {
    int max = (c2.getX() > c1.getX())? c2.getX() : c1.getX();
    int min = (c2.getX() < c1.getX())? c2.getX() : c1.getX();
    for (int i = min; i <= max; i++)
    {
      if (_Plancia[c1.getY()][i] != Flotta::Sea)
      return false;
    }
    return true;
  } else
  {
    std::cout << "ERRORE IN CHECK(Player.cpp) \n";
    return false;
  }

}

//-------------------------------------------------------------------Solo Human
void Human::setName(std::string Nome)
{
  _nome = Nome;
}


Nave Human::setShips(int len, Coordinate coord){ //crea e pone le navi
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

    if(!u && !d && !r && !le)
    {
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
    char direzione;
    std::cin >> direzione;
    std::cin.ignore(10000,'\n');
    if (direzione == 'u' && u)
    {
      _Plancia.setNave(coord, U);
      return Nave(coord, U);
    }
    if (direzione == 'd' && d)
    {
      _Plancia.setNave(coord, D);
      return Nave(coord, D);
    }
    if (direzione == 'l' && le)
    {
      _Plancia.setNave(coord, L);
      return Nave(coord, L);
    }
    if (direzione == 'r' && r)
    {
      _Plancia.setNave(coord, R);
      return Nave(coord, R);
    }
    std::cout << "not valid \n Prova direzione valida\n";
    return setShips(len,coord);
}

void Human::Mozzo(int i, int lunghezza) //chiede le coordinate delle navi da creare
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

void Human::Print() //stampa lo schermo di un giocatore
{
  std::cout << "\n\t\t\tCampo nemico\n\n";
  _Screen.PrintRadar();
  std::cout << "\n\t\t\tLa tua Flotta\n\n";
  _Plancia.PrintFlotta();

}

void Human::Attack(Player * Other) //dichiara un attacco
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
    Other->_Plancia.setRadar(x,y); //Possibilità di fare overload di setradar per non prendere necessariamente flotta
    Other->Sunk(x,y);
    //Spostiamo Other._Plancia.setRadar in Hit()?
    if(_Screen.setRadar(x,y,Other->_Plancia[y][x]))
      colpi_a_segno++;
    colpi_sparati++;
  }
}

//Eliminiamo Player::Hit e mettiamo direttamente il for in Attack?
bool Human::Sunk(int x, int y) // Dichiara se l'attacco ha Affondato una nave
{
  Coordinate A(x,y);
  for (int i = 0; i < _n; i++)
  {
    if(_navi[i].Hit(A))
    {
      std::cout << "Affondata nave di "<<_nome << '\n';

      for (int j = 0; j < _navi[i].getlunghezza(); j++)
      {
        for(int h = (_navi[i])[j].getY()-1; h <= (_navi[i])[j].getY()+1; h++)
        {
          for(int k = (_navi[i])[j].getX()-1; k <= (_navi[i])[j].getX()+1; k++)
          {
            if((h > -1) && (h < 10) && (k > -1) && (k < 10) && (_Plancia[h][k] != Flotta::Ship))
            {
              std::cout << "se funzionassi metterei @ in " << h << " " << k << "\n";
            }
          }
        }
      }
      _contatore--;
      return true;
    }
  }
  return false;
}


int Human::getContatore() const //restituisce il numero delle navi sopravvissute
{
  return _contatore;
}

void Human::Riempimento() //Riempie la plancia chiamando mozzo nNavi volte
{
  std::cout << std::string(100,'\n');
  std::cout << _nome << ", inizia la fase di creazione..."<< '\n';
  std::cout << "Inserisci la tua portaerei" << '\n';
  Mozzo(0,5);
  std::cout << "Inserisci la tua corazzata" << '\n';
  Mozzo(1,4);
  std::cout << "Inserisci i tuoi incrociatori" << '\n';
  Mozzo(2,3);
  Mozzo(3,3);
  std::cout << "Inserisci il tuo cacciatorpediniere" << '\n';
  Mozzo(4,2);
  std::string a;
  std::cout << "Premi un tasto qualsiasi" << '\n';
  std::cin >> a;
  _Plancia.Greta();
  std::cout << std::string(100,'\n');
}

//---------------------------------------------------------------------Solo CPU
void Bot::setName(std::string Nome)
{
  _nome = "R2D2";
}

Nave Bot::setShips(int len, Coordinate coord){ //crea e pone le navi

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

    if(!u && !d && !r && !le)
    {
      Coordinate A = random();
      return setShips(len,A);
    }

    int direzione = i_dist(mt);

    if (direzione == 0 && u)
    {
      _Plancia.setNave(coord, U);
      return Nave(coord, U);
    }
    if (direzione == 1 && d)
    {
      _Plancia.setNave(coord, D);
      return Nave(coord, D);
    }
    if (direzione == 2 && le)
    {
      _Plancia.setNave(coord, L);
      return Nave(coord, L);
    }
    if (direzione == 3 && r)
    {
      _Plancia.setNave(coord, R);
      return Nave(coord, R);
    }
    return setShips(len,coord);
}

void Bot::Mozzo(int i, int lunghezza) //chiede le coordinate delle navi da creare
{
  Coordinate A = random();
  _navi[i] = setShips(lunghezza, A);
  Print();

}

void Bot::Print() //stampa lo schermo di un giocatore
{
  std::cout << "\n\t\t\tCampo nemico\n\n";
  _Screen.PrintRadar();
  std::cout << "\n\t\t\tLa tua Flotta\n\n";
  _Plancia.PrintFlotta();

}

Coordinate Bot::random()
{

  int x = dist(mt);
  int y = dist(mt);
  Coordinate coord = Coordinate(x,y);

  return coord;

}

void Bot::Attack(Player * Other) //dichiara un attacco
{
  Coordinate A;
  std::cout<< " target acquired: " << this->targetAcquired << "\n";
  // "target not acquired"
  if(!this->targetAcquired){
    //srand(time(NULL));
    A = random();
    this->target = A;

    int x = A.getX();
    int y = A.getY();

    if (!_Screen.getRadar(x,y))
    {
      std::cout << "Quadrante già colpito -" << '\n';
      Attack(Other);
    }

    else

    {
      if(_Screen.setRadar(x,y,Other->_Plancia[y][x])){
       this->targetAcquired=true;
       this->firstStrike = A;
       this->i = i_dist(mt);
      }; //Possibilità di fare overload di setradar per non prendere necessariamente flotta


      colpi_sparati++;
      Other->_Plancia.setRadar(x,y);
      Other->Sunk(x,y);

    }
  }

else

{
// "target acquired"
  if(this->targetAcquired){

    this->isAcquired = this->target+this->targetDirection[this->i];
    A=this->isAcquired;

    int x = A.getX();
    int y = A.getY();

    if (!_Screen.getRadar(x,y))
    {
      std::cout << "Quadrante già colpito in " << x << " " << y << '\n';

      if(this->target==this->firstStrike){
        std::cout << "target == firstStrike" << "\n";
        std::cout << "i= " << i << " A: " << "\n";
        this->i = (i+1)%4;
        std::cout << "i= " << i << " A: " << "\n";
        A.print();
        std::cout<< "\n";
      }

      if(this->target!=this->firstStrike){
        this->target=this->firstStrike;
        this->i = (i+2)%4;
        std::cout << "target != firstStrike" << "\n";
        std::cout << "i= " << i << " A: " << "\n";
        A.print();
        std::cout<< "\n";

      }

      //this->target=this->firstStrike;

      std::cout << "attack other 450" << "\n";
      Attack(Other);
    }

    else

    {
      if(_Screen.setRadar(x,y,Other->_Plancia[y][x])){
        std::cout << "screen setRadar" << "\n";

       this->target = this->isAcquired;

       colpi_a_segno++;

       if(Other->Sunk(x,y))
       {
         this->targetAcquired=false;
         std::cout << "sunk" << "\n";
       };
      }
      else
      {
        if(this->target==this->firstStrike){
          std::cout << "target == firstStrike" << "\n";
          this->i = (i+1)%4;
        }
        if(this->target!=this->firstStrike){
          this->target=this->firstStrike;
          std::cout << "target != firstStrike" << "\n";

          this->i = (i+2)%4;
        }

      }

      Other->_Plancia.setRadar(x,y);
      std::cout << "plancia setradar" << "\n";
      colpi_sparati++;


  }

    //Spostiamo Other._Plancia.setRadar in Hit()?

  }
 }
}



bool Bot::Sunk(int x, int y) // Dichiara se l'attacco ha Affondato una nave
{
  Coordinate A(x,y);
  for (int i = 0; i < _n; i++)
  {
    if(_navi[i].Hit(A))
    {
      std::cout << "Affondata nave di "<<_nome << '\n';

      for (int j = 0; j < _navi[i].getlunghezza(); j++)
      {
        for(int h = (_navi[i])[j].getY()-1; h <= (_navi[i])[j].getY()+1; h++)
        {
          for(int k = (_navi[i])[j].getX()-1; k <= (_navi[i])[j].getX()+1; k++)
          {
            if((h > -1) && (h < 10) && (k > -1) && (k < 10) && (_Plancia[h][k] != Flotta::Ship))
            {
              std::cout << "se funzionassi metterei @ in " << h << " " << k << "\n";
            }
          }
        }
      }
      _contatore--;
      return true;
    }
  }
  return false;
}



int Bot::getContatore() const //restituisce il numero delle navi sopravvissute
{
  return _contatore;
}

void Bot::Riempimento() //Riempie la plancia chiamando mozzo nNavi volte
{
  std::cout << std::string(100,'\n');
  std::cout << _nome << ", inizia la fase di creazione..."<< '\n';
  std::cout << "Inserisci la tua portaerei" << '\n';
  Mozzo(0,5);
  std::cout << "Inserisci la tua corazzata" << '\n';
  Mozzo(1,4);
  std::cout << "Inserisci i tuoi incrociatori" << '\n';
  Mozzo(2,3);
  Mozzo(3,3);
  std::cout << "Inserisci il tuo cacciatorpediniere" << '\n';
  Mozzo(4,2);
  std::string a;
  std::cout << "Premi un tasto qualsiasi" << '\n';
  std::cin >> a;
  _Plancia.Greta();
  std::cout << std::string(100,'\n');
}
