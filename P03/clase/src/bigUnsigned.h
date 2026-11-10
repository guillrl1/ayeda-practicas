#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "bigNumber.h"
#include "bigInteger.h"
#include "bigRational.h"

using namespace std;

/**
 * @brief Clase que representa números grandes sin signo en una base especificada.
 * 
 * La clase BigUnsigned hereda de BigNumber<Base> y permite realizar operaciones
 * aritméticas y lógicas con números de gran tamaño en cualquier base entre 2 y 16.
 * 
 * @tparam Base La base en la que se representará el número (debe ser entre 2 y 16).
 */
template<unsigned char Base> 
class BigUnsigned : public BigNumber<Base> {
 public:
  /**
   * @brief Constructor por defecto que inicializa el número a 0.
   * 
   * @param n Valor inicial del número (por defecto 0).
   */
  BigUnsigned(unsigned n = 0);

  /**
   * @brief Constructor que inicializa el número a partir de una cadena de caracteres en base `Base`.
   * 
   * @param num Cadena que representa el número en base `Base`.
   */
  BigUnsigned(const unsigned char* num);

  /**
   * @brief Constructor que inicializa el número a partir de una cadena de caracteres en base `Base`.
   * 
   * @param str Cadena que representa el número en base `Base`.
   */
  BigUnsigned(const string& str);

  /**
   * @brief Constructor de copia.
   * 
   * @param other Otro objeto BigUnsigned del cual se copiarán los valores.
   */
  BigUnsigned(const BigUnsigned& other);

  /**
   * @brief Operador de asignación.
   * 
   * @param num Otro objeto BigUnsigned del cual se copiarán los valores.
   * @return Referencia al objeto actual.
   */
  BigUnsigned& operator=(const BigUnsigned& num);

  /**
   * @brief Operador de salida para imprimir el número en la base especificada.
   * 
   * @param os Flujo de salida.
   * @param num Objeto BigUnsigned a imprimir.
   * @return El flujo de salida.
   */
  template<unsigned char B> 
  friend ostream& operator<<(ostream&, const BigUnsigned<B>&);

  /**
   * @brief Operador de igualdad.
   * 
   * @param num Otro objeto BigUnsigned con el cual se comparará.
   * @return true si los números son iguales, false si son diferentes.
   */
  bool operator==(const BigUnsigned&) const;

  /**
   * @brief Operador de menor que.
   * 
   * @param other Otro objeto BigUnsigned con el cual se comparará.
   * @return true si el número es menor que el otro, false en caso contrario.
   */
  bool operator<(const BigUnsigned&) const;

  /**
   * @brief Operador de mayor que.
   * 
   * @param other Otro objeto BigUnsigned con el cual se comparará.
   * @return true si el número es mayor que el otro, false en caso contrario.
   */
  bool operator>(const BigUnsigned&) const;

  /**
   * @brief Operador de pre-incremento.
   * 
   * @return El objeto incrementado.
   */
  BigUnsigned& operator++();

  /**
   * @brief Operador de post-incremento.
   * 
   * @param int Argumento innecesario para distinguir el tipo de operador.
   * @return El objeto antes del incremento.
   */
  BigUnsigned operator++(int);

  /**
   * @brief Operador de pre-decremento.
   * 
   * @return El objeto decrementado.
   */
  BigUnsigned& operator--();

  /**
   * @brief Operador de post-decremento.
   * 
   * @param int Argumento innecesario para distinguir el tipo de operador.
   * @return El objeto antes del decremento.
   */
  BigUnsigned operator--(int);

  /**
   * @brief Operador de suma.
   * 
   * @param other Otro objeto BigUnsigned con el cual se sumará.
   * @return El resultado de la suma.
   */
  BigUnsigned operator+(const BigUnsigned&) const;

  /**
   * @brief Operador de resta.
   * 
   * @param other Otro objeto BigUnsigned con el cual se restará.
   * @return El resultado de la resta.
   */
  BigUnsigned operator-(const BigUnsigned&) const;

  /**
   * @brief Operador de multiplicación.
   * 
   * @param other Otro objeto BigUnsigned con el cual se multiplicará.
   * @return El resultado de la multiplicación.
   */
  BigUnsigned operator*(const BigUnsigned&) const;

  /**
   * @brief Operador de división.
   * 
   * @param other Otro objeto BigUnsigned con el cual se dividirá.
   * @return El cociente de la división.
   */
  BigUnsigned operator/(const BigUnsigned&) const;

  /**
   * @brief Operador de módulo.
   * 
   * @param other Otro objeto BigUnsigned con el cual se calculará el resto.
   * @return El resto de la división.
   */
  BigUnsigned operator%(const BigUnsigned&) const;

  /**
   * @brief Normaliza el número, eliminando los ceros a la izquierda.
   */
  void Normalize();

