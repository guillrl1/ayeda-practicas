#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ABB.h"
#include "AVL.h"

// -------- Clase NIF --------
class nif {
    std::string val;
public:
    nif(const std::string& s = "") : val(s) {}
    bool operator<(const nif& o) const { return val < o.val; }
    bool operator>(const nif& o) const { return val > o.val; }
    bool operator==(const nif& o) const { return val == o.val; }
    bool operator!=(const nif& o) const { return val != o.val; }
    friend std::istream& operator>>(std::istream& is, nif& x) { return is >> x.val; }
    friend std::ostream& operator<<(std::ostream& os, const nif& x) { return os << x.val; }
    static nif random() {
        int num = std::rand() % 100000000;
        char letter = 'A' + std::rand() % 26;
        return nif(std::to_string(num) + letter);
    }
};

// -------- Función de uso --------
void usage(const char* prog) {
    std::cout << "Uso: " << prog << " -ab <abb|avl> -init <manual|random s|file s f> [-trace]" << std::endl;
}

int main(int argc, char* argv[]) {
    bool isAVL = false;
    bool trace = false;
    std::string init = "manual", fileName;
    int s = 0;

    // Parseo de argumentos
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-ab" && i + 1 < argc) {
            std::string t = argv[++i];
            if (t == "avl") isAVL = true;
        } else if (arg == "-init" && i + 1 < argc) {
            init = argv[++i];
            if (init == "random" && i + 1 < argc) s = std::stoi(argv[++i]);
            else if (init == "file" && i + 2 < argc) {
                s = std::stoi(argv[++i]);
                fileName = argv[++i];
            }
        } else if (arg == "-trace") {
            trace = true;
        }
    }

    if (argc < 3) {
        usage(argv[0]);
        return 1;
    }

    std::srand(std::time(nullptr)); // Semilla aleatoria

    // -------- AVL o ABB --------
    if (isAVL) {
        AVL<nif> arbol(trace);
        if (init == "random") for (int i = 0; i < s; ++i) arbol.insertar(nif::random());
        else if (init == "file") {
            std::ifstream ifs(fileName);
            nif k;
            while (ifs >> k && s-- > 0) arbol.insertar(k);
        }

        // Menú
        int opt; nif key;
        do {
            std::cout << "\n[0] Salir\n[1] Insertar clave\n[2] Buscar clave\n[3] Mostrar árbol inorden\n> ";
            std::cin >> opt;
            switch (opt) {
                case 1:
                    std::cout << "Insertar: "; std::cin >> key;
                    arbol.insertar(key);
                    std::cout << arbol;
                    break;
                case 2:
                    std::cout << "Buscar: "; std::cin >> key;
                    std::cout << (arbol.buscar(key) ? "Encontrado\n" : "No encontrado\n");
                    break;
                case 3:
                    arbol.inorden();
                    break;
            }
        } while (opt != 0);

    } else {
        ABB<nif> arbol;
        if (init == "random") for (int i = 0; i < s; ++i) arbol.insertar(nif::random());
        else if (init == "file") {
            std::ifstream ifs(fileName);
            nif k;
            while (ifs >> k && s-- > 0) arbol.insertar(k);
        }

        // Menú
        int opt; nif key;
        do {
            std::cout << "\n[0] Salir\n[1] Insertar clave\n[2] Buscar clave\n[3] Mostrar árbol inorden\n> ";
            std::cin >> opt;
            switch (opt) {
                case 1:
                    std::cout << "Insertar: "; std::cin >> key;
                    arbol.insertar(key);
                    std::cout << arbol;
                    break;
                case 2:
                    std::cout << "Buscar: "; std::cin >> key;
                    std::cout << (arbol.buscar(key) ? "Encontrado\n" : "No encontrado\n");
                    break;
                case 3:
                    arbol.inorden();
                    break;
            }
        } while (opt != 0);
    }

    return 0;
}
