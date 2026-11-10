#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <iostream>
#include <string>
#include <stdexcept>

// Declaraciones adelantadas de clases
template <unsigned char Base> class BigRational;
template <unsigned char Base> class BigUnsigned;
template <unsigned char Base> class BigInteger;

/**
 * @brief Clase base abstracta para representar números en una base arbitraria.
 * @tparam Base La base numérica en la que opera el número.
 */
template <unsigned char Base> class BigNumber {
 public:
   /**
    * @brief Destructor virtual por defecto.
    */
   virtual ~BigNumber() = default;
   
   // Operaciones matemáticas
   /**
    * @brief Realiza la suma con otro número de la misma base.
    * @param other El número a sumar.
    * @return Un puntero a un nuevo objeto BigNumber con el resultado.
    */
   virtual BigNumber<Base>* add(const BigNumber<Base>& other) const = 0;

   /**
    * @brief Realiza la resta con otro número de la misma base.
    * @param other El número a restar.
    * @return Un puntero a un nuevo objeto BigNumber con el resultado.
    */
   virtual BigNumber<Base>* subtract(const BigNumber<Base>& other) const = 0;

   /**
    * @brief Realiza la multiplicación con otro número de la misma base.
    * @param other El número a multiplicar.
    * @return Un puntero a un nuevo objeto BigNumber con el resultado.
    */
   virtual BigNumber<Base>* multiply(const BigNumber<Base>& other) const = 0;

   /**
    * @brief Realiza la división con otro número de la misma base.
    * @param other El número divisor.
    * @return Un puntero a un nuevo objeto BigNumber con el resultado.
    */
   virtual BigNumber<Base>* divide(const BigNumber<Base>& other) const = 0;
   
   // Conversiones de tipo
   virtual operator BigUnsigned<Base>() const = 0;
   virtual operator BigInteger<Base>() const = 0;
   virtual operator BigRational<Base>() const = 0;
   
   // Entrada/Salida
   virtual std::ostream& write(std::ostream&) const = 0;
   virtual std::istream& read(std::istream&) = 0;
   
   template <unsigned char B>
   friend std::ostream& operator<<(std::ostream&, const BigNumber<Base>&);
   
   template <unsigned char B>
   friend std::istream& operator>>(std::istream&, BigNumber<Base>&);

   /**
    * @brief Crea una instancia de BigNumber a partir de una cadena.
    * @param input La representación en cadena del número.
    * @return Un puntero a un objeto BigNumber correspondiente al tipo detectado.
    */
   static BigNumber<Base>* create(const char* input);
};

// Operadores de entrada y salida
/**
 * @brief Operador de salida para BigNumber.
 */
template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& num) {
   return num.write(os);
}

/**
 * @brief Operador de entrada para BigNumber.
 */
template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigNumber<Base>& num) {
   return num.read(is);
}

/**
 * @brief Implementación del método create para determinar el tipo de número.
 */
template <unsigned char Base>
BigNumber<Base>* BigNumber<Base>::create(const char* input) {
   if (!input || input[0] == '\0')
     throw std::invalid_argument("Input inválido");
   
   const std::string input_str(input);
   const size_t last_pos{input_str.size() - 1};
   const std::string value{input_str.substr(0, last_pos)};
   const char suffix{input_str[last_pos]};
   
   if (suffix == 'u') {
     return new BigUnsigned<Base>(value);
   } else if (suffix == 'i') {
     return new BigInteger<Base>(value);
   } else if (suffix == 'r') {
     const size_t pos_slash{value.find('/')};
     if (pos_slash != std::string::npos) {
       const std::string numerator{value.substr(0, pos_slash)};
       const std::string denominator{value.substr(pos_slash + 1)};
       return new BigRational<Base>(BigInteger<Base>(numerator), BigUnsigned<Base>(denominator));
     }
   }
   return nullptr;
}

// Excepciones
/**
 * @brief Clase base para excepciones en BigNumber.
 */
class BigNumberException : public std::exception {
 public:
   virtual const char* what() const noexcept override = 0;
};

/**
 * @brief Excepción lanzada cuando se encuentra un dígito inválido.
 */
class BigNumberBadDigit : public BigNumberException {
 public:
   const char* what() const noexcept override {
     return "Not a valid digit";
   }
};

/**
 * @brief Excepción lanzada cuando ocurre una división por cero.
 */
class BigNumberDivisionByZero : public BigNumberException {
 public:
   const char* what() const noexcept override {
     return "Not a valid base";
   }
};

#endif // BIG_NUMBER_H
