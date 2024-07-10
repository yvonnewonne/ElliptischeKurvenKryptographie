#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include "Attack.cpp"
using namespace std;

// Klasse zum verwalten eines Klienten
class Client{
  private:
    EllipticFunction E= EllipticFunction(Fp(0,11),Fp(7,11),11);
    Point Q=Point(true,11);
    long long s=0; // privater Schlüssel
    Point sQ = Point(true,11); // öffentlicher Schlüssel
    long long k=10; 
    

  public:
  // Konstruktor
  Client(EllipticFunction E_, Point Q_, long long s_, long long k_){
    E = E_;
    Q = Q_;
    s = s_;
    k = k_;
    sQ = E.mult(s, Q);
  }

  // set-Methoden

  Point getPublicKey(){
    return sQ;
  }

  // Methoden zum Senden und Empfangen von Nachrichten

  std::vector<std::string> splitString(const std::string &input, size_t n) {
    std::vector<std::string> result;

    for (size_t i = 0; i < input.size(); i += n) {
        result.push_back(input.substr(i, n));
    }

    return result;
  }

  long long encode(char c) {
    // Map for uppercase letters
    std::unordered_map<char, long long> charMap = {
        {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14},
        {'F', 15}, {'G', 16}, {'H', 17}, {'I', 18}, {'J', 19},
        {'K', 20}, {'L', 21}, {'M', 22}, {'N', 23}, {'O', 24},
        {'P', 25}, {'Q', 26}, {'R', 27}, {'S', 28}, {'T', 29},
        {'U', 30}, {'V', 31}, {'W', 32}, {'X', 33}, {'Y', 34}, {'Z', 35},
        {'a', 36}, {'b', 37}, {'c', 38}, {'d', 39}, {'e', 40},
        {'f', 41}, {'g', 42}, {'h', 43}, {'i', 44}, {'j', 45},
        {'k', 46}, {'l', 47}, {'m', 48}, {'n', 49}, {'o', 50},
        {'p', 51}, {'q', 52}, {'r', 53}, {'s', 54}, {'t', 55},
        {'u', 56}, {'v', 57}, {'w', 58}, {'x', 59}, {'y', 60}, {'z', 61},
        {'!', 62}, {',', 63}, {'.', 64}, {'?', 65}, {' ', 66}
    };
    
    if (charMap.find(c) != charMap.end()) {
        return charMap[c];
    } else {
      std::cout<<" Der char "<<c<<" kann nicht verschlüsselt werden. \n";
        return -1; // Return -1 for characters not in the map
    }
  }

