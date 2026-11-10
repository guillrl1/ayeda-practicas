#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <vector>
#include <list>
#include <iostream>

// Clase base abstracta para secuencias.
template<typename Key>
class Sequence {
public:
    virtual bool search(const Key& k) const = 0;
    virtual bool insert(const Key& k) = 0;
    virtual ~Sequence() {}
};

// Secuencia dinámica para dispersión abierta.
template<typename Key>
class dynamicSequence : public Sequence<Key> {
private:
    std::list<Key> data;
public:
    virtual bool search(const Key& k) const override {
        for (const auto& elem : data) {
            if (elem == k) return true;
        }
        return false;
    }
    virtual bool insert(const Key& k) override {
        if(search(k)) return false; // evita duplicados
        data.push_back(k);
        return true;
    }
};

// Secuencia estática para dispersión cerrada.
// Utiliza un vector con capacidad limitada definida por blockSize.
template<typename Key>
class staticSequence : public Sequence<Key> {
private:
    std::vector<Key> data;
    unsigned blockSize;
public:
    staticSequence(unsigned bs) : blockSize(bs) {
        data.reserve(blockSize);
    }
    
    bool isFull() const {
        return data.size() >= blockSize;
    }
    
    virtual bool search(const Key& k) const override {
        for(const auto& elem : data) {
            if(elem == k) return true;
        }
        return false;
    }
    
    virtual bool insert(const Key& k) override {
        if(isFull()) return false;
        if(search(k)) return false; // evita duplicados
        data.push_back(k);
        return true;
    }
};

#endif // SEQUENCE_HPP