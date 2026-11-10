#include <iostream>
#include <map>
#include <functional>
#include <cstdlib>
#include "nif.h"
#include "dispersionFunction.h"
#include "explorationFunction.h"
#include "hashTable.h"
#include "Sequence.h"

using namespace std;

// Estructura para almacenar configuración de la tabla hash
struct Config {
    unsigned tableSize = 0;
    string fdType;
    string hashType;
    unsigned blockSize = 0;
    string feType;
};

// Función que imprime la ayuda
void printHelp() {
    cout << "Uso: ./practica -ts <tablaSize> -fd <f> -hash <open|close> [-bs <blockSize>] [-fe <fExpl>]\n";
    cout << "Funciones de dispersión: modulo, sum, pseudo\n";
    cout << "Funciones de exploración: linear, quadratic, double, redisp\n";
}

// Función para procesar los argumentos de la línea de comandos
Config parseArguments(int argc, char* argv[]) {
    Config config;
    map<string, function<void(string)>> handlers = {
        {"-ts", [&](string value) { config.tableSize = stoi(value); }},
        {"-fd", [&](string value) { config.fdType = value; }},
        {"-hash", [&](string value) { config.hashType = value; }},
        {"-bs", [&](string value) { config.blockSize = stoi(value); }},
        {"-fe", [&](string value) { config.feType = value; }}
    };

    for (int i = 1; i < argc - 1; i += 2) {
        if (handlers.count(argv[i])) {
            handlers[argv[i]](argv[i + 1]);
        }
    }

    return config;
}

// Función para crear la función de dispersión
DispersionFunction<nif>* createDispersionFunction(const string& type, unsigned tableSize) {
    if (type == "modulo") return new ModuloDispersion<nif>(tableSize);
    if (type == "sum") return new SumBasedDispersion<nif>(tableSize);
    if (type == "pseudo") return new PseudoRandomDispersion<nif>(tableSize);
    cout << "Función de dispersión no reconocida.\n";
    exit(1);
}

// Función para crear la función de exploración
ExplorationFunction<nif>* createExplorationFunction(const string& type, const DispersionFunction<nif>& dispersion) {
    if (type == "linear") return new LinearExploration<nif>();
    if (type == "quadratic") return new QuadraticExploration<nif>();
    if (type == "double") return new DoubleDispersion<nif>(dispersion);
    if (type == "redisp") return new Redispersion<nif>();
    cout << "Función de exploración no reconocida.\n";
    exit(1);
}

// Función que ejecuta el menú interactivo
template<typename TableType>
void runMenu(TableType& hashTable) {
    while (true) {
        cout << "\nMenú:\n1. Insertar\n2. Buscar\n0. Salir\nOpción: ";
        int option;
        cin >> option;

        switch (option) {
            case 1: {
                long num;
                cout << "Introduce un número de 8 dígitos (o 0 para generar aleatorio): ";
                cin >> num;
                nif key = (num == 0 ? nif() : nif(num));
                if (hashTable.insert(key))
                    cout << "Insertado: " << key << endl;
                else
                    cout << "Error: clave ya existente o espacio lleno.\n";
                break;
            }
            case 2: {
                long num;
                cout << "Introduce el número a buscar: ";
                cin >> num;
                nif key(num);
                cout << (hashTable.search(key) ? "Clave encontrada.\n" : "Clave no encontrada.\n");
                break;
            }
            case 0:
                return;
            default:
                cout << "Opción no válida.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));

    if (argc < 5) {
        printHelp();
        return 1;
    }

    Config config = parseArguments(argc, argv);
    if (config.tableSize == 0) {
        cout << "Error: Tamaño de tabla inválido.\n";
        return 1;
    }

    // Crear función de dispersión
    DispersionFunction<nif>* dispersion = createDispersionFunction(config.fdType, config.tableSize);

    if (config.hashType == "open") {
        // Dispersión abierta (no requiere exploración)
        HashTable<nif, dynamicSequence<nif>> hashTable(config.tableSize, *dispersion);
        runMenu(hashTable);

    } else if (config.hashType == "close") {
        // Validar parámetros adicionales para dispersión cerrada
        if (config.blockSize == 0 || config.feType.empty()) {
            cout << "Error: Dispersión cerrada requiere blockSize y función de exploración.\n";
            return 1;
        }

        ExplorationFunction<nif>* exploration = createExplorationFunction(config.feType, *dispersion);
        HashTable<nif, staticSequence<nif>> hashTable(config.tableSize, *dispersion, *exploration, config.blockSize);
        runMenu(hashTable);
        delete exploration;

    } else {
        cout << "Error: Tipo de dispersión no reconocido (usa 'open' o 'close').\n";
        return 1;
    }

    delete dispersion;
    return 0;
}
