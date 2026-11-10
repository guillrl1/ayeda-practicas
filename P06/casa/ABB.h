// ---------------- ABB.h ----------------
#ifndef ABB_H
#define ABB_H

#include "AB.h"

template<typename Key>
class ABB : public AB<Key> {
    protected:
    using AB<Key>::raiz;
    NodoB<Key>* insertarRec(NodoB<Key>* nodo, const Key& k, bool& inserted) {
        if (!nodo) {
            inserted = true;
            return new NodoB<Key>(k);
        }
        if (k < nodo->getDato())
            nodo->setIzdo(insertarRec(nodo->getIzdo(), k, inserted));
        else if (k > nodo->getDato())
            nodo->setDcho(insertarRec(nodo->getDcho(), k, inserted));
        else
            inserted = false;
        return nodo;
    }
public:
    bool insertar(const Key& k) override {
        bool inserted = false;
        raiz = insertarRec(raiz, k, inserted);
        return inserted;
    }
};

#endif // ABB_H
