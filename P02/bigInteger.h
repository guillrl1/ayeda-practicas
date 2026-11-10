#include "bigUnsigned.h"
#include <iostream>
#include <string>

using namespace std;

template<unsigned char Base> class BigInteger {
 public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned<Base>&); // Constructor de cambio de tipo
  BigInteger(const BigInteger&); // Constructor de copia
  BigInteger& operator=(const BigInteger&);
  template<unsigned char B>
  friend ostream& operator<<(ostream&, const BigInteger<B>&);
  template<unsigned char B>
  friend istream& operator>>(istream&, BigInteger<B>&);
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;
  bool operator<(const BigInteger&) const;
  bool operator>(const BigInteger&) const;
  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator/(const BigInteger&) const;
  BigInteger operator%(const BigInteger&) const;
  BigInteger& operator++(); // Pre-incremento
  BigInteger operator++(int); // Post-incremento
  BigInteger& operator--(); // Pre-decremento
  BigInteger operator--(int); // Post-decremento
  BigUnsigned<Base> getNumber() { return number_; }
  bool getSign() { return sign_; }
  void setSign(bool sign) { sign_ = sign; }
  BigUnsigned<Base> getAbsoluteValue() const { return number_; }

 private:
  bool sign_;
  BigUnsigned<Base> number_;
};

template<unsigned char Base> BigInteger<Base>::BigInteger(int n) {
  if (n < 0) {
    sign_ = true;
    n = -n;
  }
  else { sign_ = false; }
  number_ = BigUnsigned<Base>(static_cast<unsigned>(n));
}

template<unsigned char Base> BigInteger<Base>::BigInteger(const BigUnsigned<Base>& number) {   // Constructor de cambio de tipo
  number_ = number;
  sign_ = false;
}

template<unsigned char Base> BigInteger<Base>::BigInteger(const BigInteger& other) { // Constructor de copia
  *this = other;
}

template<unsigned char Base> BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger& num) {
  sign_ = num.sign_;
  number_ = num.number_;
  return *this;
}

template<unsigned char Base> ostream& operator<<(ostream& os, const BigInteger<Base>& num) {
  if (num.sign_) {
    os << '-';
  }
  os << num.number_;
  return os;
}

template<unsigned char Base> 
istream& operator>>(istream& is, BigInteger<Base>& num) {
  string str;
  is >> str; // Leer la entrada como string

  if (!str.empty() && str[0] == '-') { // Verificar si el número es negativo
    num.sign_ = true;
    str = str.substr(1); // Remover el signo para procesar el número
  } else {
    num.sign_ = false;
  }

  // Convertir la cadena numérica a `BigUnsigned<Base>`
  num.number_ = BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(str.c_str()));

  return is;
}

template<unsigned char Base> bool BigInteger<Base>::operator==(const BigInteger& num) const {
  return sign_ == num.sign_ && number_ == num.number_;
}

template<unsigned char Base> bool BigInteger<Base>::operator!=(const BigInteger& num) const {
  return !(*this == num);
}

template<unsigned char Base> bool BigInteger<Base>::operator<(const BigInteger& num) const {
  if (sign_ != num.sign_) {
    return sign_;  // Si 'this' es negativo y 'num' es positivo, 'this' es menor.
  }
  return (sign_) ? num.number_ < number_ : number_ < num.number_;
}

template<unsigned char Base> bool BigInteger<Base>::operator>(const BigInteger& num) const {
  return !(*this < num) && !(*this == num);
}

template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator+(const BigInteger<Base>& num) const {
  BigInteger result;
  if (sign_ == num.sign_) {
    result.number_ = number_ + num.number_;
    result.sign_ = sign_;
  }
  else {
    if (this->sign_ && !num.sign_) {
      if (number_ < num.number_) {
        result.number_ = num.number_ - number_;
        result.sign_ = false;
      }
      else {
        result.number_ = number_ - num.number_;
        result.sign_ = true;
      }
    }
    else {
      if (number_ < num.number_) {
        result.number_ = num.number_ - number_;
        result.sign_ = true;
      }
      else {
        result.number_ = number_ - num.number_;
        result.sign_ = false;
      }
    }
  }
  return result;
}


template<unsigned char Base> BigInteger<Base>
BigInteger<Base>::operator-(const BigInteger<Base>& num) const {
  BigInteger result;
  if (sign_ != num.sign_) {
    result.number_ = number_ + num.number_;
    result.sign_ = sign_;
  }
  else {
    if (this->sign_ && !num.sign_) {
      if (number_ < num.number_) {
        result.number_ = num.number_ - number_;
        result.sign_ = true;
      }
      else {
        result.number_ = number_ - num.number_;
        result.sign_ = true;
      }
    }
    else {
      if (number_ < num.number_) {
        result.number_ = num.number_ - number_;
        result.sign_ = false;
      }
      else {
        result.number_ = number_ - num.number_;
        result.sign_ = false;
      }
    }
  }
  return result;
}

