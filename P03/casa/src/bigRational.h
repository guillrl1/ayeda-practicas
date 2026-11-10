#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H
#include "bigInteger.h"

template<unsigned char Base> class BigRational : public BigNumber<Base> {
  public:
  BigRational(int n = 0, int d = 1) : numerador_(n), denominador_(d) { simplify(); }
  BigRational(const BigInteger<Base>& numerador, const BigUnsigned<Base>& denominador) :
              numerador_(numerador), denominador_(denominador) { simplify(); }

  BigRational<Base> operator+(const BigRational<Base>&) const;
  BigRational<Base> operator-(const BigRational<Base>&) const;
  BigRational<Base> operator*(const BigRational<Base>&) const;
  BigRational<Base> operator/(const BigRational<Base>&) const;
  template<unsigned char B>
  friend ostream& operator<<(ostream& os, const BigRational<B>& num);
  template<unsigned char B>
  friend istream& operator>>(istream& is, BigRational<B>& num);
  bool operator==(const BigRational<Base>&) const;
  bool operator!=(const BigRational<Base>&) const;
  bool operator<(const BigRational<Base>&) const;
  bool operator>(const BigRational<Base>&) const;
  void operator=(const BigRational<Base>&);

  // Virtual functions
  BigNumber<Base>* add(const BigNumber<Base>& num) const override;
  BigNumber<Base>* subtract(const BigNumber<Base>& num) const override;
  BigNumber<Base>* multiply(const BigNumber<Base>& num) const override;
  BigNumber<Base>* divide(const BigNumber<Base>& num) const override;
  ostream& write(ostream& os) const override;
  istream& read(istream& is) override;
  operator BigUnsigned<Base>() const override { return numerador_.getAbsoluteValue() / denominador_; }
  operator BigInteger<Base>() const override { return numerador_ / BigInteger<Base>(denominador_); }
  operator BigRational<Base>() const override { return *this; }

  // Conversion
  BigUnsigned<Base> GCD() const;

 private:
  BigInteger<Base> numerador_;
  BigUnsigned<Base> denominador_;
  void simplify();
};

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& num) const {
  BigRational<Base> result;
  result.numerador_ = numerador_ * BigInteger<Base>(num.denominador_) + num.numerador_ * BigInteger<Base>(denominador_);
  result.denominador_ = denominador_ * num.denominador_;
  result.simplify();
  return result;
}

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& num) const {
  BigRational<Base> result;
  result.numerador_ = numerador_ * BigInteger<Base>(num.denominador_) - num.numerador_ * BigInteger<Base>(denominador_);
  result.denominador_ = denominador_ * num.denominador_;
  result.simplify();
  return result;
}

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& num) const {
  BigRational<Base> result;
  result.numerador_ = numerador_ * num.numerador_;
  result.denominador_ = denominador_ * num.denominador_;
  result.simplify();
  return result;
}

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& num) const {
  BigRational<Base> result;
  result.numerador_ = numerador_ * BigInteger(num.denominador_);
  result.denominador_ = denominador_ * num.numerador_.getAbsoluteValue();
  result.simplify();
  return result;
}

template<unsigned char Base> void BigRational<Base>::simplify() {
  BigUnsigned<Base> gcd = GCD();
  numerador_ = numerador_ / gcd;
  denominador_ = denominador_ / gcd;
}

template<unsigned char Base> ostream& operator<<(ostream& os, const BigRational<Base>& num) {
  os << num.numerador_;
  os << '/' << num.denominador_;
  return os;
}

template<unsigned char Base> istream& operator>>(istream& is, BigRational<Base>& num) {
  char c;
  is >> num.numerador_;
  is.get(c);
  if (c == '/') {
    is >> num.denominador_;
  }
  else {
    num.denominador_ = 1;
  }
  num.simplify();
  return is;
}

template<unsigned char Base> bool BigRational<Base>::operator==(const BigRational<Base>& num) const {
  return numerador_ == num.numerador_ && denominador_ == num.denominador_;
}

template<unsigned char Base> bool BigRational<Base>::operator!=(const BigRational<Base>& num) const {
  return !(*this == num);
}

template<unsigned char Base> bool BigRational<Base>::operator<(const BigRational<Base>& num) const {
  return numerador_ * num.denominador_ < num.numerador_ * denominador_;
}

template<unsigned char Base> bool BigRational<Base>::operator>(const BigRational<Base>& num) const {
  return numerador_ * num.denominador_ > num.numerador_ * denominador_;
}

template<unsigned char Base> void BigRational<Base>::operator=(const BigRational<Base>& num) {
  numerador_ = num.numerador_;
  denominador_ = num.denominador_;
}

template<unsigned char Base>
BigUnsigned<Base> BigRational<Base>::GCD() const {
  BigUnsigned<Base> a = numerador_.getAbsoluteValue();
  BigUnsigned<Base> b = denominador_;
  while (b > BigUnsigned<Base>{}) {
    BigUnsigned<Base> r = a % b;
    a = b;
    b = r;
  }
  return a;
}

// ------------- BigNumber virtual functions -------------
template<unsigned char Base> 
BigNumber<Base>* BigRational<Base>::add(const BigNumber<Base>& num) const {
  const BigRational<Base>* rational_num = dynamic_cast<const BigRational<Base>*>(&num);
  
  if (!rational_num) {  
    // Convertimos el número si no es un BigRational
    BigRational<Base> converted(static_cast<const BigInteger<Base>&>(num));  
    return new BigRational<Base>(*this + converted);
  }

  return new BigRational<Base>(*this + *rational_num);
}

template<unsigned char Base> 
BigNumber<Base>* BigRational<Base>::subtract(const BigNumber<Base>& num) const {
  const BigRational<Base>* rational_num = dynamic_cast<const BigRational<Base>*>(&num);
  
  if (!rational_num) {  
    BigRational<Base> converted(static_cast<const BigInteger<Base>&>(num));  
    return new BigRational<Base>(*this - converted);
  }

  return new BigRational<Base>(*this - *rational_num);
}

template<unsigned char Base> 
BigNumber<Base>* BigRational<Base>::multiply(const BigNumber<Base>& num) const {
  const BigRational<Base>* rational_num = dynamic_cast<const BigRational<Base>*>(&num);
  
  if (!rational_num) {  
    BigRational<Base> converted(static_cast<const BigInteger<Base>&>(num));  
    return new BigRational<Base>(*this * converted);
  }

  return new BigRational<Base>(*this * *rational_num);
}

template<unsigned char Base> 
BigNumber<Base>* BigRational<Base>::divide(const BigNumber<Base>& num) const {
  const BigRational<Base>* rational_num = dynamic_cast<const BigRational<Base>*>(&num);
  
  if (!rational_num) {  
    BigRational<Base> converted(static_cast<const BigInteger<Base>&>(num));  
    return new BigRational<Base>(*this / converted);
  }

  return new BigRational<Base>(*this / *rational_num);
}
template<unsigned char Base> ostream& BigRational<Base>::write(ostream& os) const {
  os << *this;
  return os;
}
template<unsigned char Base> istream& BigRational<Base>::read(istream& is) {
  is >> *this;
  return is;
}
#endif // BIGRATIONAL_H