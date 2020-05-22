#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include "Coordinate.h"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <ctime>
#include <random>

//numeri random
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(0,7);
  std::uniform_int_distribution<int> i_dist(0,3);
  std::uniform_int_distribution<int> CharDist(0,25);
  std::uniform_int_distribution<int> NumDist(0,9);

//---------------------------------------------------------------Comuni a player---------------------------------------
Player::Player()
{
  _Plancia.createFlotta();
  _Plancia.createRadar();
}

std::string Player::getName()
{
  return _nome;
}

bool Player::Check(Coordinate c1, Coordinate c2) //controlla se casella di partenza e di arrivo sono compatibili quando posiziono una nave
{
  int x1 = c1.getX();
  int y1 = c1.getY();
  int x2 = c2.getX();
  int y2 = c2.getY();

  if (x2 < 0 || x2 > _Plancia.getN()-1)
    return false;
  if (y2 < 0 || y2 > _Plancia.getN()-1)
    return false;
  if (x1==x2)
  {
    int max = (y2 > y1)? y2 : y1;
    int min = (y2 < y1)? y2 : y1;
    for (int i = min; i <=  max; i++)
    {
      if (_Plancia[i][x1] != Flotta::Sea)
        return false;
    }
    return true;
  } else if (y1==y2)
  {
    int max = (x2 > x1)? x2 : x1;
    int min = (x2 < x1)? x2 : x1;
    for (int i = min; i <= max; i++)
    {
      if (_Plancia[y1][i] != Flotta::Sea)
        return false;
    }
    return true;
  } else
  {
    std::cout << "ERRORE IN CHECK(Player.cpp) \n";
    return false;
  }
}

int Player::getColpi_sparati()
{
  return colpi_sparati;
}

void Player::PrintRad() //stampa lo schermo di un giocatore senza la flotta
{
  std::cout << "\n\t\t\tCampo nemico\n\n";
  _Plancia.PrintRadar();
}

void Player::PrintFlo() //stampa lo schermo di un giocatore con la flotta
{
  std::cout << "\n\t\t\tLa tua flotta\n\n";
  _Plancia.PrintFlotta();
}

