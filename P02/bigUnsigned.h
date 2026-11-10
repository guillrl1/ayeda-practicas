#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
template<unsigned char Base> class BigUnsigned {
 public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char*);
  BigUnsigned(const BigUnsigned&); // Constructor de copia
  BigUnsigned& operator=(const BigUnsigned&);
  template<unsigned char B> 
  friend ostream& operator<<(ostream&, const BigUnsigned<B>&);
  //friend istream& operator>>(istream&, BigUnsigned&); 
  bool operator==(const BigUnsigned&) const;
  bool operator<(const BigUnsigned&) const;
  bool operator>(const BigUnsigned&) const;
  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento
  BigUnsigned operator+(const BigUnsigned&) const;
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  BigUnsigned operator/(const BigUnsigned&) const;
  BigUnsigned operator%(const BigUnsigned&) const;
  void Normalize();
 private:
  vector<unsigned char> digits_;
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

#endif // BIGUNSIGNED_H