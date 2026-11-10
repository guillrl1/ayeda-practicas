#include "bigRational.h"
#include <iostream>

using namespace std;

int main() {
  cout << "Primer ejemplo: " << endl;
// Base = 2
// N1 = 1111111111 / 1010101010
// N2 = -1000000001 / 1010101010
  // BigInteger<2> k(15);
  // BigInteger<2> m(15);
  // BigUnsigned<2> n(10);
  // BigUnsigned<2> o(10);

  // BigRational<2> i(k, n);
  // BigRational<2> j(m, o);
  // cout << "i: " << i << endl;
  // cout << "j: " << j << endl;
  // cout << i << " + " << j << " = " << i + j << endl;
  // cout << i << " - " << j << " = " << i - j << endl;
  // cout << i << " * " << j << " = " << i * j << endl;
  // //cout << i << " / " << j << " = " << i / j << endl;
  // cout << i << " == " << j << " = " << (i == j) << endl;
  // cout << i << " < " << j << " = " << (i < j) << endl;
  // cout << i << " > " << j << " = " << (i > j) << endl;

  cout << "Segundo ejemplo: " << endl;
  BigRational<10> e(-1234567890, 617283945);
  BigRational<10> f(1234567890, 246913578);
  cout << "e: " << e << endl;
  cout << "f: " << f << endl;
  cout << e << " + " << f << " = " << e + f << endl;  
  cout << e << " - " << f << " = " << e - f << endl;
  cout << e << " * " << f << " = " << e * f << endl;
  cout << e << " / " << f << " = " << e / f << endl;
  cout << e << " == " << f << " = " << (e == f) << endl;
  cout << e << " < " << f << " = " << (e < f) << endl;
  cout << e << " > " << f << " = " << (e > f) << endl;

  cout << "Tercer ejemplo: " << endl;
  const unsigned char num[] = "1234567890ABC";
  const unsigned char num2[] = "24680ABCDEF";
  BigUnsigned<16> a(num);
  BigUnsigned<16> b(num2);
  BigInteger<16> c(a);
  BigInteger<16> d(b);

  BigRational<16> g(c, a);
  BigRational<16> h(d, b);
  cout << "g: " << g << endl;
  cout << "h: " << h << endl;
  cout << g << " + " << h << " = " << g + h << endl;
  cout << g << " - " << h << " = " << g - h << endl;
  cout << g << " * " << h << " = " << g * h << endl;
  cout << g << " / " << h << " = " << g / h << endl;  
  cout << g << " == " << h << " = " << (g == h) << endl;
  cout << g << " < " << h << " = " << (g < h) << endl;

}