#include "bigUnsigned.h"
using namespace std;

BigUnsigned::BigUnsigned(unsigned n) {
  if (n == 0) {
    digits_.push_back(0);
  }
  while (n > 0) {
    digits_.push_back((n % 10));
    n /= 10;
  }
}

BigUnsigned::BigUnsigned(const unsigned char* num) {
  // Almacenados en orden inverso
  while (*num) {
    digits_.insert(digits_.begin(), *num - '0');
    ++num;
  }
}

BigUnsigned::BigUnsigned(const BigUnsigned& other) {
  digits_ = other.digits_;
}

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& num) {
  digits_ = num.digits_;
  return *this;
}

ostream& operator<<(ostream&, const BigUnsigned& num) {
  for(int i = num.digits_.size() - 1 ; i >= 0; i--) {
    cout << static_cast<char>(num.digits_[i] + '0');
  }
  return cout;
}

bool BigUnsigned::operator==(const BigUnsigned& num) const {
  return digits_ == num.digits_;
}

bool operator<(const BigUnsigned& num, const BigUnsigned& other) {
  if (num.digits_.size() != other.digits_.size()) {
    return num.digits_.size() < other.digits_.size();
  }
  for (int i = num.digits_.size() - 1; i >= 0; i--) {
    if (num.digits_[i] != other.digits_[i]) {
      return num.digits_[i] < other.digits_[i];
    }
  }
  return false;
}

bool operator>(const BigUnsigned& num, const BigUnsigned& other) {
  return !(num == other) && !(num < other);
}

void BigUnsigned::Normalize() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
    }
}

BigUnsigned& BigUnsigned::operator++() { // Pre-incremento (++x)
  BigUnsigned a = *this;
  const unsigned char num[] = "1";
  BigUnsigned b(num);
  *this = a + b;
  return *this;
}

BigUnsigned BigUnsigned::operator++(int) { // Post-incremento (x++)
  BigUnsigned temp(*this);
  ++(*this);
  return temp;
}


BigUnsigned& BigUnsigned::operator--() { // Predecremento (--x)
    BigUnsigned a = *this;
    const unsigned char num[] = "1";
    BigUnsigned b(num);
    *this = a - b;
    return *this;
}

BigUnsigned BigUnsigned::operator--(int) { // Postdecremento (x--)
    BigUnsigned temp(*this);
    --(*this);
    return temp;
}

BigUnsigned operator+(const BigUnsigned& num, const BigUnsigned& other) {
    unsigned carry = 0;
    BigUnsigned result;
    result.digits_.resize(max(num.digits_.size(), other.digits_.size()) + 1);  // Asegurar espacio suficiente

    for (size_t i = 0; i < result.digits_.size(); i++) {
        int sum = carry;
        if (i < num.digits_.size()) {
            sum += num.digits_[i];
        }
        if (i < other.digits_.size()) {
            sum += other.digits_[i];
        }

        result.digits_[i] = sum % 10;
        carry = sum / 10;
    }

    // Eliminar ceros a la izquierda
    result.Normalize();

    return result;
}

BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
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
          difference += 10;  // Pedir prestado
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

BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  BigUnsigned multiplicando, multiplicador, result, iterador;
  *this < other ? (multiplicando = *this, multiplicador = other) : (multiplicando = other, multiplicador = *this);
  while(iterador < multiplicador) {
    result = result + multiplicando;
    iterador++;
  }
  return result;
}

BigUnsigned operator/(const BigUnsigned& num, const BigUnsigned& other) {
  BigUnsigned cociente;
  BigUnsigned dividendo = num;
  BigUnsigned divisor = other;
  while(divisor < dividendo | divisor == dividendo) {
    dividendo = dividendo - divisor;
    cociente++;
  }
  return cociente;
}

BigUnsigned BigUnsigned::operator%(const BigUnsigned& other) const {
  BigUnsigned zero;
  if (other == zero) return zero;
  BigUnsigned resto = *this;
  while (resto > other || resto == other) {
    resto = resto - other;
  }
  return resto;
}