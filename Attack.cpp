#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Neighbour.cpp"
#include "Arithmetic.cpp"
using namespace std;

// Funktion zur Generierung von Primzahlen mit dem Sieb des Eratosthenes
std::vector<long long> sieveOfEratosthenes(long long max) {
    std::vector<bool> is_prime(max + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i * i <= max; ++i) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= max; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<long long> primes;
    for (long long i = 2; i <= max; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// Funktion zum Berechnen der ersten n Primzahlen, deren Produkt größer als p² ist
std::vector<Neighbour> generatePrimes(long long p) {
    long long target = p * p;
    std::vector<long long> primes = sieveOfEratosthenes(p);

    std::vector<Neighbour> result;
    long long product = 1;

    for (long long prime : primes) {
        result.push_back(Neighbour(prime));
        product *= prime;
        if (product > target) {
          std::cout<<", max(p_i)="<<prime<<" ";
            break;
        }
    }
    return result;
}


class Attack{
  private:
    EllipticFunction E = EllipticFunction(Fp(0,11),Fp(7,11),11);
    long long p; // Körper Fp
    long long order; // #E
    Server server=Server(EllipticFunction(Fp(0,11),Fp(7,11),11), 3);
    std::vector<Neighbour> neighbours; // Vektor aller Nachbarn
    long long secret; //ermitteltes s²


  public:
  // Konstruktor (führt bereits den Precomputing-Teil des Angriffs auf den Server aus)
  Attack(EllipticFunction E_){
    E = E_;
    Fp a = E.getA();
    Fp b = E.getB();
    p = a.getP();
    // Bestimmen der Primzahlen
    order=E.order();
    std::cout<<"#E="<<to_string(order)<<" ";
    neighbours = generatePrimes(order);
    long long n = neighbours.size();
    long long count=0;
    // Bestimmen der benachbarten Kurven und deren Ordnung
    for (long long i=0; i<p; i++){
      Fp b_ = Fp(i,p);
      if(!(b==b_)){
      if(!(((Fp(4,p)*(a^3)) + (Fp(27,p)*(b_^2))) == Fp(0,p))){
        EllipticFunction EN = EllipticFunction(a, b_);
        long long o = EN.order();
        for(Neighbour& neighbour : neighbours){
          if(!(neighbour.hasE())){
            if(o%neighbour.getP()==0){
              neighbour.setEC(EN, o);
              count++;
              if(count==n){
                std::cout<<", max(b_i)="<<to_string(i);
                goto done; // alle Primzahlen haben eine zug. benachbarte Kurve
              }
            }
          }
        }
      } 
      } 
    }
  done:
  // Bestimmen von Erzeugern der benachbarten Kurven
  for(Neighbour& neighbour : neighbours){
    EllipticFunction E=neighbour.getEC();
    long long p=neighbour.getP();
    std::vector<Point> points = E.generatePoints();
    for(Point& point : points){
      if(E.mult(p,point)==Point(true,p)){
        neighbour.setG(point);
        break;
      }
    }
  }
  secret=0; //können wir erst nach Interaktion mit dem Server bestimmen
  }

  // zweiter Teil des Angriffs 
  long long attackServer(Server server){
    std::vector<long long> reste;
    std::vector<long long> modis;
    // bestimme durch Handshake für jede Untergruppe mit Erzeuger G, s mod |<G>| 
    for(Neighbour& neighbour : neighbours){
      Point G= neighbour.getG();
      long long p_=neighbour.getP();
      EllipticFunction E_=neighbour.getEC();
      server.Hello();
      server.KeyExchange(G);
      for ( long long i =1; i < p_; i++){
        Point PMS_=E.mult(i,G);
        if (server.Finished(PMS_)){
          neighbour.setS((i*i)%p_);
          break;
        }
      }
      reste.push_back(neighbour.getS());
      modis.push_back(neighbour.getP());
    }
    // Chinesischer Restsatz
    secret= Arithmetic::CRS(reste, modis);
    return secret;
  }

  // toString-Funktionen
  string stringify(){
    string a_s=E.getA().stringify();
    string res=".\n\n Wir greifen an mit den folgenden benachbarten Kurven:\n";
    long long count=1;
    for (Neighbour neighbour : neighbours){
      res += to_string(count)+": p="+to_string(neighbour.getP())+", Kurve y²=x³+"+a_s+"x+"+neighbour.getEC().getB().stringify()+" mit Ordnung "+to_string(neighbour.getOrder())+" und Erzeuger der Untergruppe "+ neighbour.getG().stringify()+" -> s² mod "+to_string(neighbour.getP())+"= "+to_string(neighbour.getS())+".\n";
      count++;
    }
    res +="\nDer quadrierte private Schlüssel des Servers ist s²="+to_string(secret)+", somit ist |s|="+to_string(static_cast<long long>(std::floor(sqrt(secret))))+"!\n";
    return res;
  }

  string texStringify(){
    string a_s=E.getA().stringify();
    string res="\nWir betrachten die Kurve E="+E.stringify()+" mit Ordnung "+to_string(E.order());
    res += ".\n Für die Latex Tabelle:\n";
    res += ".\n $i$ & $p_i$ & Gleichung von $E_i$ & $\\nE$ & $G_i$ \\\\ \\hline \n";
    long long count=1;
    for (Neighbour neighbour : neighbours){
      res +="$"+ to_string(count)+"$&$"+to_string(neighbour.getP())+"$&$  y^2=x^3+"+a_s+"x+"+neighbour.getEC().getB().stringify()+" $&$ "+to_string(neighbour.getOrder())+"$ & $"+ neighbour.getG().stringify()+"$\\\\ \n";
      count++;
    }
    res +="\nDer quadrierte private Schlüssel des Servers ist s²="+to_string(secret)+", somit ist |s|="+to_string(static_cast<long long>(std::floor(sqrt(secret))))+"!\n";
    return res;
  }
};