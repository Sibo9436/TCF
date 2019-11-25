#ifndef TABELLA_H
#define TABELLA_H
#include "Coordinate.h"
#include "Nave.h"

enum class Flotta
{  // SI possono chiamare solo es. Flotta::Sea
  Sea,
  Ship,
  Near
};

enum class Radar
{
  Hit,
  Miss,
  Sea
};

class Tabella
{
public:
  //Tabella();  //Questo crea radar
  //lTabella();  //Questo crea flotta
  //void Print();
  ~Tabella();
  void PrintRadar();
  void PrintFlotta();
  void createRadar();
  void createFlotta();
  void setNave(int,int,int,int);
  void setNave(Coordinate,Coordinate);
  void setNave(Nave);
  bool getRadar(int, int);
  bool setRadar(int,int,Flotta);
  void setRadar(int,int);
  void Greta();
  Flotta * & operator[](int) const;

private:
  int n=10;
  bool _flottato=false;
  bool _radarato=false;
  Flotta **_flotta;
  Radar **_radar;
};

#endif
