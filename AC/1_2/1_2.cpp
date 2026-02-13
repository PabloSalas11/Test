#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct Pregunta {
  string enunciado;
  vector<string> opciones;
  int correcta;
  string cita;
};

void mostrarTest() {
  vector<Pregunta> banco = {
      // --- BLOQUE 1: CONCEPTOS GENERALES Y REGISTROS (10 preguntas) ---
      {"¿Cual es el tamaño de los registros vectoriales MM0-7 introducidos en "
       "1997?",
       {"32 bits", "64 bits", "128 bits", "256 bits"},
       1,
       "[cite: 646, 647, 649]"},
      {"¿Cuantos registros vectoriales posee la extension SSE2 y de que tamaño "
       "son?",
       {"8 registros de 128 bits", "16 registros de 128 bits",
        "8 registros de 64 bits", "16 registros de 256 bits"},
       0,
       "[cite: 679, 685]"},
      {"¿Cual es la capacidad total de un registro YMM en la arquitectura AVX?",
       {"128 bits", "256 bits", "512 bits", "64 bits"},
       1,
       "[cite: 694, 698]"},
      {"¿Cuantos registros YMM estan disponibles en el conjunto de "
       "instrucciones AVX?",
       {"8", "12", "16", "32"},
       2,
       "[cite: 698, 706]"},
      {"El concepto de 'Paralelismo Subword' se basa fundamentalmente en:",
       {"Dividir una palabra larga en partes pequeñas procesadas "
        "simultaneamente",
        "Ejecutar varios hilos en un solo ciclo",
        "Aumentar la frecuencia de reloj de la ALU",
        "Duplicar la Unidad de Control"},
       0,
       "[cite: 584, 589]"},
      {"Si una ALU vectorial de 256 bits trabaja con datos de 64 bits, "
       "¿cuantas operaciones realiza a la vez?",
       {"2", "4", "8", "16"},
       1,
       "[cite: 596, 604]"},
      {"¿Cuantas operaciones de 32 bits puede realizar simultaneamente un "
       "procesador con AVX?",
       {"4", "8", "16", "32"},
       1,
       "[cite: 633, 642]"},
      {"¿Que instruccion de MMX se utilizaria para sumar datos de tipo 'double "
       "word' (32 bits)?",
       {"PADDB", "PADDW", "PADDD", "PADDQ"},
       2,
       "[cite: 654, 662]"},
      {"¿Que significa el prefijo 'P' en instrucciones como PADDB?",
       {"Parallel", "Packed (Empaquetado)", "Processor", "Pipeline"},
       1,
       "[cite: 656, 662]"},
      {"¿En que año se introdujo la extension SSE2?",
       {"1997", "1999", "2001", "2011"},
       2,
       "[cite: 680, 686]"},

      // --- BLOQUE 2: ARQUITECTURA X86-64 E IDENTIFICACIÓN (10 preguntas) ---
      {"¿Cual es el nombre comercial de la arquitectura de 64 bits de Intel "
       "(EM64T)?",
       {"AMD64", "IA32e", "Intel64", "Todas las anteriores"},
       3,
       "[cite: 433, 437, 439]"},
      {"¿Que instruccion se utiliza para detectar en tiempo de ejecucion los "
       "conjuntos de instrucciones avanzados?",
       {"MOVAPS", "CPUID", "VADDPD", "RSM"},
       1,
       "[cite: 728, 729]"},
      {"Segun el CPU-Z del i3-6100U, ¿que nivel de cache es compartido "
       "(12-way)?",
       {"L1 Data", "L1 Inst", "Level 2", "Level 3"},
       3,
       "[cite: 360, 413]"},
      {"¿Cual es el TDP maximo del procesador Skylake-U mostrado en el PDF?",
       {"10.0 W", "15.0 W", "35.0 W", "45.0 W"},
       1,
       "[cite: 334, 385]"},
      {"¿Que extension esta especificamente diseñada para la criptografia "
       "segun los descriptores de CPU-Z?",
       {"AVX", "SSE4.2", "AES", "FMA3"},
       2,
       "[cite: 355, 538]"},
      {"¿Cual es el proposito de la extension TSX?",
       {"Cifrado de datos", "Optimizacion de software multihilo",
        "Virtualizacion", "Calculo vectorial de 512 bits"},
       1,
       "[cite: 355, 552]"},
      {"¿Que tecnologia permite la virtualizacion en procesadores Intel?",
       {"EM64T", "VT-x", "SSSE3", "FMA3"},
       1,
       "[cite: 354, 566]"},
      {"En AVX, ¿que indica el mnemotecnico VADDPD?",
       {"Vector Add Packed Double (64-bit float)",
        "Vector Add Packed Single (32-bit float)", "Vector Add Parallel Data",
        "Virtual Add Packed Decimal"},
       0,
       "[cite: 696, 704]"},
      {"¿Cuantos operandos utiliza la instruccion VADDPD en AVX?",
       {"1", "2", "3", "4"},
       2,
       "[cite: 710]"},
      {"Diferencia de operandos entre SSE2 y AVX:",
       {"SSE2 usa 3 y AVX usa 2", "SSE2 usa 2 y AVX usa 3", "Ambos usan 3",
        "Ambos usan 2"},
       1,
       "[cite: 689, 710]"},

      // --- BLOQUE 3: LIMITACIONES DE VECTORIZACIÓN (10 preguntas) ---
      {"¿Cual de estos elementos impide la vectorizacion automatica de un "
       "bucle?",
       {"Operaciones de suma", "Sentencias Switch", "Uso de punteros",
        "Multiplicaciones"},
       1,
       "[cite: 737]"},
      {"¿Que tipo de llamadas a funciones son permitidas dentro de un bucle "
       "vectorizable?",
       {"Cualquiera de usuario", "Solo matematicas intrinsecas",
        "Llamadas de sistema", "Ninguna"},
       1,
       "[cite: 740]"},
      {"¿Que condicion sobre las iteraciones es necesaria para la "
       "vectorizacion?",
       {"Deben ser infinitas",
        "El numero de iteraciones debe estar predefinido",
        "Deben ser menores de 10", "Deben depender entre si"},
       1,
       "[cite: 744]"},
      {"En bucles anidados, ¿cual suele vectorizar el compilador?",
       {"El mas externo", "El mas interno", "Todos simultaneamente", "Ninguno"},
       1,
       "[cite: 747, 748]"},
      {"¿Que problema de datos bloquea la vectorizacion?",
       {"Datos de 32 bits", "Dependencias entre iteraciones",
        "Datos en memoria cache", "Uso de constantes"},
       1,
       "[cite: 741]"},
      {"¿Cual es una solucion manual si el compilador no vectoriza bien?",
       {"Cambiar el SO", "Usar bloques __asm { }",
        "Bajar la frecuencia de reloj", "Aumentar la RAM"},
       1,
       "[cite: 751, 753]"},
      {"¿Que archivo de cabecera en C permite trabajar con 'intrinsecos'?",
       {"stdio.h", "intrin.h", "math.h", "vector.h"},
       1,
       "[cite: 758]"},
      {"¿Cual es la ventaja de usar intrinsecos frente a ensamblador puro?",
       {"Mayor velocidad", "Portabilidad y legibilidad en alto nivel",
        "No requieren CPU avanzada", "Eliminan la latencia"},
       1,
       "[cite: 756, 757]"},
      {"¿Que ocurre si un bucle contiene un 'salto' (GOTO) fuera del cuerpo?",
       {"Se vectoriza mas rapido", "Impide la vectorizacion", "No influye",
        "El compilador lo borra"},
       1,
       "[cite: 737]"},
      {"¿Para que sirve la guia de intrinsecos de Intel mencionada?",
       {"Para programar en Java",
        "Consultar la lista de funciones x86 disponibles", "Configurar la BIOS",
        "Medir la temperatura de la CPU"},
       1,
       "[cite: 759, 760]"},

      // --- BLOQUE 4: DETALLES TÉCNICOS AVANZADOS (10 preguntas) ---
      {"La instruccion VADDPS trabaja con datos de tipo:",
       {"64-bit float", "32-bit float", "16-bit integer", "8-bit integer"},
       1,
       "[cite: 697, 705]"},
      {"En MMX, PADDB opera sobre:",
       {"8 bytes de 8 bits cada uno", "4 words de 16 bits", "2 double words",
        "1 quad word"},
       0,
       "[cite: 652, 656]"},
      {"¿Cual es el tamaño maximo de registro vectorial visto en este temario?",
       {"64 bits", "128 bits", "256 bits", "512 bits"},
       2,
       "[cite: 694, 698]"},
      {"Un registro de 128 bits realizando PADDB hace las operaciones de:",
       {"2 en 2", "4 en 4", "8 en 8", "16 en 16"},
       3,
       "[cite: 674, 684]"},
      {"Un registro de 128 bits realizando PADDW hace las operaciones de:",
       {"2 en 2", "4 en 4", "8 en 8", "16 en 16"},
       2,
       "[cite: 674, 684]"},
      {"Un registro de 128 bits realizando PADDD hace las operaciones de:",
       {"2 en 2", "4 en 4", "8 en 8", "16 en 16"},
       1,
       "[cite: 674, 684]"},
      {"¿Que generacion de procesadores Intel introdujo AVX segun el nombre en "
       "clave?",
       {"Sandy Bridge (no citado)", "Skylake-U (ejemplo usado)", "Haswell",
        "Pentium Pro"},
       1,
       "[cite: 333, 456]"},
      {"La instruccion PADDQ de SSE2 suma:",
       {"Bytes", "Words", "Double Words", "Quad Words (64 bits)"},
       3,
       "[cite: 675, 684]"},
      {"¿Que sucede con los componentes vectoriales segun el temario?",
       {"Son fijos", "Son adaptables segun el tamaño de dato",
        "Se borran tras cada uso", "Solo funcionan en Linux"},
       1,
       "[cite: 590, 593]"},
      {"Homer Simpson prefiere programar en:",
       {"Bajo nivel", "Ensamblador", "Alto nivel", "Binario puro"},
       2,
       "[cite: 720, 721]"}};

  random_device rd;
  mt19937 g(rd());
  shuffle(banco.begin(), banco.end(), g);

  int puntuacion = 0;
  const int numPreguntas =
      15; // Selecciona 15 al azar de las 40 para evitar repetitividad

  cout << "====================================================" << endl;
  cout << " EXAMEN AVANZADO: EXTENSIONES SIMD Y PARALELISMO   " << endl;
  cout << "====================================================\n" << endl;

  for (int i = 0; i < numPreguntas; i++) {
    cout << "PREGUNTA " << i + 1 << ": " << banco[i].enunciado << endl;
    for (int j = 0; j < 4; j++) {
      cout << "  " << (char)('A' + j) << ") " << banco[i].opciones[j] << endl;
    }

    char respuesta;
    cout << ">> Respuesta: ";
    cin >> respuesta;
    respuesta = toupper(respuesta);

    if ((respuesta - 'A') == banco[i].correcta) {
      cout << "CORRECTO. Ref: " << banco[i].cita << "\n" << endl;
      puntuacion++;
    } else {
      cout << "ERROR. Era la " << (char)('A' + banco[i].correcta)
           << ". Ref: " << banco[i].cita << "\n"
           << endl;
    }
  }

  float nota = (float)puntuacion / numPreguntas * 10;
  cout << "FINAL DEL EXAMEN. Puntuacion: " << puntuacion << "/" << numPreguntas
       << " (Nota: " << nota << ")" << endl;
  if (nota >= 8.5)
    cout << "Nivel: EXPERTO EN OPTIMIZACION SIMD." << endl;
  else if (nota >= 5)
    cout
        << "Nivel: APROBADO. Sigue practicando las limitaciones del compilador."
        << endl;
  else
    cout << "Nivel: SUSPENSO. Repasa la jerarquia de registros vectoriales."
         << endl;
}

int main() {
  mostrarTest();
  return 0;
}