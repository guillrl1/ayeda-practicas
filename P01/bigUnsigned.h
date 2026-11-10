#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

class BigUnsigned {

 public:
  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char*);
  BigUnsigned(const BigUnsigned&); // Constructor de copia
  BigUnsigned& operator=(const BigUnsigned&);
  friend ostream& operator<<(ostream&, const BigUnsigned&);
  friend istream& operator>>(istream&, BigUnsigned&); 
  bool operator==(const BigUnsigned&) const;
  friend bool operator<(const BigUnsigned&, const BigUnsigned&);
  friend bool operator>(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento
  friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator%(const BigUnsigned&) const;
  void Normalize();
 private:
  vector<unsigned char> digits_;

};

#endif // BIGUNSIGNED_H