bool Player::Sunk(int x, int y) // Dichiara se l'attacco ha Affondato una nave
{
  Coordinate A(x,y);
  for (int i = 0; i < _n; i++)
  {
    if(_navi[i].Hit(A))
    {
      // std::cout << "Affondata nave di "<<_nome << '\n';
      _funda = _navi[i];

      for (int j = 0; j < _navi[i].getlunghezza(); j++)
      {
        for(int h = (_navi[i])[j].getY()-1; h <= (_navi[i])[j].getY()+1; h++)
        {
          for(int k = (_navi[i])[j].getX()-1; k <= (_navi[i])[j].getX()+1; k++)
          {
            if((h > -1) && (h < _Plancia.getN()) && (k > -1) && (k < _Plancia.getN()) && (_Plancia.getRadar(k,h)))
            {
              _Plancia.setRadar(k,h);
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

void Player::Stats()
{
  std::cout << _nome << ":" << '\n';
  std::cout << "\tNumero di colpi sparati:\t\t" << colpi_sparati << '\n';
  std::cout << "\tNumero di colpi a segno:\t\t" << colpi_a_segno << '\n';
  std::cout << "\tPrecisione:\t\t\t\t" << 100*(float)colpi_a_segno/(float)colpi_sparati << "%\n\n";
  std::cout << "\tNumero di navi nemiche affondate:\t" << navi_affondate << '\n';
  std::cout << "\tNumero di navi superstiti:\t\t" << _contatore << '\n';
}
//--------------------------------------------------------------------Solo Human---------------------------------------
void Human::setName(std::string Nome)
{
  _nome = Nome;
}

Nave Human::setShips(int len, Coordinate coord)//crea e pone le navi
{
    int l = len - 1;
    Coordinate U,D,R,L;
    U = coord + Coordinate(0,-l);
    D = coord + Coordinate(0,+l);
    R = coord + Coordinate(+l,0);
    L = coord + Coordinate(-l,0);

    //stabilisce quali direzioni sono valide
    bool u = Check(coord, U);
    bool d = Check(coord, D);
    bool r = Check(coord, R);
    bool le = Check(coord, L);

    if(!u && !d && !r && !le)
    {
      std::cout << "not valid\n Prova coordinate valide\n";
      std::cin.ignore(10000,'\n');

      Coordinate A;
      A.getFromPlayer(_Plancia.getN());
      return setShips(len,A);
    }

    if (u)
    {
      std::cout << "Premi u per posizionare l'altra estremità della nave in ";
      U.print();
      std::cout << "\n";
    }
    if (d)
    {
      std::cout << "Premi d per posizionare l'altra estremità della nave in ";
      D.print();
      std::cout << "\n";
    }
    if (le)
    {
      std::cout << "Premi l per posizionare l'altra estremità della nave in ";
      L.print();
      std::cout << "\n";
    }
    if (r)
    {
      std::cout << "Premi r per posizionare l'altra estremità della nave in ";
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
    return setShips(len,coord);}

void Human::Mozzo(int i, int lunghezza) //chiede le coordinate delle navi da creare
{
  Coordinate A;
  if(A.getFromPlayer(_Plancia.getN()))
  {
    _navi[i] = setShips(lunghezza, A);
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    PrintFlo();
    std::cout << std::string(12,'\n');

  }else
  {
    std::cout << "Qualcosa è andato storto in Mozzo!" << '\n';
  }

}

void Human::Attack(Player * Other) //dichiara un attacco
{
  Coordinate A;

  if(!A.getFromPlayer(_Plancia.getN()))
  {
    std::cout << "Coordinate fuori range \n";
    Attack(Other);
  }

  int x = A.getX();
  int y = A.getY();
  if (!Other->_Plancia.getRadar(x,y))
  {
    std::cout << "Quadrante già colpito" << '\n';
    Attack(Other);
  }else
  {
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    if(Other->_Plancia.setRadar(x,y)) //Possibilità di fare overload di setradar per non prendere necessariamente flotta
      {
        colpi_a_segno++;
        if(Other->Sunk(x,y))
        {
          std::cout << "Colpita e affondata nave di " << Other->getName() << "!\n";
          navi_affondate++;
        }else
        {
          std::cout << "Colpito!\n";
        }
      }else
      {
        std::cout << "Mancato!\n";
      }
    colpi_sparati++;
  }
}

int Human::getContatore() const //restituisce il numero delle navi sopravvissute
{
  return _contatore;
}

void Human::Riempimento() //Riempie la plancia chiamando mozzo nNavi volte
{
  std::cout << std::string(100,'\n');
  PrintFlo();
  std::cout << std::string(12,'\n');
  std::cout << _nome << ", inizia la fase di creazione...\n"<< '\n';
  std::cout << "Posiziona un'estremità della tua portaerei (5 caselle)" << '\n';
  Mozzo(0,5);
  std::cout << "Posiziona un'estremità della tua corazzata (4 caselle)" << '\n';
  Mozzo(1,4);
  std::cout << "Posiziona un'estremità del tuo primo incrociatore (3 caselle)" << '\n';
  Mozzo(2,3);
  std::cout << "Posiziona un'estremità del tuo secondo incrociatore (3 caselle)" << '\n';
  Mozzo(3,3);
  std::cout << "Posiziona un'estremità del tuo cacciatorpediniere (2 caselle)" << '\n';
  Mozzo(4,2);
  std::string a;
  std::cout << "Premi un tasto qualsiasi e poi invio\n" << '\n';
  std::cin >> a;
  _Plancia.Greta();
  std::cout << std::string(100,'\n');
}

//---------------------------------------------------------------------Solo CPU
void Player::setName()
{
  char a = (char)(CharDist(mt)+65);
  std::string b = std::to_string(NumDist(mt));
  char c = (char)(CharDist(mt)+65);
  std::string d = std::to_string(NumDist(mt));

  _nome += a;
  _nome += b;
  _nome += c;
  _nome += d;
}

Nave Bot::setShips(int len, Coordinate coord)//crea e pone le navi
{

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

void Bot::Print() //stampa lo schermo di un giocatore
{
  std::cout << "\n\t\t\tCampo nemico\n\n";
  // PrintRadar();
  std::cout << "\n\t\t\tLa tua Flotta\n\n";
  _Plancia.PrintFlotta();

}

void Bot::Mozzo(int i, int lunghezza) //chiede le coordinate delle navi da creare
{
  Coordinate A = random();
  _navi[i] = setShips(lunghezza, A);
  //PrintFlo();

}

Coordinate Bot::random() //coordinate random
{

  int x = dist(mt);
  int y = dist(mt);
  Coordinate coord = Coordinate(x,y);

  return coord;

}

void Bot::Attack(Player * Other) //dichiara un attacco
{
  Coordinate A;
  int x, y;
  // std::cout<< " target acquired: " << this->targetAcquired << "\n";
  // "target not acquired"
  if(!this->targetAcquired)
  {
    //srand(time(NULL));
    A = random();
    this->target = A;

    x = A.getX();
    y = A.getY();

    if (!Other->_Plancia.getRadar(x,y))
    {
      // std::cout << "Quadrante già colpito -" << '\n';
      Attack(Other);
    }else
    {
      std::cout << "\n\n" << this->_nome << " attacca in ";
      A.print();
      std::cout <<  "...\n\n";
      if(Other->_Plancia.setRadar(x,y))
      {
        std::cout << "Colpito!\n";
        this->targetAcquired=true;
        this->firstStrike = A;
        this->i = i_dist(mt);
        Other->Sunk(x,y);
        colpi_a_segno ++;
      }else
      {
        std::cout << "Mancato!\n";
      }
       //Possibilità di fare overload di setradar per non prendere necessariamente flotta
      colpi_sparati++;
      //Other->_Plancia.setRadar(x,y);
    }
  }else if(this->targetAcquired)
// "target acquired"
  {
    this->isAcquired = this->target+this->targetDirection[this->i];
    A=this->isAcquired;

    int x = A.getX();
    int y = A.getY();

    if (!Other->_Plancia.getRadar(x,y))
    {
      // std::cout << "Quadrante già colpito in " << x << " " << y << '\n';

      if(this->target==this->firstStrike)
      {
        // std::cout << "target == firstStrike" << "\n";
        // std::cout << "i= " << i << " A: " << "\n";
        this->i = (i+1)%4;
        // std::cout << "i= " << i << " A: " << "\n";
        // A.print();
        // std::cout<< "\n";
      }

      if(this->target!=this->firstStrike)
      {
        this->target=this->firstStrike;
        this->i = (i+2)%4;
        // std::cout << "target != firstStrike" << "\n";
        // std::cout << "i= " << i << " A: " << "\n";
        // A.print();
        // std::cout<< "\n";
      }
      //this->target=this->firstStrike;
      // std::cout << "attack other 450" << "\n";
      Attack(Other);
    }else
    {
      std::cout << "\n\n" << this->_nome << " attacca in ";
      A.print();
      std::cout <<  "...\n\n";
      if(Other->_Plancia.setRadar(x,y))
      {

        this->target = this->isAcquired;

        colpi_a_segno++;

        if(Other->Sunk(x,y))
        {
         this->targetAcquired=false;
         std::cout << "Colpita e affondata nave di " << Other->getName() << "!\n";
         navi_affondate++;
       }else
       {
         std::cout << "Colpito!\n";
       }
      }
      else
      {
        std::cout << "Mancato!\n";
        if(this->target==this->firstStrike)
        {
          // std::cout << "target == firstStrike" << "\n";
          this->i = (i+1)%4;
        }
        if(this->target!=this->firstStrike)
        {
          this->target=this->firstStrike;
          // std::cout << "target != firstStrike" << "\n";

          this->i = (i+2)%4;
        }
      }
      //Other->_Plancia.setRadar(x,y);
      // std::cout << "plancia setradar" << "\n";
      colpi_sparati++;
    }
  }
}

int Bot::getContatore() const //restituisce il numero delle navi sopravvissute
{
  return _contatore;
}

void Bot::Riempimento() //Riempie la plancia chiamando mozzo nNavi volte
{
  std::cout << std::string(100,'\n');
  Mozzo(0,5);
  Mozzo(1,4);
  Mozzo(2,3);
  Mozzo(3,3);
  Mozzo(4,2);
  _Plancia.Greta();
}

//-------------------------------------------------------------------solo Locale---------------------------------

void Locale::PrintRad() //stampa lo schermo di un giocatore senza la flotta
{
  std::cout << "\n\t\t\tCampo nemico\n\n";
  _Screen.PrintRadar();
}

bool Locale::Server()
{
  _Screen.createRadar();

  std::cout << std::string(100,'\n');
  std::cout << "In attesa di uno sfidante...";
  std::cout << std::string(25,'\n');
  int server_fd;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  // char *hello = "Sta funzionando!";
  // char *ciao = "Incredibbbbile!";

  if ((server_fd = socket(AF_INET,SOCK_STREAM, 0)) == 0)
  {
    std::cout << "Socket fallito\n\n";
    return false;
  }

  if (setsockopt(server_fd,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    std::cout << "setsockopt fallito\n\n";
    return false;
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0)
  {
    std::cout << "Bind fallito\n\n";
    return false;
  }
  if (listen(server_fd, 3) < 0 )
  {
    std::cout << "Listen fallito\n\n";
    return false;
  }
  if ((_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
  {
    std::cout << "Connessione fallita\n\n";
    return false;
  }
  struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&address;
  struct in_addr ipAddr = pV4Addr->sin_addr;
  char indie[INET_ADDRSTRLEN];
  inet_ntop( AF_INET, &ipAddr, indie, INET_ADDRSTRLEN );
  std::cout << "Connessione stabilita con " << indie << '\n';
  _isServer=true;
  char * nomino = new char[_nome.size()];
  int l = _nome.size();

  std::copy(_nome.begin(),_nome.end(),nomino);
  send(_socket,&l, sizeof(int),0);
  send(_socket,nomino, sizeof(char)*l,0);
  int l2;
  read(_socket,&l2,sizeof(int));
  char buffer[l2] = {0};
  read(_socket,&buffer,sizeof(char)*l2);
  for (int i = 0; i < l2 ; i++)
  {
    _oppo = _oppo + buffer[i];
  }

  return true;
}

void Locale::sunk(Nave relitto)
{
  for (int j = 0; j < relitto.getlunghezza(); j++)
  {
    for(int h = relitto[j].getY()-1; h <= relitto[j].getY()+1; h++)
    {
      for(int k = relitto[j].getX()-1; k <= relitto[j].getX()+1; k++)
      {
        if((h > -1) && (h < _Screen.getN()) && (k > -1) && (k < _Screen.getN()) && (_Screen.getRadar(k,h)))
        {
          _Screen.setRadar(k, h, Flotta::Sea);
        }
      }
    }
  }
}

bool Locale::Client()
{
  _Screen.createRadar();
  struct sockaddr_in serv_addr;
  char* indirizzo = new char[15];
  std::cout << std::string(100,'\n');
	std::cout << "Digita l'indirizzo a cui connetterti" << '\n';
  std::cout << std::string(25,'\n');
	std::cin >> indirizzo;
  std::cin.ignore(10000,'\n');
  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Errore nella creazione del socket \n");
    return false;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, indirizzo, &serv_addr.sin_addr)<=0)
  {
    printf("\nInvalid address/ Address not supported \n");
    return false;
  }

  if (connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
    return false;
  }
  _isClient = true;
  char * nomino = new char[_nome.size()];
  int l = _nome.size();

  std::copy(_nome.begin(),_nome.end(),nomino);
  send(_socket,&l, sizeof(int),0);
  send(_socket,nomino, sizeof(char)*l,0);
  int l2;
  read(_socket,&l2,sizeof(int));
  char buffer[l2] = {0};
  read(_socket,&buffer,sizeof(char)*l2);
  for (int i = 0; i < l2 ; i++)
  {
    _oppo = _oppo + buffer[i];
  }
  return true;
}

void Locale::Attack()
{
  Coordinate A;

  if(!A.getFromPlayer(_Screen.getN()))
  {
    std::cout << "Coordinate fuori range \n";
    Attack();
  }
  int x = A.getX();
  int y = A.getY();
  if (!_Screen.getRadar(x,y)) //RICORDARSI DI CAMBIARE TABELLA PERCHÉ USI COORDINATE
  {
    std::cout << "Quadrante già colpito" << '\n';
    Attack();
  }else
  {
    std::cout << std::string(100,'\n'); //"aggiorna" schermo
    Co att = A.getStruct();
    send(_socket, &att, sizeof(att), 0);
    int result;
    read(_socket, &result, sizeof(int));
    Flotta colpo = (result == 1 || result == 2 || result == -1)? Flotta::Ship : Flotta::Sea;
    if(_Screen.setRadar(x,y,colpo))
    {
      colpi_a_segno++;
      if (result == 2 || result == -1)
      {
        std::cout << "Colpito e affondato!\n" << '\n';
        Co inizio, fine;
        read(_socket, &inizio, sizeof(inizio));
        read(_socket, &fine, sizeof(fine));
        Nave relitto(inizio, fine);
        sunk(relitto);
        navi_affondate++;
      }else if (result == 1)
      {
        std::cout << "Colpito!\n" << '\n';
      }
    }else
    {
      std::cout << "Mancato!\n" << '\n';
    }
    if (result == -1)
    {
      // std::cout << "Grande Frate Hai VINICIO" << '\n';
      _win = true;
    }
    colpi_sparati++;
  }
}

void Locale::Down()
{
  std::cout << "In attesa di "<< _oppo << "..." << '\n';
  Co subito;
  read(_socket, &subito, sizeof(subito));
  int snd;
  Coordinate Colpo(subito);
  // std::cin.ignore(10000,'\n');
  std::cout << std::string(100,'\n'); //"aggiorna" schermo
  std::cout << _oppo << " spara in ";
  Colpo.print();
  std::cout << "...\n\n";
  if(_Plancia.setRadar(subito._x,subito._y))
  {
    if(Sunk(subito._x,subito._y))
    {
      std::cout << "Colpito e affondato!\n\n";
      snd = 2;
    }else
    {
      std::cout << "Colpito!\n\n";
      snd = 1;
    }
  }else
  {
    std::cout << "Mancato!\n\n";
    snd = 0;
  }
  if (getContatore() == 0)
  {
    snd = -1;
  }
  send(_socket,&snd,sizeof(int),0);
  if (snd == 2 || snd == -1)
  {
    Coordinate prua = _funda[0];
    Coordinate poppa = _funda[_funda.getlunghezza()-1];
    Co testa = prua.getStruct();
    Co coda = poppa.getStruct();
    send(_socket, &testa, sizeof(testa), 0);
    send(_socket, &coda, sizeof(coda), 0);
  }
}

void Locale::Stats()
{
  int mystats[5] = {colpi_sparati, colpi_a_segno, (int)(100*(float)colpi_a_segno/(float)colpi_sparati),navi_affondate,_contatore};
  int hisstats[5]={0};
  send(_socket,&mystats,sizeof(int)*5,0);
  read(_socket, &hisstats,sizeof(int)*5);


  std::cout << _nome << ":" << '\n';
  std::cout << "\tNumero di colpi sparati:\t\t" << mystats[0] << '\n';
  std::cout << "\tNumero di colpi a segno:\t\t" << mystats[1] << '\n';
  std::cout << "\tPrecisione:\t\t\t\t" << mystats[2] << "%\n\n";
  std::cout << "\tNumero di navi nemiche affondate:\t" << mystats[3] << '\n';
  std::cout << "\tNumero di navi superstiti:\t\t" << mystats[4] << '\n';

  std::cout << _oppo << ":" << '\n';
  std::cout << "\tNumero di colpi sparati:\t\t" << hisstats[0] << '\n';
  std::cout << "\tNumero di colpi a segno:\t\t" << hisstats[1] << '\n';
  std::cout << "\tPrecisione:\t\t\t\t" << hisstats[2] << "%\n\n";
  std::cout << "\tNumero di navi nemiche affondate:\t" << hisstats[3] << '\n';
  std::cout << "\tNumero di navi superstiti:\t\t" << hisstats[4] << '\n';

}
