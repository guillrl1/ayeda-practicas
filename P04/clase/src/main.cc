
using namespace std;

#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <cctype>     // isdigit
#include <iostream>   // cout, cin, cerr
#include <string>     // string

#include "nif.h"
#include "hashTable.h"
#include "persona.h"
#include "dispersionFunction.h"
#include "explorationFunction.h"

int main() {
  ModuloDispersion<nif> fd_modulo(10);  // Función de dispersión
  QuadraticExploration<nif> fe_cuadratica(10);  // Función de exploración
  HashTable<Persona, staticSequence<Persona>> tabla(10, fd_modulo, fe_cuadratica, 3);

  int opcion;
  do {
      std::cout << "\nMenú:\n1. Insertar Persona\n2. Buscar Persona por NIF\n0. Salir\nElige una opción: ";
      std::cin >> opcion;

      if (opcion == 1) {
          std::string nombre;
          int edad, numeroDNI;
          std::cout << "Introduce el nombre: ";
          std::cin >> nombre;
          std::cout << "Introduce la edad: ";
          std::cin >> edad;
          std::cout << "Introduce el NIF (sin letra): ";
          std::cin >> numeroDNI;

          Persona nuevaPersona(nombre, edad, nif(numeroDNI));
          if (tabla.insert(nuevaPersona)) {
              std::cout << "Persona insertada con éxito.\n";
          } else {
              std::cout << "No se pudo insertar la persona (posiblemente ya existe o la celda está llena).\n";
          }

      } else if (opcion == 2) {
          int numeroDNI;
          std::cout << "Introduce el NIF a buscar: ";
          std::cin >> numeroDNI;

          Persona personaBuscar("", 0, nif(numeroDNI)); // Solo necesitamos el NIF para buscar
          if (tabla.search(personaBuscar)) {
              std::cout << "Persona encontrada.\n";
          } else {
              std::cout << "Persona no encontrada.\n";
          }
      }
  } while (opcion != 0);

  return 0;
}