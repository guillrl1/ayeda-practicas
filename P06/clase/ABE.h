template<typename Key>
class ABE : public AB<Key> {
    using AB<Key>::raiz;  // Esto permite acceso directo a 'raiz'
public:
    bool insertar(const Key& k) override {
        raiz = insertarRec(raiz, k);
        return true;
    }

    bool buscar(const Key& k) const {
        return buscarRec(raiz, k);
    }

private:
    NodoB<Key>* insertarRec(NodoB<Key>* nodo, const Key& k) {
        if (!nodo) return new NodoB<Key>(k);

        int izq = contarNodos(nodo->getIzdo());
        int dch = contarNodos(nodo->getDcho());

        if (izq <= dch) {
            nodo->setIzdo(insertarRec(nodo->getIzdo(), k));
        } else {
            nodo->setDcho(insertarRec(nodo->getDcho(), k));
        }

        return nodo;
    }

    int contarNodos(NodoB<Key>* nodo) const {
        if (!nodo) return 0;
        return 1 + contarNodos(nodo->getIzdo()) + contarNodos(nodo->getDcho());
    }

    bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
        if (!nodo) return false;
        if (k == nodo->getDato()) return true;
        return buscarRec(nodo->getIzdo(), k) || buscarRec(nodo->getDcho(), k);
    }
};
