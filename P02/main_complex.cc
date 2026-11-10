#include "bigComplex.h"
#include <iostream>

using namespace std;

int main() {
// Base = 2
// N1 = 1111111111  1010101010i
// N2 = -1000000001 - 1010101010i
  cout << "Segundo ejemplo: " << endl;
  // Base = 10
  // N1 = -1234567890 + 617283945i
  // N2 = 1234567890 - 246913578i
  BigInteger<10> a(-1234567890);
  BigInteger<10> b(617283945);
  BigInteger<10> c(1234567890);
  BigInteger<10> d(-246913578);
  BigComplex<10> e(a, b);
  BigComplex<10> f(c, d);
  cout << "e: " << e << endl;
  cout << "f: " << f << endl;
  cout << e << " + " << f << " = " << e + f << endl << endl;

// Base = 16
// N1 = 1234567890ABC + 1234567890ABCi
// N2 = ABCDEF6543210 - 1234567890A01i
  cout << "Tercer ejemplo: " << endl;
  const unsigned char num[] = "1234567890ABC";
  const unsigned char num3[] = "ABCDEF6543210";
  const unsigned char num4[] = "1234567890A01";
  BigInteger<16> g(num);
  BigInteger<16> h(num3);
  BigInteger<16> i(num4);
  BigComplex<16> j(g, g);
  BigComplex<16> k(h, i);
  cout << "j: " << j << endl;
  cout << "k: " << k << endl;
  cout << j << " + " << k << " = " << j + k << endl;


}