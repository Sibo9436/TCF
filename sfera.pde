double G=6.67e-11;
void Elastico(Sfera Uno, Sfera Due){
  
  double vf1x = ((Uno.getm()-Due.getm())*Uno.getvx() + 2*Due.getm()*Due.getvx())/(Uno.getm()+Due.getm());
  double vf1y = ((Uno.getm()-Due.getm())*Uno.getvy() + 2*Due.getm()*Due.getvy())/(Uno.getm()+Due.getm());
  
  double vf2x = ((Due.getm()-Uno.getm())*Due.getvx() + 2*Uno.getm()*Uno.getvx())/(Uno.getm()+Due.getm());
  double vf2y = ((Due.getm()-Uno.getm())*Due.getvy() + 2*Uno.getm()*Uno.getvy())/(Uno.getm()+Due.getm());

  Uno.setvx(vf1x);
  Uno.setvy(vf1y);
  Due.setvx(vf2x);  
  Due.setvy(vf2y);
}

int con=0;

class Sfera{
  
  double x,y,vx,vy,ax,ay,r,m;
  int over = 0;
  color c;
  Sfera( double posx, double posy,double radius, double massa,color colore){
  x = posx;
  y = posy;
  r=radius;
  m = massa;
  c = colore;
  
}  
  Sfera( double posx,  double posy,  double velx,  double vely, 
double radius, double
massa,color colore){
  x = posx;
  y = posy;
  r=radius;
  m = massa;
  vx = velx;
  vy = vely;
  c = colore;

}
  void setvx(double VX){vx=VX;}
  void setvy(double VY){vy=VY;}
  double getx(){return x;}
  double gety(){return y;}
  double getvx(){return vx;}
  double getvy(){return vy;}
  
  double getr(){return r;}
  double getm(){return m;}
  double dist(Sfera Other){
    double distx =x-Other.getx();
    double disty = y -Other.gety();
    double dist = sqrt(pow((float)distx,2.)+pow((float)disty,2.));
    return dist;
  }
  boolean Overlap(Sfera Other){
    double dista = dist(Other);
    
    if (dista > r+Other.getr()) return false;
    //println( "Overlap");
    return true;
  }
  void Forze(Sfera Other){
    if (!Overlap(Other) ){
  double distx = Other.getx() - x ;
  double disty = Other.gety() - y ;
  double dist = sqrt(pow((float)distx,2.)+pow((float)disty,2.));
  double forza = G*m*Other.getm()/pow((float)dist,2.);

  double sint = distx/dist;
  double cost = disty/dist;
  double fx = forza*sint;
  double fy = forza*cost;
  ax += fx/m;
  ay += fy/m;
  

   }else if(con-over==0){
      con++;
      over++;
      Elastico(this,Other);

      
    }else {
          
          ax += 0;
          ay += 0;
      
  }
  }
void Update(){

    x += vx;
    y += vy;
    vx += ax;
    vy += ay;
    ax = 0;
    ay = 0;
 
    }
void Draw(double max){
  double mx;
  double my;
  double mr;
  mx = map((float)x,-(float)max,(float)max,-height/2,height/2);
  my = map((float)y,-(float)max,(float)max,-height/2,height/2);
  mr = map((float)r,0,(float)max,0,height/2);
 
  //stroke(255);
  //strokeWeight(3);
  //vertex(mx,my);
  stroke(c);
 
  strokeWeight(5);
  fill(0);
  
  //circle(mx,my,mr);
  ellipse((float)mx,(float)my,(float)mr,(float)mr);
  

  //line(mx,my,mx+10*ax,my+10*ay);
  
}
  
};
