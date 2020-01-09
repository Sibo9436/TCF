//sibo iloveyou
#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
  Coordinate();
  Coordinate(int,int);
  int getX() const;
  int getY() const;
  void setY(int);
  void setX(int);
  bool getFromPlayer();
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
