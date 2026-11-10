// ---------------- AB.h ----------------
#ifndef AB_H
#define AB_H

#include <iostream>
#include <queue>
#include <typeinfo>
#include "NodoB.h"
#include "NodoAVL.h"  // para detectar equilibrio en AVL

template<typename Key>
class AB {
protected:
    NodoB<Key>* raiz;
    bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
        if (!nodo) return false;
        if (k == nodo->getDato()) return true;
        if (k < nodo->getDato()) return buscarRec(nodo->getIzdo(), k);
        return buscarRec(nodo->getDcho(), k);
    }
public:
    AB() : raiz(nullptr) {}
    virtual ~AB() { }
    virtual bool insertar(const Key& k) = 0;
    bool buscar(const Key& k) const { return buscarRec(raiz, k); }

    void inordenRec(NodoB<Key>* nodo) const {
        if (!nodo) return;
        inordenRec(nodo->getIzdo());
        std::cout << nodo->getDato() << " ";
        inordenRec(nodo->getDcho());
    }
    void inorden() const {
        inordenRec(raiz);
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
        if (!arbol.raiz) {
            os << "Nivel 0: [.]" << std::endl;
            return os;
        }
        std::queue<NodoB<Key>*> q;
        q.push(arbol.raiz);
        int nivel = 0;
        while (!q.empty()) {
            int sz = q.size();
            os << "Nivel " << nivel << ": ";
            for (int i = 0; i < sz; ++i) {
                NodoB<Key>* n = q.front(); q.pop();
                if (n) {
                    // si es AVL, mostrar factor de balance
                    if (auto avl = dynamic_cast<NodoAVL<Key>*>(n)) {
                        os << "[" << avl->getDato() << "(" << avl->getBalance() << ")] ";
                    } else {
                        os << "[" << n->getDato() << "] ";
                    }
                    q.push(n->getIzdo());
                    q.push(n->getDcho());
                } else {
                    os << "[.] ";
                }
            }
            os << std::endl;
            nivel++;
        }
        return os;
    }
};

#endif // AB_H