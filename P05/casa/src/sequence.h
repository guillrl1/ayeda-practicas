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
    virtual const Key& operator[](const unsigned) const = 0;
    virtual Key& operator[](const unsigned) = 0;  
    virtual ~Sequence() {}
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

    virtual unsigned getSize() const {
        return data.size();
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
    const Key& operator[](const unsigned i) const override { return data[i]; }

    Key& operator[](const unsigned i) override { return data[i]; }


    void Print() const {
        for (const auto& elem : data) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

#endif // SEQUENCE_HPP