double K=6.67e-11;

//tutto riferito all'afelio
double massaTerra=5.972e24;
double raggioTerra=6371000;
double distanzaTS=1.521e11;
double velocitaTerra=29300;

double massaLuna=7.342e22;
double raggioLuna=1737100;
double distanzaTL=4.054e8;
double velocitaLuna=964.6;

double massaMercurio=0.33011e24;
double raggioMercurio=2439700;
double distanzaMS=69.82e9;
double velocitaMercurio=38700;

double massaVenere=4.8675e24;
double raggioVenere=6051800;
double distanzaVS=108.94e9;
double velocitaVenere=34790;

double massaMarte=6.4171e23;
double raggioMarte=3396.2e3;
double distanzaMtS=249.23e9;
double velocitaMarte=21.97e3;

double massaGiove=1.898e27;
double raggioGiove=69911e3;
double distanzaGS=816.6e9;
double velocitaGiove=12.44e3;


double massaSole = 1.989e30;
double raggioSole = (1.39095e9)/2.;

//Dist Max
double max=817e9;
//double max=distanzaTL;//*5;

Sfera M = new Sfera(distanzaMS, 0,0,velocitaMercurio, raggioMercurio, massaMercurio,#f0830b);
Sfera V = new Sfera(distanzaVS, 0,0,velocitaVenere, raggioVenere, massaVenere,#ffc0ca);
Sfera T = new Sfera(distanzaTS, 0,0,velocitaTerra, raggioTerra, massaTerra,#64bfd2);
Sfera Mt = new Sfera(distanzaMtS, 0,0,velocitaMarte, raggioMarte, massaMarte,#ff0000);
Sfera J = new Sfera(distanzaGS,0,0,velocitaGiove,raggioGiove,massaGiove,#00ff00);
//EPIC
Sfera T1 = new Sfera(-distanzaTL/5, distanzaTL/9,-3000,0, raggioTerra, massaTerra,#ffc0cb);
Sfera T2 = new Sfera(distanzaTL/3, -distanzaTL/6, 500,200,raggioTerra, massaTerra*10,#ffff00);
Sfera T3 = new Sfera(-distanzaTL/8, -distanzaTL/2,-1000,1000, raggioTerra, massaTerra,#00ffff);
Sfera SUN = new Sfera(0, 0,0,0, raggioSole, massaSole,#ffa500);
//EPICO2
//Sfera T1 = new Sfera(-distanzaTL/4, 0,300,0, raggioTerra, massaTerra,#ffc0cb);
//Sfera T2 = new Sfera(distanzaTL/4, 0, -300,0,raggioTerra, massaTerra,#ffff00);
//Sfera T3 = new Sfera(0, -distanzaTL/4,0,300, raggioTerra, massaTerra,#00ffff);



Sfera L1 = new Sfera(distanzaTL+distanzaTS, 0, 0, 29300+964.6, raggioLuna, massaLuna,#ff00ff);
Sfera L2 = new Sfera(-distanzaTL, 0, 0, -964.6, raggioLuna, massaLuna,#ff00ff);
Sfera L3 = new Sfera(-distanzaTL, 0, 0, -964.6, raggioLuna, massaLuna,#00ff00);



Sfera[] sfere = {M,V,T,SUN,Mt,J};

//Sfera[] sfere = {T1, T2, T3};

int n=6;

//int n=3;

void setup() {


  stroke(255);


  //size(1000,1000,P3D);
  fullScreen(P3D);



  frameRate(30);
}
int cont=0;
void draw() {
    background(0);

  translate(width/2, height/2);
  
  for (int i =0; i < 1000; i++) {
    cont++;
    println(cont);
    for (int l = 0; l < n; l++) {
      
      
      sfere[l].Update();
      sfere[l].Draw(max);
    }

    for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
        if (j != k) {
          sfere[k].Forze(sfere[j]);
        }
      }
    }
  }
}
int m=n;
double c = 3e6;
double D=(pow((float)c,2)*raggioSole)/(2*K);
void mouseClicked(){
  //translate(width/2,height/2);
    double tx = map(mouseX,0,width,-(float)max,(float)max);
    double ty = map(mouseY,0,height,-(float)max,(float)max);
    println(tx,ty);
    Sfera X = new Sfera(tx,ty ,raggioTerra, D,#ffffff);
    Sfera[] temp=sfere;
    sfere = (Sfera[])append(temp,X);
    n++;
 
}