template<unsigned char Base> BigInteger<Base>
BigInteger<Base>::operator*(const BigInteger<Base>& num) const {
  BigInteger result;
  this->sign_ == num.sign_ ? result.sign_ = false : result.sign_ = true;
  result.number_ = number_ * num.number_;
  return result;
}

template<unsigned char Base> BigInteger<Base>
BigInteger<Base>::operator/(const BigInteger<Base>& num) const {
  BigInteger result;
  this->sign_ == num.sign_ ? result.sign_ = false : result.sign_ = true;
  result.number_ = number_ / num.number_;
  return result;
}

template<unsigned char Base> 
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& num) const {
  BigInteger<Base> result;
  result.sign_ = this->sign_; // El módulo mantiene el signo del dividendo
  result.number_ = this->number_ % num.number_; // Aplicar módulo en `BigUnsigned`
  return result;
}









template<> class BigInteger<2> {
 public:
  BigInteger(int n = 0);
  BigInteger(string str);
  BigInteger(const BigUnsigned<2>&); // Constructor de cambio de tipo
  BigInteger(const BigInteger&); // Constructor de copia
  BigInteger& operator=(const BigInteger&);
  friend ostream& operator<<(ostream& os, const BigInteger<2>& num);
  friend istream& operator>>(istream&, BigInteger&);
  bool operator==(const BigInteger&) const;
  bool operator!=(const BigInteger&) const;
  bool operator<(const BigInteger&) const;
  bool operator>(const BigInteger&) const;
  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator/(const BigInteger&) const;
  BigInteger operator%(const BigInteger&) const;
  BigInteger& operator++(); // Pre-incremento
  BigInteger operator++(int); // Post-incremento
  BigInteger& operator--(); // Pre-decremento
  BigInteger operator--(int); // Post-decremento


  std::vector<bool> getNumber() const { return number_; }
  void complement2();
 private:
  std::vector<bool> number_;
};


BigInteger<2>::BigInteger(int n) {
  bool sign = false;
  if (n < 0) {
    sign = true;
    n = -n;
  }
  while (n > 0) {
    number_.push_back(n % 2);
    n /= 2;
  }
  if(sign) {
    complement2();
  }
  number_.push_back(sign);
}

BigInteger<2>::BigInteger(string str) {
  bool sign = false;
  if (!str.empty() && str[0] == '-') { // Verificar si el número es negativo
    sign = true;
    str = str.substr(1); // Remover el signo para procesar el número
  }
  else { sign = false; }

  for (int i = str.size() - 1; i >= 0; i--) {
    if (str[i] == '0') {
      number_.push_back(false);
    }
    else {
      number_.push_back(true);
    }
  }
  if(sign) {
    complement2();
  }
}


BigInteger<2>::BigInteger(const BigInteger& other) { // Constructor de copia
  *this = other;
}

BigInteger<2>& BigInteger<2>::operator=(const BigInteger& num) {
  number_ = num.number_;
  return *this;
}

bool BigInteger<2>::operator<(const BigInteger<2>& num) const {
  if (number_.back() != num.number_.back()) {
    return number_.back();
  }
  if (number_.size() != num.number_.size()) {
    return number_.size() < num.number_.size();
  }
  for (int i = number_.size() - 2; i >= 0; i--) {
    if (number_[i] != num.number_[i]) {
      return number_[i] < num.number_[i];
    }
  }
  return false;
} 

bool BigInteger<2>::operator>(const BigInteger<2>& num) const {
  return !(*this < num) && !(*this == num);
}

ostream& operator<<(ostream& os, const BigInteger<2>& num) {
  for(int i = num.number_.size() - 1; i >= 0; i--) {
    os << num.number_[i];
  }
  return os;
}

istream& operator>>(istream& is, BigInteger<2>& num) {
  string str;
  is >> str; // Leer la entrada como string

  for(int i = str.size() - 1; i >= 0; i--) {
    if(str[i] == '0') {
      num.number_.push_back(false);
    } else {
      num.number_.push_back(true);
    }
  }

  return is;
}

bool BigInteger<2>::operator==(const BigInteger& num) const {
  return number_ == num.number_;
}

bool BigInteger<2>::operator!=(const BigInteger& num) const {
  return !(*this == num);
}