  char decode(long long value){
    std::unordered_map<long long, char> longlongMap = {
        {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'},
        {15, 'F'}, {16, 'G'}, {17, 'H'}, {18, 'I'}, {19, 'J'},
        {20, 'K'}, {21, 'L'}, {22, 'M'}, {23, 'N'}, {24, 'O'},
        {25, 'P'}, {26, 'Q'}, {27, 'R'}, {28, 'S'}, {29, 'T'},
        {30, 'U'}, {31, 'V'}, {32, 'W'}, {33, 'X'}, {34, 'Y'}, {35, 'Z'},
        {36, 'a'}, {37, 'b'}, {38, 'c'}, {39, 'd'}, {40, 'e'},
        {41, 'f'}, {42, 'g'}, {43, 'h'}, {44, 'i'}, {45, 'j'},
        {46, 'k'}, {47, 'l'}, {48, 'm'}, {49, 'n'}, {50, 'o'},
        {51, 'p'}, {52, 'q'}, {53, 'r'}, {54, 's'}, {55, 't'},
        {56, 'u'}, {57, 'v'}, {58, 'w'}, {59, 'x'}, {60, 'y'}, {61, 'z'},
        {62, '!'}, {63, ','}, {64, '.'}, {65, '?'}, {66, ' '}
    };

    if (longlongMap.find(value) != longlongMap.end()) {
        return longlongMap[value];
    } else {
        return '\0'; // Return null character for values not in the map
    }
  }

  // std::vector<Point> send(string message, Client Bob, long long random) {
  //   int len = message.length();
  //   long long m = 0;
  //   long long p = Q.getP();
  //   for(int i=0; i<len;i++){
  //     m=100*m+encode(message[i]);
  //   }
  //   Fp mi = Fp(k*m, p);
  //   std::cout<<"Die x-Koordiante vom Punkt ist "<<mi.stringify()<<"\n";
  //   bool found = false;
  //   for(int i=0; i<k;i++){
  //     if (E.f(mi).quadRes()){
  //       std::cout<<"es ist f("<<mi.stringify()<<") ein quadres\n";
  //       found = true;
  //       break;
  //     } else {
  //       std::cout<<"es ist f("<<mi.stringify()<<") kein quadres\n";

  //     }
  //     mi= Fp(mi.getN()+1, p);
  //   }
  //   Point M = Point(p, true); 

  //   if (found){
  //     for(long long y=0; y<(p+1)/2; y++){
  //         if((Fp(y,p)^2)==E.f(mi)){
  //             M = Point(mi, Fp(y,p));
  //             std::cout<<"Die Nachricht ist im Punkt "<<M.stringify()<<" verschlüsselt.\n";
  //             break;
  //         }
  //     }
  //   } else {
  //     std::cout<<"Es wurde kein Punkt auf der Kurve gefunden, der dieser Nachricht entspricht. \n";
  //   }
  //   Point C1 = E.mult(random, Q);
  //   Point C2 = E.add(M,E.mult(random, Bob.getPublicKey()));
  //   std::cout<<"C1="<<C1.stringify()<<", C2="<<C2.stringify()<<".\n";
  //   std::vector<Point> res{C1, C2};
  //   return res;
  // }

  std::vector<Point> send(string message, Client Bob, std::vector<long long> randoms) {
    long long p = Q.getP();
    // maximale Charanzahl pro Point:
    int numchar=(static_cast<int>(std::log10(p/k-1)))/2;
    std::vector<std::string> strings = splitString(message, numchar);
    std::vector<Point> points;
    std::cout<<"Wir können maximal "<<numchar<<" Zeichen in einen Punkt verschlüsseln.\n";
    int l=0;
    std::cout<<"\n Zeichen - Kodierung - M - C1 - C2             \n";
    for(string& str : strings){
      long long m = 0;
      int len = str.length();
      for(int i=0; i<len;i++){
        m=100*m+encode(str[i]);
      }
      Fp mi = Fp(k*m, p);
      bool found = false;
      for(int i=0; i<k;i++){
        if (E.f(mi).quadRes()){
          found = true;
          break;
        }
        mi= Fp(mi.getN()+1, p);
      }
      Point M = Point(p, true); 

      if (found){
        for(long long y=0; y<(p+1)/2; y++){
            if((Fp(y,p)^2)==E.f(mi)){
                M = Point(mi, Fp(y,p));
                //std::cout<<" "<<M.stringify()<<"";
                break;
            }
        }
      } else {
        std::cout<<"Es wurde kein Punkt auf der Kurve gefunden, der dieser Nachricht entspricht. \n";
      }
      Point C1 = E.mult(randoms[l], Q);
      Point C2 = E.add(M,E.mult(randoms[l], Bob.getPublicKey()));
      points.push_back(C1);
      points.push_back(C2);
      std::cout<<str<<" | "<<m<<" | "<<M.stringify()<<" | "<<C1.stringify()<<" | "<<C2.stringify()<<" \n";
      l++;
    }
    return points;
  }

  // string receive(std::vector<Point> input){
  //   Point C1 = input[0];
  //   Point C2 = input[1];
  //   Point M = E.add(C2, -E.mult(s, C1));
  //   std::cout<<"Der entschlüsselte Punkt M="<<M.stringify()<<".\n";
  //   long long x = M.getX().getN();
  //   string message ="";
  //   x = x/k;
  //   while (x!=0){
  //     message=decode(x%100)+message; // letzten zwei Ziffern dekodieren
  //     x=x/100;
  //   }
  //   //std::cout<<" Die entschlüsselte Nachricht ist: "<< message<<"\n"
  //   return message;
  // } 

   string receive(std::vector<Point> input){
    string message="";
    int l=input.size(); 
    for(int j=0; j<l; j+=2){
      Point C1 = input[j];
      Point C2 = input[j+1];
      Point M = E.add(C2, -E.mult(s, C1));
      //std::cout<<"Der entschlüsselte Punkt M="<<M.stringify()<<".\n";
      long long x = M.getX().getN();
      x = x/k;
      string str="";
      while (x!=0){
        str=decode(x%100)+str; // letzten zwei Ziffern dekodieren
        x=x/100;
      }
      message+=str;
    }

    //std::cout<<" Die entschlüsselte Nachricht ist: "<< message<<"\n"
    return message;
  } 
};