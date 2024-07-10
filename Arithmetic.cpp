#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Arithmetic {
public:
    // Schnelle exponentielle Modulo-Berechnung
    static long long modExp(long long base, long long exp, long long p) {
        long long res = 1;
        base = base % p;
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = (res * base) % p;
            }
            exp = exp >> 1;
            base = (base * base) % p;
        }
        return res;
    }

    // Modularer Inverser mit Fermat
    static long long modInverse(long long a, long long p) {
        return modExp(a, p - 2, p);
    }

    // Chinesischer Restsatz (nur für Primzahl-Modi!)
    static long long CRS(const std::vector<long long>& res, const std::vector<long long>& modis) {
        long long product = 1;
        for (long long mod : modis) {
            product *= mod;
        }
        long long result = 0;
        for (size_t i = 0; i < res.size(); ++i) {
            long long partialProduct = product / modis[i];
            long long inverse = modInverse(partialProduct, modis[i]);
            result += res[i] * partialProduct * inverse;
            result %= product; 
        }
        long long solution = (result % product + product) % product;
        return solution;
        
    }
};

