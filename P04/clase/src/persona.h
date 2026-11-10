#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>
#include "nif.h"  

class Persona {
private:
    std::string nombre;
    int edad;
    nif clave;  

public:
    Persona() : nombre(""), edad(0), clave() {}

    Persona(std::string nombre, int edad, nif nifValor)
        : nombre(nombre), edad(edad), clave(nifValor) {}

    // Getters
    std::string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    nif getClave() const { return clave; }

    // Setters
    void setNombre(std::string n) { nombre = n; }
    void setEdad(int e) { edad = e; }
    void setClave(nif nifValor) { clave = nifValor; }

    // Operador de comparación
    bool operator==(const Persona& otra) const {
        return clave == otra.clave;
    }

    // Operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Persona& p) {
        os << "Nombre: " << p.nombre << ", Edad: " << p.edad << ", NIF: " << p.clave;
        return os;
    }

    void display() const {
      std::cout << "NIF: " << clave << ", Nombre: " << nombre << ", Edad: " << edad << std::endl;
  }
};

#endif // PERSONA_H
