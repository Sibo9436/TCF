//sibo iloveyou
#ifndef COORDINATE_H
#define COORDINATE_H

struct Co
{
  int _x;
  int _y;
};

class Coordinate
{
public:
  Coordinate();
  Coordinate(Co);
  Coordinate(int,int);
  Co getStruct();
  int getX() const;
  int getY() const;
  void setY(int);
  void setX(int);
  bool getFromPlayer(int);
  void  operator=(Coordinate);
  Coordinate operator+(Coordinate);
  int operator-(Coordinate);
  bool operator==(Coordinate)const;
  bool operator!=(Coordinate)const;
  void print()const;

private:
  int _x;
  int _y;
};


#endif
