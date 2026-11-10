#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <iostream>
#include <memory>
#include "Sequence.h"
#include "dispersionFunction.h"
#include "explorationFunction.h"

// Clase HashTable (dispersión cerrada)
template<typename Key, typename Container = staticSequence<Key>>
class HashTable : public Sequence<Key> {
private:
    unsigned tableSize;
    std::vector<std::unique_ptr<Container>> table;
    const DispersionFunction<Key>& fd;
    const ExplorationFunction<Key>& fe;
    unsigned blockSize;

    // Método auxiliar para encontrar una posición de inserción válida
    unsigned findPosition(const Key& k) const {
        unsigned hash = fd(k);
        unsigned i = 0, pos;
        do {
            pos = (hash + fe(k, i)) % tableSize;
            if (!table[pos]->isFull() || table[pos]->search(k)) {
                return pos;
            }
            i++;
        } while (i < tableSize);
        return tableSize; // Indica que no se encontró espacio
    }

public:
    HashTable(unsigned ts, const DispersionFunction<Key>& dispersionFunc, const ExplorationFunction<Key>& explorationFunc, unsigned bs)
    : tableSize(ts), fd(dispersionFunc), fe(explorationFunc), blockSize(bs) {
        table.resize(tableSize);
        for (unsigned i = 0; i < tableSize; i++) {
            table[i] = std::make_unique<Container>(blockSize);
        }
    }

    virtual bool insert(const Key& k) override {
        unsigned pos = findPosition(k);
        if (pos == tableSize || table[pos]->search(k)) return false;
        return table[pos]->insert(k);
    }

    virtual bool search(const Key& k) const override {
        unsigned hash = fd(k);
        unsigned i = 0, pos;
        do {
            pos = (hash + fe(k, i)) % tableSize;
            if (table[pos]->search(k)) return true;
            i++;
        } while (i < tableSize);
        return false;
    }
};

// Especialización para dispersión abierta
template<typename Key>
class HashTable<Key, dynamicSequence<Key>> : public Sequence<Key> {
private:
    unsigned tableSize;
    std::vector<std::unique_ptr<dynamicSequence<Key>>> table;
    const DispersionFunction<Key>& fd;

public:
    HashTable(unsigned ts, const DispersionFunction<Key>& dispersionFunc)
    : tableSize(ts), fd(dispersionFunc) {
        table.resize(tableSize);
        for (unsigned i = 0; i < tableSize; i++) {
            table[i] = std::make_unique<dynamicSequence<Key>>();
        }
    }

    virtual bool insert(const Key& k) override {
        unsigned hash = fd(k);
        if (table[hash]->search(k)) return false;
        return table[hash]->insert(k);
    }

    virtual bool search(const Key& k) const override {
        unsigned hash = fd(k);
        return table[hash]->search(k);
    }

};

#endif // HASHTABLE_HPP
