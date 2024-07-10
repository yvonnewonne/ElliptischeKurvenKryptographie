#include <iostream>
#include <cmath>
//#include <vector>
#include <string>
#include "Client.cpp"
using namespace std;

void testFp() {
    long long p=17;
    std::cout<<"----------------------- Test von der Klasse Fp -----------------------\nWir betrachten den Körper F"<<int(p)<<".\n ";
    Fp a=Fp(6,p);
    Fp b=Fp(15,p);
    long long k=-3;
    long long l=-1;
    std::cout<<"\n Test der Operationen +, - und *\n";
    std::cout<<a.stringify()<<"+"<<b.stringify()<<"="<<(a+b).stringify()<<"\n";
    std::cout<<a.stringify()<<"*"<<b.stringify()<<"="<<(a*b).stringify()<<"\n";
    std::cout<<a.stringify()<<"-"<<b.stringify()<<"="<<(a-b).stringify()<<"\n";
    std::cout<<a.stringify()<<"*"<<a.stringify()<<"="<<(a*a).stringify()<<"\n";
    std::cout<<a.stringify()<<"*"<<a.stringify()<<"*"<<a.stringify()<<"="<<(a*a*a).stringify()<<"\n";
    std::cout<<a.stringify()<<"-"<<b.stringify()<<"="<<(a-b).stringify()<<"\n";
    std::cout<<a.stringify()<<"/"<<b.stringify()<<"="<<(a/b).stringify()<<"\n";
    std::cout<<"\n Test des Potenzierens\n";
    std::cout<<a.stringify()<<"^"<<k<<"="<<(a^k).stringify()<<"\n";
    std::cout<<a.stringify()<<"^"<<l<<"="<<(a^l).stringify()<<"\n";
    std::cout<<b.stringify()<<"^"<<l<<"="<<(b^l).stringify()<<"\n";
    std::cout<<b.stringify()<<"^"<<k<<"="<<(b^k).stringify()<<"\n";
    std::cout<<"\n Test von (Un)gleichheiten\n";
    std::cout<<b.stringify()<<"=="<<a.stringify()<<" ist "<< to_string(b==a)<<"\n";
    std::cout<<Fp(19,17).stringify()<<"=="<<Fp(2,17).stringify()<<" ist "<< to_string(Fp(19,17)==Fp(2,17))<<"\n";
    std::cout<<b.stringify()<<"!="<<a.stringify()<<" ist "<< to_string(!(b==a))<<"\n";
}

void testEC() { // testet Operationen auf der elliptischen Kurve
    long long p=11;
    Fp a=Fp(0,11);
    Fp b=Fp(7,11);
    EllipticFunction E=EllipticFunction(a,b,p);
    std::cout<<"----------------------- Test von der Klasse EllipticFunction und Point ------------------------------\n Wir betrachten den Körper F"<<int(p)<<".\n E="<<E.stringify();
    E.list();
    Point P=Point(Fp(5,p),Fp(0,p));
    Point Q=Point(Fp(3,p),Fp(10,p));
    std::cout<<"\n\nP="<<P.stringify()<<", Q="<<Q.stringify()<<"\n\n";
    std::cout<<"Addition verschiedener Punkte: P+Q="<<(E.add(P,Q)).stringify()<<"\n";
    std::cout<<"Inverses eines Punktes: -P="<<(-P).stringify()<<"\n";
    std::cout<<"Addition vom Inversen: P-P="<<(E.add(P,-P)).stringify()<<"\n";
    std::cout<<"Skalarmultiplikation: 2*Q="<<(E.mult(2,Q)).stringify()<<"\n";
    std::cout<<"Skalarmultiplikation: 2*P="<<(E.mult(2,P)).stringify()<<"\n";
    std::cout<<"Einsetzen in Kurvengleichung: f("<<P.getX().getN()<<")="<<(E.f(P.getX())).stringify()<<"\n";
    std::cout<<"Bestimmen Ordnung: Die Ordnung von E ist "<<E.order()<<"\n";

    Fp a2=Fp(1,7);
    Fp b2=Fp(-1,7);
    
    EllipticFunction E2=EllipticFunction(a2,b2);
    std::cout<<"Die Ordnung von E'="<<E2.stringify()<< "ist "<<E2.order()<<"\n";
    E2.list();

    std::cout<<"\nSkalarmultiplikationstest:\n";
    std::cout<<"2*Q="<<(E.mult(2,Q)).stringify()<<"\n";
    std::cout<<"5*Q="<<(E.mult(5,Q)).stringify()<<"\n";
    std::cout<<"3*Q="<<(E.mult(3,Q)).stringify()<<"\n";
    std::cout<<"3*P="<<(E.mult(3,P)).stringify()<<"\n";
    std::cout<<"2*P="<<(E.mult(2,P)).stringify()<<"\n";
}

void testAttack1() {
    std::cout<<"------ testAttack1() -----------------------------------------------------------------\n";
    long long p=73;
    Fp a=Fp(17,p);
    Fp b=Fp(9,p);
    EllipticFunction E=EllipticFunction(a,b);
    E.list();
    
    // Angreifer Setup
    Attack A = Attack(E);

    // erster Server Setup
    Server server =Server(E, 54); // zweiter Eintrag ist der private Schlüssel des Servers
    
    // erster Angriff und Ausgabe
    std::cout<<"\n\n Wir greifen jetzt den Server an. \n";
    A.attackServer(server);
    std::cout<<A.stringify();
}

