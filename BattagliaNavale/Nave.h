class Nave
{
public:
  Nave();
  Nave(const int, int, int, int, int);
  ~Nave();
  void Hit(int , int );



private:
  int _lunghezza;
  int _contatore;
  bool _affondato;
  int _coordinates[][2];

};
