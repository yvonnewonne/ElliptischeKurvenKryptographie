#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Server.cpp"
using namespace std;

// Klasse zum verwalten der benachbarten Kurve
class Neighbour{
  private:
    long long p; // kleine Primzahld, die Ordnung der Kurve teilt
    bool hasEC; //speichert, ob schon ein bi gefunden wurde
    EllipticFunction E= EllipticFunction(Fp(0,11),Fp(7,11),11);
    long long order=0; // Ordnung der benachbarten Kurve
    Point G=Point(true,11); //Erzeuger Untergruppe
    long long s=0; // speichert s² mod p

  public:
  // Konstruktor
  Neighbour(long long p_){
    p=p_;
    E = EllipticFunction(Fp(0,11),Fp(7,11),11);
    hasEC = false;
    order = 0;
    s = 0;
    G=Point(true,p);
  }

  // set-Funktionen
  void setEC(EllipticFunction E_, long long order_){
    E=E_;
    order=order_;
    hasEC=true;
  }

  void setG(Point G_){
    G=G_;
  }

  void setS(long long s_){
    s=s_;
  }

  // get-Funktionen
  long long getP(){
    return p;
  }

  EllipticFunction getEC(){
    return E;
  }

  long long getOrder(){
    return order;
  }

  Point getG(){
    return G;
  }

  long long getS(){
    return s;
  }

  bool hasE(){
    return(hasEC);
  }
};