void testAttack2() {
    std::cout<<"------ testAttack2() -----------------------------------------------------------------\n";
    long long p=12347;
    Fp a2=Fp(2,p);
    Fp b2=Fp(3,p);
    EllipticFunction E=EllipticFunction(a2,b2);
    // Kurve wird wegen der großen Ordnung nicht aufgelistet

    // Angreifer Setup
    Attack A = Attack(E);

    // Server Setup
    Server server =Server(E, 5387);

    // Angriff und Ausgabe
    std::cout<<"\n\n Wir greifen jetzt den Server an. \n";
    A.attackServer(server);   
    std::cout<<A.stringify();
    //std::cout<<A.texStringify();
}

void testComparison() { //braucht ein gutes Weilchen zur Berechnung
    std::vector<long long> primes{5,11, 17,31,47,79,97, 137, 271, 409, 541, 673, 809, 941, 1087, 1213, 1361, 1481, 1613, 1747, 1879, 2017, 2153, 2281, 2417, 2549, 2683, 2819, 2953, 3089, 3221, 3359, 3491, 3623, 3761, 3889, 4027, 4157, 4297, 4441, 4561, 4703, 4831, 4967, 5099, 5231, 5381, 5501, 5639, 5779, 5903, 6037, 6173, 6301, 6449, 6569, 6703, 6841, 6971, 7109, 7243, 7393, 7507, 7643, 7789, 7919, 8053, 8179, 8311, 8447, 8581, 8713, 8849, 8999, 9127, 9257, 9391, 9521, 9661, 9787, 9923, 10061, 10193, 10321, 10457, 10589, 10723, 10859, 10993, 11131, 11261, 11393, 11527, 11677, 11801, 11933, 12071, 12197, 12343, 12473, 12601, 12739, 12889, 13001, 13147, 13291, 13411, 13537, 13679, 13807, 13963, 14081, 14207, 14341, 14479, 14621, 14747, 14879, 15013, 15149, 15287, 15413, 15551, 15683, 15817, 15959, 16087, 16217, 16361, 16487, 16619, 16759, 16889, 17021, 17159, 17291, 17431, 17569, 17707, 17827, 17959, 18097, 18229, 18367, 18503, 18637, 18773, 18899, 19031, 19181, 19301, 19433, 19571, 19709, 19841, 19973, 19997, 21347, 41879, 62851, 83773, 105407, 125683, 145949, 167593, 187823, 210139, 230393, 250673, 270913, 293201, 313471};
    for(long long p : primes){
        std::cout<<"\n p="<<to_string(p)<<", ";
        Fp a=Fp(2,p);
        Fp b=Fp(3,p);
        if(!(((Fp(4,p)*(a^3)) + (Fp(27,p)*(b^2))) == Fp(0,p))){
            EllipticFunction E=EllipticFunction(a,b);

            // Angreifer Setup
            Attack A = Attack(E);

            // Server Setup
            Server server =Server(E, 5387);

            // Angriff und Ausgabe
            A.attackServer(server);   
            std::cout<<A.stringify();
            //std::cout<<A.texStringify();
        } else {
            std::cout<<"\n Für p="<<to_string(p)<<" ist E singulär. \n";
        }
    }
}

void testArithmetic(){ // testet Chinesischen Restsatz
    std::cout<<"------ testArithmetic() -----------------------------------------------------------------\n";
    std::vector<long long> res = {2, 3, 2}; // Beispielwerte
    std::vector<long long> moduli = {3, 5, 7};  // Beispielmoduli
    std::cout<<"\nWir kennen die Kongruenzen:\n";
    for(int i=0; i<res.size();i++){
        std::cout<<"s mod "<<moduli[i]<<" = "<<res[i]<<"\n";
    }
    try {
        long long s = Arithmetic::CRS(res, moduli);
        std::cout << "\nSomit ist s=" << s << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void testSending() {
    string message = "Ein Geheimnis!";
    std::cout<<"------ testSending() -----------------------------------------------------------------\n";
    long long p= 346111;
    //long long p=17487707;
    EllipticFunction E=EllipticFunction(Fp(1234,p),Fp(17,p));
    std::cout<<"wir nutzen die Kurve "<<E.stringify()<<" mit p="<<p<<"\n";
    Point Q= Point(Fp(283468,p),Fp(291812,p));
    long long a = 95; // privater Schlüssel Alice
    long long b = 42; // privater Schlüssel Bob
    long long k = 50;  // erhöhen um Versagenswahrscheinlihceit zu verringern
    Client Alice = Client(E, Q, a, k);
    Client Bob = Client(E, Q, b, k);
    std::vector<long long> randoms = {5, 13, 9, 11, 2, 40, 3, 67, 5, 2, 8, 9, 32, 89, 213, 7}; //muss lang genug für die message sein
    std::cout<<"Q="<<Q.stringify()<<", k="<<k<<"\n";

    std::cout<<"\n Alice verschlüsselt die Nachricht: \""<<message<<"\"\n\n";
    std::vector<Point> C = Alice.send(message, Bob, randoms);
    string decMessage = Bob.receive(C);
    
    std::cout<<"\nBob entschlüsselt die Nachricht: \""<<decMessage<<"\"\n";
}

// nur Hilfsfunktion fürs Testen, nicht relevant für irgendwelche Berechnungen
std::vector<long long> shorten(const std::vector<long long>& primes, int n) {
    if (primes.empty() || n <= 0) {
        return {};
    }
    std::vector<long long> result;
    long long max = primes.back();
    long long min = primes.front();
    long long step = (max - min) / (n - 1);
    result.push_back(min);
    int count = 1;
    long long current = min + step;

    for (size_t i = 1; i < primes.size() - 1 && count < n; ++i) {
        if (primes[i] >= current) {
            result.push_back(primes[i]);
            current += step;
            ++count;
        }
    }
    result.push_back(max);
    return result;
}


int main() {
    //testFp();
    //testEC();
    //testAttack1();
    //testAttack2();
    //testComparison();
    //testArithmetic();
    testSending();
    return 0;
}

