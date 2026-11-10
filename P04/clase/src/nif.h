#ifndef NIF_HPP
#define NIF_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

class nif {
private:
    long number;
public:
    // Constructor por defecto: genera un número aleatorio de 8 dígitos.
    nif() {
        number = 10000000 + rand() % 90000000;
    }
    // Constructor a partir de un número.
    nif(long n) : number(n) {}
    
    // Conversión a long para operaciones numéricas.
    operator long() const {
        return number;
    }
    
    bool operator==(const nif& other) const {
        return number == other.number;
    }
    
    bool operator<(const nif& other) const {
        return number < other.number;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const nif& n) {
        os << n.number;
        return os;
    }
};

#endif // NIF_HPP