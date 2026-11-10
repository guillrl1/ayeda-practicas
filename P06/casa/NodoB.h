// ---------------- NodoB.h ----------------
#ifndef NODOB_H
#define NODOB_H

template<typename Key>
class NodoB {
protected:
    Key dato;
    NodoB<Key>* izdo;
    NodoB<Key>* dcho;
public:
    NodoB(const Key& k) : dato(k), izdo(nullptr), dcho(nullptr) {}
    virtual ~NodoB() = default;
    Key getDato() const { return dato; }
    NodoB<Key>* getIzdo() const { return izdo; }
    NodoB<Key>* getDcho() const { return dcho; }
    void setIzdo(NodoB<Key>* p) { izdo = p; }
    void setDcho(NodoB<Key>* p) { dcho = p; }
};

#endif // NODOB_H