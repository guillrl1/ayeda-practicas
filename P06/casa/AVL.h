// ---------------- AVL.h ----------------
#ifndef AVL_H
#define AVL_H

#include "ABB.h"
#include "NodoAVL.h"
#include <algorithm>
#include <cmath>
#include <iostream>

template<typename Key>
class AVL : public ABB<Key> {
    using ABB<Key>::raiz;
    bool modoTrace;

    int altura(NodoAVL<Key>* p) const {
        if (!p) return -1;
        return 1 + std::max(altura(p->getIzdo()), altura(p->getDcho()));
    }
    void actualizarBalance(NodoAVL<Key>* p) const {
        if (p) p->setBalance(altura(p->getDcho()) - altura(p->getIzdo()));
    }
    NodoAVL<Key>* rotacionII(NodoAVL<Key>* p) {
        NodoAVL<Key>* u = p->getIzdo();
        p->setIzdo(u->getDcho());
        u->setDcho(p);
        actualizarBalance(p); actualizarBalance(u);
        return u;
    }
    NodoAVL<Key>* rotacionDD(NodoAVL<Key>* p) {
        NodoAVL<Key>* u = p->getDcho();
        p->setDcho(u->getIzdo());
        u->setIzdo(p);
        actualizarBalance(p); actualizarBalance(u);
        return u;
    }
    NodoAVL<Key>* rotacionID(NodoAVL<Key>* p) {
        p->setIzdo(rotacionDD(p->getIzdo()));
        return rotacionII(p);
    }
    NodoAVL<Key>* rotacionDI(NodoAVL<Key>* p) {
        p->setDcho(rotacionII(p->getDcho()));
        return rotacionDD(p);
    }

    NodoAVL<Key>* insertarRec(NodoAVL<Key>* nodo, const Key& k, bool& inserted) {
        if (!nodo) {
            inserted = true;
            return new NodoAVL<Key>(k);
        }
        if (k < nodo->getDato())
            nodo->setIzdo(insertarRec(nodo->getIzdo(), k, inserted));
        else if (k > nodo->getDato())
            nodo->setDcho(insertarRec(nodo->getDcho(), k, inserted));
        else {
            inserted = false;
            return nodo;
        }
        actualizarBalance(nodo);
        if (modoTrace && std::abs(nodo->getBalance()) > 1) {
            std::cout << "Desbalanceo en nodo " << nodo->getDato()
                      << "(" << nodo->getBalance() << ")" << std::endl;
        }
        if (nodo->getBalance() < -1) {
            if (nodo->getIzdo()->getBalance() <= 0) {
                if (modoTrace) std::cout << "Rotación II en ["<< nodo->getDato() <<"]"<<std::endl;
                nodo = rotacionII(nodo);
            } else {
                if (modoTrace) std::cout << "Rotación ID en ["<< nodo->getDato() <<"]"<<std::endl;
                nodo = rotacionID(nodo);
            }
        } else if (nodo->getBalance() > 1) {
            if (nodo->getDcho()->getBalance() >= 0) {
                if (modoTrace) std::cout << "Rotación DD en ["<< nodo->getDato() <<"]"<<std::endl;
                nodo = rotacionDD(nodo);
            } else {
                if (modoTrace) std::cout << "Rotación DI en ["<< nodo->getDato() <<"]"<<std::endl;
                nodo = rotacionDI(nodo);
            }
        }
        return nodo;
    }

public:
    AVL(bool trace = false) : modoTrace(trace) {}
    bool insertar(const Key& k) override {
        bool inserted = false;
        raiz = insertarRec(static_cast<NodoAVL<Key>*>(raiz), k, inserted);
        return inserted;
    }
    void setTrace(bool t) { modoTrace = t; }
};

#endif // AVL_H