  // Métodos heredados de BigNumber
  BigNumber<Base>* add(const BigNumber<Base>&) const override;
  BigNumber<Base>* subtract(const BigNumber<Base>&) const override;
  BigNumber<Base>* multiply(const BigNumber<Base>&) const override;
  BigNumber<Base>* divide(const BigNumber<Base>&) const override;
  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&) override;

  /**
   * @brief Convierte el objeto BigUnsigned en un objeto BigUnsigned del mismo tipo.
   * 
   * @return El objeto BigUnsigned.
   */
  operator BigUnsigned<Base>() const override { return *this; }

  /**
   * @brief Convierte el objeto BigUnsigned en un objeto BigInteger.
   * 
   * @return El objeto BigInteger equivalente.
   */
  operator BigInteger<Base>() const override { return BigInteger<Base>(*this); }

  /**
   * @brief Convierte el objeto BigUnsigned en un objeto BigRational.
   * 
   * @return El objeto BigRational equivalente.
   */
  operator BigRational<Base>() const override { return BigRational<Base>(BigInteger<Base>(*this), BigUnsigned<Base>{1}); }

  operator BigComplex<Base>() const override { return BigComplex<Base>(BigInteger<Base>(*this), BigInteger<Base>{0}); }

 private:
  vector<unsigned char> digits_; ///< Almacena los dígitos del número en base `Base`.
};

template<unsigned char Base> BigUnsigned<Base>::BigUnsigned(unsigned n) {
  if (n == 0) {
    digits_.push_back(0);
  }
  while (n > 0) {
    digits_.push_back((n % Base));
    n /= Base;
  }
}

template<unsigned char Base> 
BigUnsigned<Base>::BigUnsigned(const unsigned char* num) {
  // Convertir desde una cadena en base `Base`
  while (*num) {
    if (*num >= '0' && *num <= '9') {
      digits_.insert(digits_.begin(), *num - '0');
    } else if (*num >= 'A' && *num <= 'F') {
      digits_.insert(digits_.begin(), *num - 'A' + 10);
    } else if (*num >= 'a' && *num <= 'f') {
      digits_.insert(digits_.begin(), *num - 'a' + 10);
    }
    ++num;
  }
}

template<unsigned char Base> BigUnsigned<Base>::BigUnsigned(const string& str) {
  // Convertir desde una cadena en base `Base`
  for (char c : str) {
    if (c >= '0' && c <= '9') {
      digits_.insert(digits_.begin(), c - '0');
    } else if (c >= 'A' && c <= 'F') {
      digits_.insert(digits_.begin(), c - 'A' + 10);
    } else if (c >= 'a' && c <= 'f') {
      digits_.insert(digits_.begin(), c - 'a' + 10);
    }
  }
}

template<unsigned char Base> BigUnsigned<Base>::BigUnsigned::BigUnsigned(const BigUnsigned& other) {
  digits_ = other.digits_;
}

template<unsigned char Base> BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned& num) {
  digits_ = num.digits_;
  return *this;
}
template<unsigned char Base> 
ostream& operator<<(ostream& os, const BigUnsigned<Base>& num) {
  for (int i = num.digits_.size() - 1; i >= 0; i--) {
    if (num.digits_[i] < 10) {
      os << static_cast<char>(num.digits_[i] + '0');
    } else {
      os << static_cast<char>(num.digits_[i] - 10 + 'A');
    }
  }
  return os;
}

template<unsigned char Base> bool BigUnsigned<Base>::operator==(const BigUnsigned& num) const {
  return digits_ == num.digits_;
}

template<unsigned char Base>
bool BigUnsigned<Base>::operator<(const BigUnsigned<Base>& other) const {
  if (this->digits_.size() != other.digits_.size()) {
    return this->digits_.size() < other.digits_.size();
  }
  for (int i = this->digits_.size() - 1; i >= 0; i--) {
    if (this->digits_[i] != other.digits_[i]) {
      return this->digits_[i] < other.digits_[i];
    }
  }
  return false;
}

template<unsigned char Base>
bool BigUnsigned<Base>::operator>(const BigUnsigned<Base>& other) const {
  return !(*this == other) && !(*this < other);
}

template<unsigned char Base>
void BigUnsigned<Base>::Normalize() {
  while (digits_.size() > 1 && digits_.back() == 0) {
      digits_.pop_back();
  }
}

