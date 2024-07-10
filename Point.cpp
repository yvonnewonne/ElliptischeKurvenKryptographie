#include <iostream>
#include <cmath>
#include <string>
#include "Fp.cpp"
using namespace std;

class Point{
    private:
    Fp x=Fp(0,5);
    Fp y=Fp(0,5);
    bool inf=false; 
    
    public:
    // Konstruktoren
    Point(Fp x_, Fp y_, bool inf_){
        x=x_;
        y=y_;
        inf=inf_;  
    }

    Point(Fp x_, Fp y_){
        x=x_;
        y=y_;
        inf=false;      
    }
    
    Point(long long p, bool inf_){
        if(inf_){
            x=Fp(0,p);
            y=Fp(0,p);
            inf=true;
        } else {
            throw invalid_argument("Weder ein Punkt noch inf übergeben");
        }
    }

    // Operatoren
    bool operator == (const Point& Q) const {
        if( inf!=Q.isInf()){
            return false;
        } else if (inf) {
            return true; 
        } else if (x==Q.getX() && y==Q.getY()){
            return true; 
        } else {
            return false;
        }
    }

    Point operator - () const{
       if(inf){
        return Point(x.getP(), true);
       } else {
        return Point(x,-y);
       } 
    }

    // Get-Funktionen
    Fp getX() const{
        return x;
    }

    Fp getY() const{
        return y;
    }

    bool isInf() const{
        return inf;
    }

    long long getP() const{
        return x.getP();
    }

    // Sonstiges
    Point inverse(){
        return Point(x,-y,inf);
    }

    Point copy(){
        return Point(x, y, inf);
    }

    // toString-Funktion
    string stringify(){
        if(inf){
            return " inf  ";
        }  else {
            return "("+x.stringify()+", "+y.stringify()+")";
        }
    }
};