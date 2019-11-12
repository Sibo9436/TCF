#include "Tabella.h"
#include "Nave.h"
#include "Player.h"
#include <iostream>
//mi sento nel posto sbagliato
//Al momento giusto <3
int main()
{

//
  Player Andrea;

  Player Daniel;

  Andrea.setName("Andrea");
  Daniel.setName("Daniel");

  //
  // Tabella _Plancia;
  // _Plancia.createFlotta();
  //_Plancia.createRadar();

  int i = 0;
  Nave navetta(1,1,1,5);
  Andrea.Mozzo(0,4);
  Andrea.Print();
  while (true)
  {
  Daniel.Attack(Andrea);
  Daniel.Print();
  Andrea.Print();
  }

  // Tabella Plancia;
  // // Plancia.createRadar();
  // // Plancia.createFlotta();
  // //
  // // Tabella Screen;
  // // Screen.createRadar();
  // //
  // // Plancia.PrintFlotta();
  // // std::cout << "\n\n\n\n";
  // // Screen.PrintRadar();
  // //
  // //
  // // const int nNavi = 5;
  // // Nave player1[nNavi];
  // // Nave player2[nNavi];
  // // for (int i = 0; i < 5; i++)
  // // {
  // //   player1[i] = Nave(i,1,0,1,1);
  // //   std::cout << "aaaaaa" << '\n';
  // //   player2[i] = Nave(i,1,0,1,1);
  // //   std::cout << "BBBBBB" << '\n';
  // // }
  //
  // Nave Caccia(1,1,1,3);
  // Caccia.Print();
  // // piro.Hit(1,1);
  // std::cout << "Aiut" << '\n';
  //



  //Screen.PrintFlotta();
  /*
  while()
  {
    while()
    {
    for(int i=0; i<nNavi; i++) player1[i].Hit(x,y);
    }
    while()
    {
    for(int i=0; i<nNavi; i++) player2[i].Hit(x,y);
    }
  }*/
  return 0;
}
