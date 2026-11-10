#include "bigInteger.h"

BigInteger::BigInteger(int n) {
  if (n < 0) {
    sign_ = true;
    n = -n;
  }
  else { sign_ = false; }
  number_ = BigUnsigned(n);
}

BigInteger::BigInteger(const BigUnsigned& number) {   // Constructor de cambio de tipo
  number_ = number;
  sign_ = false;
}

BigInteger::BigInteger(const BigInteger& other) { // Constructor de copia
  *this = other;
}

BigInteger& BigInteger::operator=(const BigInteger& num) {
  sign_ = num.sign_;
  number_ = num.number_;
  return *this;
}

ostream& operator<<(ostream& os, const BigInteger& num) {
  if (num.sign_) {
    os << '-';
  }
  os << num.number_;
  return os;
}

istream& operator>>(istream& is, BigInteger& num) {
  string str;
  is >> str;
  if (!str.empty() && str[0] == '-') {
    num.sign_ = true;
    str = str.substr(1);
  }
  else {
    num.sign_ = false;
  }
  num.number_ = BigUnsigned(reinterpret_cast<const unsigned char*>(str.c_str()));
  return is;
}

bool BigInteger::operator==(const BigInteger& num) const {
  return sign_ == num.sign_ && number_ == num.number_;
}

bool BigInteger::operator!=(const BigInteger& num) const {
  return !(*this == num);
}

bool BigInteger::operator<(const BigInteger& num) const {
  if (sign_ != num.sign_) {
    return sign_;  // Si 'this' es negativo y 'num' es positivo, 'this' es menor.
  }
  return (sign_) ? num.number_ < number_ : number_ < num.number_; 
}

bool BigInteger::operator>(const BigInteger& num) const {
  return !(*this < num) && !(*this == num);
}

BigInteger BigInteger::operator+(const BigInteger& num) const {
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

BigInteger BigInteger::operator-(const BigInteger& num) const {
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

BigInteger BigInteger::operator*(const BigInteger& num) const {
  BigInteger result;
  this->sign_ == num.sign_ ? result.sign_ = false : result.sign_ = true;
  result.number_ = number_ * num.number_;
  return result;
}

BigInteger BigInteger::operator/(const BigInteger& num) const {
  BigInteger result;
  this->sign_ == num.sign_ ? result.sign_ = false : result.sign_ = true;
  result.number_ = number_ / num.number_;
  return result;
}

BigInteger& BigInteger::operator++() { // Pre-incremento
  *this = *this + BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator++(int) { // Post-incremento
  BigInteger temp(*this);
  *this = *this + BigInteger(1);
  return temp;
}

BigInteger& BigInteger::operator--() { // Pre-decremento
  *this = *this - BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator--(int) { // Post-decremento
  BigInteger temp(*this);
  *this = *this - BigInteger(1);
  return temp;
}

BigInteger BigInteger::operator%(const BigInteger& num) const {
  BigInteger result;
  this->sign_ == num.sign_ ? result.sign_ = false : result.sign_ = true;
  result.number_ = number_ % num.number_;
  return result;
}


