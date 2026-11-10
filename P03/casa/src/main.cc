 #include <fstream>
 #include <iostream>
 #include <sstream>
 #include <string>
 #include <vector>
 
 #include "bigRational.h"
 
 constexpr int kExpectedArguments{3};
 
 /**
  * @brief Muestra el mensaje de uso en caso de que los argumentos sean incorrectos.
  * @param program_name Nombre del programa ejecutado.
  */
 inline void MostrarUso(const char* program_name) {
   std::cerr << "Uso: " << program_name << " <archivo_entrada> <archivo_salida>\n";
 }
 
 /**
  * @brief Realiza cálculos en Notación Polaca Inversa (RPN) con una base determinada.
  * @tparam Base Base numérica usada en los cálculos.
  * @param memoria Vector que almacena las variables y sus valores.
  * @param flujo_entrada Flujo de entrada con la expresión en formato RPN.
  * @param resultado_nombre Nombre de la variable que almacenará el resultado.
  * @param primer_operando Primer operando de la operación.
  */
 template <unsigned char Base>
 void EvaluarRPN(std::vector<std::pair<std::string, BigNumber<Base>*>>& memoria,
                 std::istringstream& flujo_entrada, std::string& resultado_nombre,
                 std::string primer_operando) {
   std::vector<std::string> pila{primer_operando};
   memoria.push_back({resultado_nombre, nullptr});
   std::string simbolo{};
 
   while (flujo_entrada >> simbolo) {
     if (simbolo == "+" || simbolo == "-" || simbolo == "*" || simbolo == "/") {
       if (pila.size() < 2)
         throw std::runtime_error("Error: Operandos insuficientes");
 
       std::string operando2_str{pila.back()};
       pila.pop_back();
       std::string operando1_str{pila.back()};
       pila.pop_back();
       BigNumber<Base>* operando1{nullptr};
       BigNumber<Base>* operando2{nullptr};
 
       for (const auto& [clave, valor] : memoria) {
         if (clave == operando1_str)
           operando1 = valor;
         if (clave == operando2_str)
           operando2 = valor;
       }
 
       if (!operando1 || !operando2)
         throw std::runtime_error("Error: Operando inválido");
 
       std::cout << "Operando 1: " << *operando1 << " Operando 2: " << *operando2 << std::endl;
       BigNumber<Base>* resultado{nullptr};
 
       switch (simbolo[0]) {
         case '+':
           resultado = operando1->add(*operando2);
           break;
         case '-':
           resultado = operando1->subtract(*operando2);
           break;
         case '*':
           resultado = operando1->multiply(*operando2);
           break;
         case '/':
           resultado = operando1->divide(*operando2);
           break;
         default:
           throw std::runtime_error("Error: Operador inválido");
       }
 
       pila.push_back(resultado_nombre);
 
       // Actualiza el resultado en la memoria
       for (auto& [clave, valor] : memoria) {
         if (clave == resultado_nombre) {
           delete valor;
           valor = resultado;
         }
       }
       std::cout << "Resultado: " << *resultado << std::endl;
     } else {
       pila.push_back(simbolo);
     }
   }
 }
 
 /**
  * @brief Procesa un archivo de entrada y realiza los cálculos definidos en él.
  * @tparam Base Base numérica utilizada en las operaciones.
  * @param archivo_entrada Archivo de entrada con las instrucciones.
  * @param archivo_salida Archivo de salida donde se guardan los resultados.
  * @return Código de salida del programa (EXIT_SUCCESS o EXIT_FAILURE).
  */
 template <unsigned char Base>
 int ProcesarArchivo(std::ifstream& archivo_entrada, std::ofstream& archivo_salida) {
   std::string linea{};
   std::vector<std::pair<std::string, BigNumber<Base>*>> memoria{};
 
   while (std::getline(archivo_entrada, linea)) {
     if (linea.empty())
       continue;
     std::istringstream flujo{linea};
     std::string variable{}, asignacion{}, valor{};
     flujo >> variable >> asignacion >> valor;
     if (asignacion == "=") {
       BigNumber<Base>* numero = BigNumber<Base>::create(valor.c_str());
       if (!numero) {
         throw std::runtime_error("Error: Número inválido");
       }
       memoria.push_back({variable, numero});
     } else if (asignacion == "?") {
       EvaluarRPN<Base>(memoria, flujo, variable, valor);
     } else {
       throw std::runtime_error("Error: Asignación inválida");
     }
   }
 
   for (const auto& [clave, valor] : memoria) {
     archivo_salida << clave << " = " << *valor;
 
     if (typeid(*valor) == typeid(BigUnsigned<Base>)) {
       archivo_salida << "u\n";
     } else if (typeid(*valor) == typeid(BigInteger<Base>)) {
       archivo_salida << "i\n";
     } else if (typeid(*valor) == typeid(BigRational<Base>)) {
       archivo_salida << "r\n";
     } else {
       std::cerr << "Error: Tipo de número inválido\n";
       return EXIT_FAILURE;
     }
   }
 
   // Liberar memoria
   for (const auto& [clave, valor] : memoria) {
     delete valor;
   }
 
   return EXIT_SUCCESS;
 }
 
 /**
  * @brief Punto de entrada del programa.
  * @param argc Número de argumentos pasados por línea de comandos.
  * @param argv Array de argumentos (nombre del programa, archivo de entrada, archivo de salida).
  * @return Código de salida (EXIT_SUCCESS o EXIT_FAILURE).
  */
 int main(int argc, char* argv[]) {
   if (argc != kExpectedArguments) {
     MostrarUso(argv[0]);
     return EXIT_FAILURE;
   }
 
   std::ifstream archivo_entrada{argv[1]};
   if (!archivo_entrada.is_open()) {
     std::cerr << "Error: No se pudo abrir el archivo " << argv[1] << '\n';
     return EXIT_FAILURE;
   }
 
   std::string base_str{};
   std::getline(archivo_entrada, base_str);
   if (base_str.empty()) {
     std::cerr << "Error: Base no especificada\n";
     return EXIT_FAILURE;
   } else if (base_str.starts_with("Base =")) {
     base_str = base_str.substr(6);
   } else {
     std::cerr << "Error: Base inválida\n";
     return EXIT_FAILURE;
   }
 
   std::ofstream archivo_salida{argv[2]};
   if (!archivo_salida.is_open()) {
     std::cerr << "Error: No se pudo abrir el archivo " << argv[2] << '\n';
     return EXIT_FAILURE;
   }
 
   const unsigned char base{static_cast<unsigned char>(std::stoi(base_str))};
   archivo_salida << "Base: " << static_cast<int>(base) << '\n';
 
   switch (base) {
     case 2:
       return ProcesarArchivo<2>(archivo_entrada, archivo_salida);
     case 8:
       return ProcesarArchivo<8>(archivo_entrada, archivo_salida);
     case 10:
       return ProcesarArchivo<10>(archivo_entrada, archivo_salida);
     case 16:
       return ProcesarArchivo<16>(archivo_entrada, archivo_salida);
     default:
       std::cerr << "Error: Base no soportada: " << base << "\n";
       return EXIT_FAILURE;
   }
 }