#include "bigInteger.h"

template<unsigned char Base> class BigComplex {
  
 public:
  BigComplex() : real_(0), imag_(0) {}
  BigComplex(const BigInteger<Base>& real, const BigInteger<Base>& imag) : real_(real), imag_(imag) {}
  template<unsigned char B>
  friend ostream& operator<<(ostream& os, const BigComplex<B>& num);
  BigComplex operator+(const BigComplex& num) const;

 private:
  BigInteger<Base> real_;
  BigInteger<Base> imag_;
};

template<unsigned char Base>
ostream& operator<<(ostream& os, const BigComplex<Base>& num) {
  os << num.real_ << ", " << num.imag_ << "i";
  return os;
}

template<unsigned char Base>
BigComplex<Base> BigComplex<Base>::operator+(const BigComplex& num) const {
  return BigComplex(real_ + num.real_, imag_ + num.imag_);
}
