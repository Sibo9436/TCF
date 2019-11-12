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
  void setNave(int,int,int,int);

  Flotta * & operator[](int) const;

private:
  int n=8;
  bool _flottato=false;
  bool _radarato=false;
  Flotta **_flotta;
  Radar **_radar;


};


#endif
