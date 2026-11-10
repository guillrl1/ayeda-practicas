// ---------------- NodoAVL.h ----------------
#ifndef NODOAVL_H
#define NODOAVL_H
#include "NodoB.h"

template<typename Key>
class NodoAVL : public NodoB<Key> {
    int bal;
public:
    NodoAVL(const Key& k) : NodoB<Key>(k), bal(0) {}
    int getBalance() const { return bal; }
    void setBalance(int b) { bal = b; }
    // redefinir accesores para tipo AVL
    NodoAVL<Key>* getIzdo() const { return static_cast<NodoAVL<Key>*>(this->izdo); }
    NodoAVL<Key>* getDcho() const { return static_cast<NodoAVL<Key>*>(this->dcho); }
    void setIzdo(NodoAVL<Key>* p) { this->izdo = p; }
    void setDcho(NodoAVL<Key>* p) { this->dcho = p; }
};

#endif // NODOAVL_H