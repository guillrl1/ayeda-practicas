#include "bigUnsigned.h"
#include "bigInteger.h"

int main() {
  const unsigned char num[] = "20";
  const unsigned char num2[] = "40";
  BigUnsigned a(num);
  BigUnsigned b(num2);
  BigUnsigned c(23);
  cout << "c vale: " << c << endl;
  cout << a << endl;
  cout << b << endl;
  cout << "Suma: " << a + b << endl;
  cout << "Resta: " << b - a << endl;
  cout << "Multiplicación: " << a * b << endl;
  cout << "División: " << b / a << endl;
  cout << "Incremento a: " << ++a << endl;
  cout << "Decremento b: " << --b << endl;

  cout << "Empieza los integers..." << endl;
  BigInteger x(-20);
  BigInteger y(40);
  BigInteger z(-50);
  
  cout << "x vale: " << x << endl;
  cout << "y vale: " << y << endl;
  cout << "Suma de: " << x << " + " << y << " = " << x + y << endl;
  cout << "suma de: " << x << " + " << z << " = " << x + z << endl;
  cout << "suma de: " << y << " + " << z << " = " << y + z << endl;
  cout << "suma de: " << y << " + " << x << " = " << y + x << endl;

  cout << "Resta de: " << x << " - " << y << " = " << x - y << endl;
  cout << "Resta de: " << x << " - " << z << " = " << x - z << endl;
  cout << "Resta de: " << y << " - " << z << " = " << y - z << endl;
  cout << "Resta de: " << y << " - " << x << " = " << y - x << endl;

  cout << "Multiplicación de: " << x << " * " << y << " = " << x * y << endl;
  cout << "Multiplicación de: " << x << " * " << z << " = " << x * z << endl;
  cout << "Multiplicación de: " << y << " * " << z << " = " << y * z << endl;
  cout << "Multiplicación de: " << y << " * " << x << " = " << y * x << endl;

  cout << "División de: " << x << " / " << y << " = " << x / y << endl;
  cout << "División de: " << x << " / " << z << " = " << x / z << endl;
  cout << "División de: " << y << " / " << z << " = " << y / z << endl;
  cout << "División de: " << y << " / " << x << " = " << y / x << endl;

  cout << "Incremento de x: " << ++x << endl;
  cout << "Incremento de y: " << ++y << endl;
  cout << "Incremento de z: " << ++z << endl;

  cout << "Decremento de x: " << --x << endl;
  cout << "Decremento de y: " << --y << endl;
  cout << "Decremento de z: " << --z << endl;

  cout << "Resto de: " << x << " % " << y << " = " << x % y << endl;
  cout << "Resto de: " << x << " % " << z << " = " << x % z << endl;
  cout << "Resto de: " << y << " % " << z << " = " << y % z << endl;
  cout << "Resto de: " << y << " % " << x << " = " << y % x << endl;
  
}