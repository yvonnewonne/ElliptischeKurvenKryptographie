#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Fp{
  // Klasse, die Elemente aus Fp verwaltet
  private:
  long long p=5;
  long long n=0;

  public:
  // Konstruktoren
  Fp(long long n_, long long p_){
    p=p_; // überprüft nicht, ob p Primzahl ist!
    n=n_%p;
    if(n<0){
      n=n+p;
    }
  }

  Fp(){
    p=5;
    n=0;
  }

  // Operatoren 
  Fp operator + (const Fp& m) const{
    if(p != m.getP()){
        throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
    }
    return Fp(n+m.getN(), p);
  }

  Fp operator - (const Fp& m) const{
    if(p != m.getP()){
        throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
    }
    return Fp(n-m.getN(),p);
  }

  Fp operator * (const Fp& m) const{
    if(p != m.getP()){
      throw invalid_argument(" n und m sind in verschiedenen Körpern (unterschiedliches p)");
    }
    return Fp((n%p)*(m.getN()%p),p);
  }

  bool operator == (const Fp& m) const {
    if(p != m.getP()){
        throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
    }
    return (((n-m.getN())%p)==0);
  }

  bool operator != (const Fp& m) const {
    return (!(*this==m));
  }

  Fp operator - () const{
    return Fp(-n,p);  
  }

  Fp operator ^ (const long long& k) const{
    long long res=1;
    long long base=n%p;
    long long exp=k%(p-1);
    if(k<0){ 
      exp=exp+(p-1);
    }
    while(exp>0){
      if(exp%2==1){
        res = (res*base)%p;
      }
      exp = exp >> 1;
      base = (base*base)%p;
    }
    return Fp(res,p);
  }
  
  Fp operator / (const Fp& b) const{
    if(p != b.getP()){
        throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
    } 
    return (*this)*(b^-1);
  }


  // Eulers Kriterium, überprüft, ob das ein Quadrat ist
  bool quadRes(){
    Fp l=*this^((p-1)/2);
    Fp k=Fp(1,p);
    if( (*this^((p-1)/2))== Fp(1,p) ){
        return true;
    } else if((*this^((p-1)/2))== Fp(-1,p)){
        return false;
    } else { //den Fall sollte es nicht geben
        std::cout << "Eulers Kriterium ergibt fuer "<<stringify()<<" "<< (*this^((p-1)/2)).stringify()<<". "<< "\n";
        return false;
    }
  }

  // get-Funktionen
  long long getN() const{
    return n;
  }
  long long getP() const{
    return p;
  }

  // toString-Funktionen
  string stringify() {
    return to_string(n);
  }
};