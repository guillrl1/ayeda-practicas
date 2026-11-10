#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

#include "ABB.h"
#include "AVL.h"
#include "ABE.h"

// ---------------------- Clase NIF ----------------------
class nif {
    std::string val;
public:
    static int comparaciones;

    nif(const std::string& s = "") : val(s) {}

    bool operator<(const nif& o) const {
        ++comparaciones;
        return val < o.val;
    }

    bool operator>(const nif& o) const {
        ++comparaciones;
        return val > o.val;
    }

    bool operator==(const nif& o) const {
        ++comparaciones;
        return val == o.val;
    }

    bool operator!=(const nif& o) const {
        ++comparaciones;
        return val != o.val;
    }

    static nif random() {
        int num = std::rand() % 100000000;
        char letter = 'A' + std::rand() % 26;
        return nif(std::to_string(num) + letter);
    }

    friend std::istream& operator>>(std::istream& is, nif& x) {
        return is >> x.val;
    }

    friend std::ostream& operator<<(std::ostream& os, const nif& x) {
        return os << x.val;
    }
};

int nif::comparaciones = 0;

// ---------------------- Main ----------------------
int main() {
    std::srand(std::time(nullptr));

    const int n = 4; // 10^n elementos
    const int totalClaves = std::pow(10, n);
    const int busquedas = 50;

    // Generar claves únicas
    std::vector<nif> claves;
    claves.reserve(totalClaves);
    for (int i = 0; i < totalClaves; ++i)
        claves.push_back(nif::random());

    // Seleccionar 50 al azar para buscar
    std::vector<nif> clavesBuscar;
    for (int i = 0; i < busquedas; ++i)
        clavesBuscar.push_back(claves[std::rand() % totalClaves]);

    // -------- ABB --------
    ABB<nif> abb;
    for (const auto& k : claves) abb.insertar(k);

    int maxAbb = 0, totalAbb = 0;
    for (const auto& k : clavesBuscar) {
        nif::comparaciones = 0;
        abb.buscar(k);
        totalAbb += nif::comparaciones;
        maxAbb = std::max(maxAbb, nif::comparaciones);
    }

    // -------- AVL --------
    AVL<nif> avl;
    for (const auto& k : claves) avl.insertar(k);

    int maxAvl = 0, totalAvl = 0;
    for (const auto& k : clavesBuscar) {
        nif::comparaciones = 0;
        avl.buscar(k);
        totalAvl += nif::comparaciones;
        maxAvl = std::max(maxAvl, nif::comparaciones);
    }

    // -------- ABE --------
    ABE<nif> abe;
    for (const auto& k : claves) abe.insertar(k);

    int maxAbe = 0, totalAbe = 0;
    for (const auto& k : clavesBuscar) {
        nif::comparaciones = 0;
        abe.buscar(k);
        totalAbe += nif::comparaciones;
        maxAbe = std::max(maxAbe, nif::comparaciones);
    }

    // -------- Resultados --------
    std::cout << "Búsqueda de " << busquedas << " claves entre " << totalClaves << " elementos:\n";
    std::cout << "\n[ABB]  Comparaciones totales: " << totalAbb << ", Máximo en una búsqueda: " << maxAbb;
    std::cout << "\n[AVL]  Comparaciones totales: " << totalAvl << ", Máximo en una búsqueda: " << maxAvl;
    std::cout << "\n[ABE]  Comparaciones totales: " << totalAbe << ", Máximo en una búsqueda: " << maxAbe;
    std::cout << std::endl;

    return 0;
}
