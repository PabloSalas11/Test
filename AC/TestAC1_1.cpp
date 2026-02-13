#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct Pregunta {
  string enunciado;
  vector<string> opciones;
  int correcta; // Índice de la opción correcta (0-3)
  string cita;  // Referencia al PDF
};

void mostrarTest() {
  // Batería de preguntas basadas en el PDF Tema1-Parte1
  vector<Pregunta> banco = {
      {"¿Cuál es el criterio fundamental de la Taxonomía de Flynn (1972)?",
       {"Frecuencia de reloj y número de núcleos.",
        "Nº de secuencias de instrucciones y de datos simultáneas.",
        "Capacidad de la memoria caché L1.",
        "Nivel de segmentación del pipeline."},
       1,
       "[cite: 13-18]"},

      {"En una arquitectura SIMD, ¿qué tipo de paralelismo se explota "
       "principalmente?",
       {"Paralelismo a nivel de proceso (PLP).",
        "Paralelismo a nivel de hilo (TLP).",
        "Paralelismo a nivel de datos (DLP).", "Paralelismo de control (CLP)."},
       2,
       "[cite: 39, 40]"},

      {"¿Qué sucede en un pipeline de 5 etapas una vez que el cauce está "
       "completamente lleno?",
       {"Se termina una instrucción en cada ciclo de reloj.",
        "La latencia de cada instrucción se reduce a cero.",
        "Se ejecutan 5 instrucciones simultáneamente por etapa.",
        "El procesador pasa a modo superescalar automáticamente."},
       0,
       "[cite: 245, 246]"},

      {"¿Cuál es la diferencia principal entre MIMD de memoria compartida y "
       "memoria distribuida?",
       {"El número de unidades de control.",
        "La forma en que los procesadores acceden a la memoria y la red de "
        "interconexión.",
        "El uso de instrucciones vectoriales.",
        "El grado del procesador superescalar."},
       1,
       "[cite: 126, 127]"},

      {"El concepto de 'Grado' en un procesador superescalar se refiere a:",
       {"La cantidad de etapas del pipeline.",
        "El número de hilos lógicos por núcleo.",
        "El número máximo de instrucciones iniciadas simultáneamente por "
        "etapa.",
        "La velocidad de transferencia del bus interno."},
       2,
       "[cite: 268-272]"},

      {"¿Qué técnica convierte un procesador físico en varios procesadores "
       "lógicos?",
       {"Pipelining.", "Vectorización.", "Multithreading.", "Segmentación EX."},
       2,
       "[cite: 273-276]"},

      {"En el modelo SIMD, ¿qué componente es responsable de enviar la misma "
       "instrucción a múltiples UP?",
       {"La Memoria de Datos.", "La Unidad de Control (UC).",
        "El Banco de Registros.", "La red de interconexión."},
       1,
       "[cite: 41-47]"},

      {"¿Cuál de estos es un tipo de multithreading mencionado en la taxonomía "
       "avanzada?",
       {"Multithreading de instrucción única.", "Multithreading de grano fino.",
        "Multithreading de segmentación (IF/ID).",
        "Multithreading de bus distribuido."},
       1,
       "[cite: 293-294]"},

      {"¿Qué etapa del pipeline MIPS se encarga de la lectura de operandos y "
       "decodificación?",
       {"IF (Instruction Fetch).", "EX (Execution).", "MEM (Memory).",
        "ID (Instruction Decode)."},
       3,
       "[cite: 150, 157]"},

      {"¿Qué permite la vectorización de código realizada por los "
       "compiladores?",
       {"Ejecutar iteraciones de un bucle en paralelo mediante instrucciones "
        "vectoriales.",
        "Reducir el número de registros en el banco de registros.",
        "Eliminar la etapa de WriteBack del pipeline.",
        "Transformar una arquitectura MIMD en SISD."},
       0,
       "[cite: 73-78]"},

      {"Un procesador SMT (Simultaneous Multithreading) se clasifica dentro "
       "del paralelismo a nivel de:",
       {"Datos (DLP).", "Instrucción (ILP).", "Hilo (TLP).",
        "Segmentación simple."},
       2,
       "[cite: 278, 297]"},

      {"¿Qué elemento es indispensable replicar para conseguir una "
       "arquitectura superescalar?",
       {"El bus de direcciones.",
        "Elementos del procesador (unidades funcionales).",
        "La memoria principal.", "El contador de programa (PC)."},
       1,
       "[cite: 265-267]"}};

  // Aleatorizar el banco de preguntas
  srand(time(0));
  random_shuffle(banco.begin(), banco.end());

  int puntuacion = 0;
  cout << "--- TEST DE ARQUITECTURA DE COMPUTADORES (UCA) ---\n" << endl;

  for (int i = 0; i < 10; i++) {
    cout << i + 1 << ". " << banco[i].enunciado << endl;
    for (int j = 0; j < 4; j++) {
      cout << "   " << (char)('A' + j) << ") " << banco[i].opciones[j] << endl;
    }

    char respuesta;
    cout << "Tu respuesta: ";
    cin >> respuesta;
    respuesta = toupper(respuesta);

    if ((respuesta - 'A') == banco[i].correcta) {
      cout << "¡CORRECTO! " << banco[i].cita << "\n" << endl;
      puntuacion++;
    } else {
      cout << "INCORRECTO. La respuesta era la "
           << (char)('A' + banco[i].correcta) << ". " << banco[i].cita << "\n"
           << endl;
    }
  }

  cout << "--- RESULTADO FINAL ---" << endl;
  cout << "Puntuacion: " << puntuacion << "/10" << endl;
  if (puntuacion >= 5)
    cout << "Estado: APROBADO" << endl;
  else
    cout << "Estado: SUSPENSO - Repasa el PDF." << endl;
}

int main() {
  mostrarTest();
  return 0;
}