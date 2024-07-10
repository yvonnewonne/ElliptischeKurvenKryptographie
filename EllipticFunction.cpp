#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Point.cpp"
using namespace std;

class EllipticFunction{
    private:
    // Für die Funktion f=x^3+ax+b im Raum Fp
     Fp a = Fp(0,5);
     Fp b = Fp(0,5);
     long long p = 5;

    public:
    // Konstruktor
    EllipticFunction(Fp a_, Fp b_, long long p_){
        if(a_.getP()!=b_.getP()){
            throw invalid_argument("a und b sind nicht im gleichen Körper (verschiedene p) ");
        }
        if(a_.getP()!=p_){
            throw invalid_argument(" Das übergebene p passt nicht zum p von a und b. ");
        }
        p=p_;
        if(((Fp(4,p)*(a_^3)) + (Fp(27,p)*(b_^2))) == Fp(0,p)){
            throw invalid_argument("Keine elliptische Kurve: Term hat mehrfache Nullstellen. ");
        }
        a=a_;
        b=b_;
    }

    EllipticFunction(Fp a_, Fp b_){
        if(a_.getP()!=b_.getP()){
             throw invalid_argument("a und b sind nicht im gleichen Körper (verschiedene p) ");
        }
        p=a_.getP();
        if(((Fp(4,p)*(a_^3)) + (Fp(27,p)*(b_^2))) == Fp(0,p)){
            throw invalid_argument("Keine elliptische Kurve: Term hat mehrfache Nullstellen. ");
        }
        a=a_;
        b=b_;
    }

    // Operator 
    bool operator == (const EllipticFunction& E) const {
        return (a==E.getA() && b==E.getB());
    }

    // get-Funktionen
    Fp getA() const {
        return a;
    }
    Fp getB() const {
        return b;
    }


    // Rechenoperationen
    Point add(Point P, Point Q) const {
        Fp x1=P.getX();
        Fp x2=Q.getX();
        Fp y1=P.getY();
        Fp y2=Q.getY();
        bool inf1=P.isInf();
        bool inf2=Q.isInf();
        long long p=x1.getP();
        if(inf1){ // Fall 1: P oder Q ist inf
            return Q.copy();
        } else if(inf2){
            return P.copy();
        } else if(x1==x2 && y1==-y2){ // Fall 2: x1 = x2 ∧ y1 = −y2
            return Point(Fp(), Fp(), true);
        } else if(P==Q){ // Fall 3: Addition mit sich selbst (falls y1 ̸ = 0, sonst selbstinvers)
            Fp x3 = ((((Fp(3,p)*(x1^2))+a)/(Fp(2,p)*y1))^2)-(Fp(2,p)*x1);
            Fp y3 = -y1+((Fp(3,p)*(x1^2)+a)/(Fp(2,p)*y1))*(x1-x3);
            return Point(x3,y3);
        } else { // Fall 4: Addition verschiedener Punkte
            Fp x3 = ((((y2-y1)/(x2-x1))^2)-x1)-x2;
            Fp y3 = -y1+((y2-y1)/(x2-x1))*(x1-x3);
            return Point(x3,y3);
        }    
    }

    Point mult(long long k, Point P){
        if(k==0){
            return Point(P.getP(), true);
        } 
        Point res = Point(P.getP(), true);
        Point base = P;
        while (k>0){
            if(k%2==1){
                if(res.isInf()){
                    res=base;
                } else {
                    res=add(res,base);
                }
            }
            base=add(base, base);
            k >>= 1;    
        }
        return res;
    }

    // Funktionsrückgabe
    Fp f(Fp x){
        return ((x^3)+(a*x))+b;
    }

    long long order(){ // Ordnung mit Eulers Kriterium
        long long count=1; // für neutrales Element
        for(long long k=0; k<p; k++){
            Fp a = f(Fp(k,p));
            if(a==Fp(0,p)){
                count++;
            } else if(a.quadRes()){
                count=count+2;
            }
        }
        return count;
    }

    // gibt Vektor aller Punkte (außer infty) der Elliptischen Kurve zurück, nur für kleine p!
    std::vector<Point> generatePoints() {
        std::vector<Point> points;
        for(long long x=0; x<p; x++){
            Fp a = f(Fp(x,p));
            if(a==Fp(0,p)){
                points.push_back(Point(Fp(x,p),Fp(0,p)));
            } else if(a.quadRes()){
                for(long long y=1; y<(p+1)/2; y++){
                    if((Fp(y,p)^2)==a){
                        points.push_back(Point(Fp(x,p),Fp(y,p)));
                        points.push_back(Point(Fp(x,p),Fp(-y,p)));
                    }
                }
            }
        }
        return points;
    }

    // listet alle Punkte der Elliptischen Kurve auf, nur für kleine p!!
    void list() {
        std::cout<<"\nAuf der Kurve E="<<stringify()<<" liegen die Punkte \n{"<<Point(p,true).stringify();
        int count=1;
        for(long long x=0; x<p; x++){
            Fp a = f(Fp(x,p));
            if(a==Fp(0,p)){
                std::cout<<", "<<Point(Fp(x,p),Fp(0,p)).stringify();
                count++;
            } else if(a.quadRes()){
                count=count+2;
                for(long long y=1; y<(p+1)/2; y++){
                    if((Fp(y,p)^2)==a){
                            std::cout<<", "<<Point(Fp(x,p),Fp(y,p)).stringify()<<", "<<Point(Fp(x,p),Fp(-y,p)).stringify();
                    }
                }
            }
        }
        std::cout<<" },\n insgesamt sind das "<<count<<" Stück. \n";
    }

    // to-String Funktion
    string stringify() {
        return "{(x,y) e Fp^2| y^2=x^3+"+a.stringify()+"x+"+b.stringify()+"} U {infty} ";
    }
};