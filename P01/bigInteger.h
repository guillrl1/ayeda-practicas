#include "bigUnsigned.h"

class BigInteger {
 public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned&); // Constructor de cambio de tipo
  BigInteger(const BigInteger&); // Constructor de copia
  BigInteger& operator=(const BigInteger&);
  friend ostream& operator<<(ostream&, const BigInteger&);
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
  
 private:
  bool sign_;
  BigUnsigned number_;
};