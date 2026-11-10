#include "bigInteger.h"
#include "bigNumber.h"

template<unsigned char Base> class BigComplex : public BigNumber<Base> {
  
 public:
  BigComplex() : real_(0), imag_(0) {}
  BigComplex(const BigInteger<Base>& real, const BigInteger<Base>& imag) : real_(real), imag_(imag) {}
  template<unsigned char B>
  friend ostream& operator<<(ostream& os, const BigComplex<B>& num);
  BigComplex operator+(const BigComplex& num) const;

  // Virtual functions
  BigNumber<Base>* add(const BigNumber<Base>& num) const override;
  BigNumber<Base>* subtract(const BigNumber<Base>& num) const override {}
  BigNumber<Base>* multiply(const BigNumber<Base>& num) const override {}
  BigNumber<Base>* divide(const BigNumber<Base>& num) const override {}
  ostream& write(ostream& os) const override;
  istream& read(istream& is) override;
  operator BigUnsigned<Base>() const override { return real_.getAbsoluteValue(); }
  operator BigInteger<Base>() const override { return real_; }
  operator BigRational<Base>() const override { return BigRational<Base>(real_, imag_); }
  operator BigComplex<Base>() const override { return *this; }


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

// <<---------------- BigNumber virtual functions -------------
template<unsigned char Base>
BigNumber<Base>* BigComplex<Base>::add(const BigNumber<Base>& num) const {
  const BigComplex<Base>* complex_num = dynamic_cast<const BigComplex<Base>*>(&num);
  
  if (!complex_num) {  
    // Convertimos el número si no es un BigComplex
    BigComplex<Base> converted(static_cast<const BigInteger<Base>&>(num), 0);  
    return new BigComplex<Base>(*this + converted);
  }

  return new BigComplex<Base>(*this + *complex_num);
}

template<unsigned char Base>
ostream& BigComplex<Base>::write(ostream& os) const {
  os << *this;
  return os;
}
template<unsigned char Base>
istream& BigComplex<Base>::read(istream& is) {
  is >> *this;
  return is;
}