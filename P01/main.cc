#include "bigInteger.h"
#include "bigUnsigned.h"

BigInteger mcd(BigInteger a, BigInteger b) { // Iterativo
  if(a < 0) a = BigInteger(0) - a;
  if(b < 0) b = BigInteger(0) - b;
  while (b != 0) {
    BigInteger r = a % b;
    a = b;
    b = r;
  }
  return a;
}

using namespace std;
int main() {
  BigInteger num1, num2;
  cout << "Introduce el primer número: ";
  cin >> num1;
  cout << "Introduce el segundo número: ";
  cin >> num2;

  cout << "El MCD de " << num1 << " y " << num2 << " es: " << mcd(num1, num2) << endl;
  
  return 0;
}