#ifndef EXPLORATIONFUNCTION_HPP
#define EXPLORATIONFUNCTION_HPP

#include <cstdlib>
#include "nif.h"
#include "dispersionFunction.h"

// Clase base abstracta para la función de exploración.
template<typename Key>
class ExplorationFunction {
public:
    virtual unsigned operator()(const Key& key, unsigned i) const = 0;
    virtual ~ExplorationFunction() {}
};

// Exploración lineal: g(k,i) = i
template<typename Key>
class LinearExploration : public ExplorationFunction<Key> {
public:
    virtual unsigned operator()(const Key& key, unsigned i) const override {
        return i;
    }
};

// Exploración cuadrática: g(k,i) = i^2
template<typename Key>
class QuadraticExploration : public ExplorationFunction<Key> {
public:
    virtual unsigned operator()(const Key& key, unsigned i) const override {
        return i * i;
    }
};

// Exploración por doble dispersión: g(k,i) = f(k) * i
template<typename Key>
class DoubleDispersion : public ExplorationFunction<Key> {
private:
    const DispersionFunction<Key>& aux;
public:
    DoubleDispersion(const DispersionFunction<Key>& f) : aux(f) {}
    virtual unsigned operator()(const Key& key, unsigned i) const override {
        return (aux(key) * i);
    }
};

// Exploración por redispersión: g(k,i) = f(i)(k)
// Se reinicializa el generador con la clave y se obtiene el i-ésimo número.
template<typename Key>
class Redispersion : public ExplorationFunction<Key> {
public:
    virtual unsigned operator()(const Key& key, unsigned i) const override {
        long k = key;
        srand(static_cast<unsigned>(k));
        unsigned value = 0;
        for(unsigned j = 0; j < i; j++){
            value = rand();
        }
        return value;
    }
};

#endif // EXPLORATIONFUNCTION_HPP