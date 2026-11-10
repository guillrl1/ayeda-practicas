#ifndef DISPERSIONFUNCTION_HPP
#define DISPERSIONFUNCTION_HPP

#include <cstdlib>
#include "nif.h"

// Clase base abstracta para la función de dispersión.
template<typename Key>
class DispersionFunction {
public:
    virtual unsigned operator()(const Key& key) const = 0;
    virtual ~DispersionFunction() {}
};

// Función de dispersión: h(k) = k % tableSize
template<typename Key>
class ModuloDispersion : public DispersionFunction<Key> {
private:
    unsigned tableSize;
public:
    ModuloDispersion(unsigned ts) : tableSize(ts) {}
    virtual unsigned operator()(const Key& key) const override {
        long k = key;
        return static_cast<unsigned>(k % tableSize);
    }
};

// Función de dispersión basada en la suma de dígitos: h(k) = sum(ki) % tableSize
template<typename Key>
class SumBasedDispersion : public DispersionFunction<Key> {
private:
    unsigned tableSize;
public:
    SumBasedDispersion(unsigned ts) : tableSize(ts) {}
    virtual unsigned operator()(const Key& key) const override {
        long k = key;
        unsigned sum = 0;
        while(k > 0) {
            sum += k % 10;
            k /= 10;
        }
        return sum % tableSize;
    }
};

// Función de dispersión pseudoaleatoria: h(k) = {srand(k); rand()} % tableSize
template<typename Key>
class PseudoRandomDispersion : public DispersionFunction<Key> {
private:
    unsigned tableSize;
public:
    PseudoRandomDispersion(unsigned ts) : tableSize(ts) {}
    virtual unsigned operator()(const Key& key) const override {
        long k = key;
        srand(static_cast<unsigned>(k));
        return rand() % tableSize;
    }
};

#endif // DISPERSIONFUNCTION_HPP