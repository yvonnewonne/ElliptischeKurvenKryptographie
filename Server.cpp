#include <iostream>
#include <cmath>
#include <string>
#include "EllipticFunction.cpp"
using namespace std;

class Server{
  private:
    EllipticFunction E = EllipticFunction(Fp(0,11), Fp(7,11));
    long long s; // privater Schlüssel des Servers
    Point PMS=Point(Fp(0,5),Fp(0,5)); // Premaster-Secret

  public:
  // Konstruktoren
  Server(){
    E = EllipticFunction(Fp(0,11), Fp(7,11));
    s = 2;
  }

  Server(EllipticFunction E_, long long s_){
      E=E_;
      s=s_; 
  }

  // Handshake Simulation
  void Hello(){ //ist nur für Ausgabe
    std::cout<<"\n Server-HELLO: Der Server verschlüsselt mit der Kurve "<<E.stringify();
  }

  void KeyExchange(Point aQ){
    std::cout<<"\n Key-Exchange: Der Server bekommt Punkt "<<aQ.stringify()<<" übergeben.";
    PMS=E.mult(s,aQ);
  }

  bool Finished(Point G){
    if(G.isInf() && PMS.isInf()){
      std::cout<<"\n Server-FINISHED ";
      return true;
    } else if(G.isInf() || PMS.isInf()){
      return false;
    } else if(G.getX()==PMS.getX()){
      //std::cout<<"\n Server-FINISHED \n";
      return true;
    } 
    return false;
  }
};