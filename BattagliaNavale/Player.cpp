#include "Player.h"
#include "Tabella.h"
#include "Nave.h"
#include "Coordinate.h"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


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
  std::cout << "\n\t\t\tCampo nemico\n\n";
  _Screen.PrintRadar();
  std::cout << "\n\t\t\tLa tua Flotta\n\n";
  _Plancia.PrintFlotta();

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
    Other._Plancia.setRadar(x,y); //Possibilità di fare overload di setradar per non prendere necessariamente flotta
    Other.Sunk(x,y);
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
      _funda = true;

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
    }
  }
}


int Player::getContatore() const //restituisce il numero delle navi sopravvissute
{
  return _contatore;
}

void Player::Riempimento() //Riempie la plancia chiamando mozzo nNavi volte
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

void Player::Stats()
{
  std::cout << _nome << ":" << '\n';
  std::cout << "\tNumero di colpi sparati: " << colpi_sparati<< '\n';
  std::cout << "\tNumero di colpi a segno: " << colpi_a_segno<< '\n';
  std::cout << "\tPrecisione: " << 100*(float)colpi_a_segno/(float)colpi_sparati<< "%\n\n\n";
}



void Player::Server()
{
  std::cout << "Inizializzazione server side" << '\n';
  int server_fd;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  char *hello = "Sta funzionando!";
  char *ciao = "Incredibbbbile!";

  if ((server_fd = socket(AF_INET,SOCK_STREAM, 0)) == 0)
  {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(server_fd,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsockopt fallito");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0)
  {
    perror("Bind fallito");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0 )
  {
    perror("Listen fallito");
    exit(EXIT_FAILURE);
  }
  if ((_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
  {
      perror("accept");
      exit(EXIT_FAILURE);
  }
  struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&address;
  struct in_addr ipAddr = pV4Addr->sin_addr;
  char indie[INET_ADDRSTRLEN];
  inet_ntop( AF_INET, &ipAddr, indie, INET_ADDRSTRLEN );
  std::cout << "Connessione stabilita con " << indie << '\n';
  _isServer=true;


}
void Player::Client()
{
  std::cout << "AAAAAAAAAAAAAA" << '\n';
  struct sockaddr_in serv_addr;
  char buffer[1024] = {0};
  char* indirizzo = new char[15];
	std::cout << "Digita l'indirizzo a cui connetterti" << '\n';
	std::cin >> indirizzo;
  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Errore nella creazione del socket \n");
    return;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, indirizzo, &serv_addr.sin_addr)<=0)
  {
    printf("\nInvalid address/ Address not supported \n");
    return;
  }

  if (connect(_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
    return;
  }
  _isClient = true;
}

void Player::Attack()
{

  Coordinate A;
  int valread;
  if(!A.getFromPlayer())
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

    Co att = A.getStruct();
    send(_socket, &att, sizeof(att),0);
    int result;
    valread = read(_socket, &result,sizeof(int));
    if (result == -1)
    {
      std::cout << "Grande Frate Hai VINICIO" << '\n';
      _win = true;
    }else if (result == 2)
    {
      std::cout << "Hai affondato una nave nemica" << '\n';
      result = 1;
    }
    //RICORDARSI DI METTERLA IN DOWN
    // Other._Plancia.setRadar(x,y); //Possibilità di fare overload di setradar per non prendere necessariamente flotta
    // Other.Sunk(x,y);
    //Spostiamo Other._Plancia.setRadar in Hit()?

    Flotta colpo = (result == 1)? Flotta::Ship : Flotta::Sea;
    if(_Screen.setRadar(x,y,colpo))
      colpi_a_segno++;
    colpi_sparati++;
    Print();
  }
}
void Player::Down()
{
  std::cout << "Turno del giocatore avverso" << '\n';
  Co subito;
  int valread = read(_socket,&subito, sizeof(subito));
  int snd;
  std::cout << subito._x << "," << subito._y << '\n';
  _Plancia.setRadar(subito._x,subito._y);
  Sunk(subito._x,subito._y);
  snd = (_Plancia[subito._y][subito._x]==Flotta::Ship)? 1 : 0;
  if (_funda)
  {
    snd = 2;
    _funda = false;
  }
  if (getContatore() == 0)
  {
    snd = -1;
    send(_socket,&snd,sizeof(int),0);
    return;
  }
  send(_socket,&snd,sizeof(int),0);
  Print();
}