template<unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator++() { // Pre-incremento (++x)
  BigUnsigned a = *this;
  const unsigned char num[] = "1";
  BigUnsigned b(num);
  *this = a + b;
  return *this;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator++(int) { // Post-incremento (x++)
  BigUnsigned temp(*this);
  ++(*this);
  return temp;
}

template<unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator--() { // Predecremento (--x)
    BigUnsigned a = *this;
    const unsigned char num[] = "1";
    BigUnsigned b(num);
    *this = a - b;
    return *this;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator--(int) { // Postdecremento (x--)
    BigUnsigned temp(*this);
    --(*this);
    return temp;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator+(const BigUnsigned<Base>& other) const {
  unsigned carry = 0;
  BigUnsigned<Base> result;
  result.digits_.resize(max(this->digits_.size(), other.digits_.size()) + 1);  // Asegurar espacio suficiente

  for (size_t i = 0; i < result.digits_.size(); i++) {
      int sum = carry;
      if (i < this->digits_.size()) {
          sum += this->digits_[i];
      }
      if (i < other.digits_.size()) {
          sum += other.digits_[i];
      }

      result.digits_[i] = sum % Base;
      carry = sum / Base;
  }

  // Eliminar ceros a la izquierda
  result.Normalize();

  return result;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& other) const {
  if (*this < other) {
      return BigUnsigned();  // Devuelve un BigUnsigned vacío si no se puede restar.
  }

  unsigned carry = 0;
  BigUnsigned result;
  result.digits_.resize(digits_.size());  // Asegurar espacio suficiente

  for (size_t i = 0; i < digits_.size(); ++i) {
      int subtrahend = (i < other.digits_.size()) ? other.digits_[i] : 0;
      int difference = digits_[i] - subtrahend - carry;

      if (difference < 0) {
          difference += Base;  // Pedir prestado
          carry = 1;
      } else {
          carry = 0;
      }

      result.digits_[i] = difference;
  }

  // Eliminar ceros a la izquierda
  result.Normalize();

  return result;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& other) const {
  BigUnsigned multiplicando, multiplicador, result, iterador;
  *this < other ? (multiplicando = *this, multiplicador = other) : (multiplicando = other, multiplicador = *this);
  while(iterador < multiplicador) {
    result = result + multiplicando;
    iterador++;
  }
  return result;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator/(const BigUnsigned<Base>& other) const {
  BigUnsigned<Base> cociente;
  BigUnsigned dividendo = *this;
  BigUnsigned divisor = other;
  while(divisor < dividendo | divisor == dividendo) {
    dividendo = dividendo - divisor;
    cociente++;
  }
  return cociente;
}

template<unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& other) const {
  BigUnsigned zero;
  if (other == zero) return zero;
  BigUnsigned resto = *this;
  while (resto > other || resto == other) {
    resto = resto - other;
  }
  return resto;
}


// ------------------------ BigNumber ------------------------

template<unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::add(const BigNumber<Base>& other) const {
  if (dynamic_cast<const BigInteger<Base>*>(&other)) {
    return new BigInteger<Base>(static_cast<BigInteger<Base>>(*this) + static_cast<BigInteger<Base>>(other));
  } else if (dynamic_cast<const BigUnsigned<Base>*>(&other)) {
    return new BigUnsigned<Base>(*this + static_cast<BigUnsigned<Base>>(other));
  } else {
    return new BigRational<Base>(static_cast<BigRational<Base>>(*this) + static_cast<BigRational<Base>>(other));
  }
}
template<unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::subtract(const BigNumber<Base>& other) const {
  if (dynamic_cast<const BigInteger<Base>*>(&other)) {
    return new BigInteger<Base>(static_cast<BigInteger<Base>>(*this) - static_cast<BigInteger<Base>>(other));
  } else if (dynamic_cast<const BigUnsigned<Base>*>(&other)) {
    return new BigUnsigned<Base>(*this - static_cast<BigUnsigned<Base>>(other));
  } else {
    return new BigRational<Base>(static_cast<BigRational<Base>>(*this) - static_cast<BigRational<Base>>(other));
  }
}
template<unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::multiply(const BigNumber<Base>& other) const {
  if (dynamic_cast<const BigInteger<Base>*>(&other)) {
    return new BigInteger<Base>(static_cast<BigInteger<Base>>(other) * static_cast<BigInteger<Base>>(*this));
  } else if (dynamic_cast<const BigUnsigned<Base>*>(&other)) {
    return new BigUnsigned<Base>(*this * static_cast<BigUnsigned<Base>>(other));
  } else {
    return new BigRational<Base>(static_cast<BigRational<Base>>(*this) * static_cast<BigRational<Base>>(other));
  }
}
template<unsigned char Base>
BigNumber<Base>* BigUnsigned<Base>::divide(const BigNumber<Base>& other) const {
  if (dynamic_cast<const BigInteger<Base>*>(&other)) {
    return new BigInteger<Base>(static_cast<BigInteger<Base>>(*this) / static_cast<BigInteger<Base>>(other));
  } else if (dynamic_cast<const BigUnsigned<Base>*>(&other)) {
    return new BigUnsigned<Base>(*this / static_cast<BigUnsigned<Base>>(other));
  } else {
    return new BigRational<Base>(static_cast<BigRational<Base>>(*this) / static_cast<BigRational<Base>>(other));
  }
}
template<unsigned char Base>
std::ostream& BigUnsigned<Base>::write(std::ostream& os) const {
  os << *this;
  return os;
}
template<unsigned char Base>
std::istream& BigUnsigned<Base>::read(std::istream& is) {
  std::string str;
  is >> str;
  *this = BigUnsigned(str.c_str());
  return is;
}
#endif // BIGUNSIGNED_H