BigInteger<2> BigInteger<2>::operator+(const BigInteger<2>& num) const {
  BigInteger<2> result;

  // Obtener los números en complemento a 2
  std::vector<bool> a = this->number_;
  std::vector<bool> b = num.number_;

  // Normalizar tamaños con extensión de signo
  size_t max_size = std::max(a.size(), b.size());
  bool sign_a = a.back(); // Bit de signo de A
  bool sign_b = b.back(); // Bit de signo de B

  while (a.size() < max_size) a.push_back(sign_a); // Extender con el bit de signo
  while (b.size() < max_size) b.push_back(sign_b);

  // Agregar un bit extra para manejar desbordamiento
  a.push_back(sign_a);
  b.push_back(sign_b);

  std::vector<bool> sum(a.size(), 0);
  bool carry = 0;

  // Suma binaria bit a bit con acarreo
  for (size_t i = 0; i < a.size(); i++) {
      bool bitA = a[i];
      bool bitB = b[i];

      sum[i] = bitA ^ bitB ^ carry;  // Suma binaria
      carry = (bitA & bitB) | (carry & (bitA ^ bitB)); // Nuevo acarreo
  }

  // **Eliminar bits extra innecesarios**
  // Si el bit de signo esperado es el mismo en los dos últimos bits, eliminamos el último bit
  while (sum.size() > max_size && sum.back() == sum[sum.size() - 2]) {
      sum.pop_back();
  }

  // Asignar el resultado a la instancia
  result.number_ = sum;
  return result;
}


BigInteger<2> BigInteger<2>::operator-(const BigInteger<2>& num) const {
  BigInteger<2> negB = num;  // Copia de B para modificarla
  negB.complement2();        // Calcular -B
  return *this + negB;       // Sumar A + (-B)
}

BigInteger<2> BigInteger<2>::operator*(const BigInteger<2>& num) const {
  // Determinar el signo del resultado
  bool signA = this->number_.back();
  bool signB = num.number_.back();
  bool resultSign = signA ^ signB; // XOR para determinar signo final

  // Convertir a valores positivos si son negativos
  BigInteger<2> a = *this;
  BigInteger<2> b = num;
  if (signA) a.complement2();
  if (signB) b.complement2();

  // Determinar el tamaño máximo del resultado
  size_t sizeA = a.number_.size();
  size_t sizeB = b.number_.size();
  size_t max_size = sizeA + sizeB; // Tamaño máximo posible

  // Inicializar resultado en 0 con el tamaño correcto
  BigInteger<2> result;
  result.number_.resize(max_size, 0);

  // Multiplicación por sumas repetitivas (shift and add)
  for (size_t i = 0; i < b.number_.size(); i++) {
      if (b.number_[i]) { // Si el bit es 1, sumar `a` desplazado
          BigInteger<2> shiftedA = a;
          shiftedA.number_.insert(shiftedA.number_.begin(), i, 0); // Shift left i veces
          result = result + shiftedA;
      }
  }

  // Si el resultado debe ser negativo, aplicar complemento a 2
  if (resultSign) {
      result.complement2();
  }

  return result;
}

BigInteger<2> BigInteger<2>::operator/(const BigInteger<2>& num) const {
  // Verificar división por cero
  if (num == BigInteger<2>(0)) {
      throw std::runtime_error("División por cero");
  }

  // Determinar el signo del resultado
  bool signA = this->number_.back();
  bool signB = num.number_.back();
  bool resultSign = signA ^ signB; // XOR para determinar signo final

  // Convertir a valores absolutos si son negativos
  BigInteger<2> a = *this;
  BigInteger<2> b = num;
  if (signA) a.complement2();
  if (signB) b.complement2();

  // Inicializar cociente en 0 con el tamaño adecuado
  BigInteger<2> quotient(0);
  BigInteger<2> one(1);  // Para incrementar el cociente

  // Restar repetidamente 'b' de 'a' hasta que 'a' sea menor que 'b'
  while (a > b | a == b) {  
      a = a - b;  // Restamos b de a
      quotient = quotient + one;  // Incrementamos el cociente
  }

  // Asegurar que el cociente tiene el tamaño adecuado (eliminamos bits sobrantes)
  while (quotient.number_.size() > 1 && quotient.number_.front() == 0) {
      quotient.number_.erase(quotient.number_.begin()); // Eliminar bits innecesarios
  }

  // Si el resultado debe ser negativo, aplicar complemento a 2
  if (resultSign && quotient != BigInteger<2>(0)) {
      quotient.complement2();
  }

  return quotient - 1;
}

BigInteger<2> BigInteger<2>::operator%(const BigInteger<2>& num) const {
  // Verificar división por cero
  if (num == BigInteger<2>(0)) {
      throw std::runtime_error("División por cero");
  }
  return *this - (*this / num) * num;
}

void BigInteger<2>::complement2() {
  for (int i = 0; i < number_.size(); i++) {
    number_[i] = !number_[i];
  }
  bool carry = true;
  for (int i = 0; i < number_.size(); i++) {
    if (number_[i] && carry) {
      number_[i] = false;
    }
    else if (!number_[i] && carry) {
      number_[i] = true;
      carry = false;
    }
  }
}