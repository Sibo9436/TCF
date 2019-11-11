#ifndef TABELLA_H
#define TABELLA_H

enum class Flotta
{  // SI possono chiamare solo es. Flotta::Sea
  Sea,
  Ship
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
  ~Tabella();
  void PrintRadar();
  void PrintFlotta();
  //void Print();
  void createRadar();
  void createFlotta();

private:
  int n=8;
  bool _flottato=false;
  Flotta **_flotta;
  Radar **_radar;


};


#endif
