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
      // --- BLOQUE 1: TAXONOMÍA DE FLYNN (5 preguntas) ---
      {"¿Que arquitectura procesa una unica secuencia de datos con multiples "
       "instrucciones?",
       {"SISD", "SIMD", "MISD", "MIMD"},
       2,
       "[cite: 22-23]"},
      {"El principal beneficio de una arquitectura SIMD es:",
       {"Paralelismo a nivel de hilo (TLP).",
        "Paralelismo a nivel de datos (DLP).", "Independencia de la UC.",
        "Reduccion de UP."},
       1,
       "[cite: 39-40]"},
      {"En una arquitectura MIMD de memoria distribuida:",
       {"Acceso a memoria global unica.",
        "Cada procesador tiene memoria local y red de interconexion.",
        "No hay caches.", "UC compartida."},
       1,
       "[cite: 125-127]"},
      {"¿Cual es un ejemplo de arquitectura MIMD multinucleo?",
       {"Intel Core i7.", "Procesadores vectoriales.", "SISD puras.",
        "Extensiones SIMD."},
       0,
       "[cite: 128-130]"},
      {"Criterio de clasificacion de Flynn:",
       {"Frecuencia y transistores.",
        "Nº de secuencias de instrucciones y datos simultaneas.",
        "Consumo y area.", "Capacidad de disco."},
       1,
       "[cite: 13-18]"},

      // --- BLOQUE 2: PIPELINE / CAMINO DE DATOS (10 preguntas) ---
      {"Objetivo de segmentar la ejecucion:",
       {"Reducir latencia de una instruccion.",
        "Conseguir paralelismo a nivel de instruccion (ILP).",
        "Eliminar la UC.", "Aumentar registros."},
       1,
       "[cite: 139-140, 220]"},
      {"¿Que ocurre en la etapa ID del pipeline?",
       {"Busqueda en memoria.", "Escritura en registros.",
        "Decodificacion en la U.C.", "Calculo en la ALU."},
       2,
       "[cite: 157-158]"},
      {"Componente hardware de la etapa EX:",
       {"Memoria de datos.", "Banco de registros.",
        "Unidad Aritmetico-Logica (ALU).", "PC."},
       2,
       "[cite: 159-160]"},
      {"Una vez lleno el pipeline de 5 etapas:",
       {"Se detiene.", "Tarda 1 ciclo por instruccion.",
        "En cada ciclo termina una instruccion.", "Falla."},
       2,
       "[cite: 245-246]"},
      {"Funcion de la etapa WB (WriteBack):",
       {"Acceso a RAM.", "Escribir en el banco de registros.", "Actualizar PC.",
        "Interrupciones."},
       1,
       "[cite: 163-164]"},
      {"¿Donde se encuentra la etapa IF?",
       {"En la ALU.", "En la memoria de instrucciones.", "En la UC.",
        "En el banco de registros."},
       1,
       "[cite: 155-156]"},
      {"En el esquema tecnico (p. 23), ¿que registro almacena la instruccion "
       "leida?",
       {"MAR", "MBR", "RI (Registro de Instruccion)", "PC"},
       2,
       "[cite: 184]"},
      {"¿Cual es la funcion del registro PC en el camino de datos?",
       {"Almacenar operandos.",
        "Contener la direccion de la proxima instruccion.", "Realizar sumas.",
        "Decodificar."},
       1,
       "[cite: 182]"},
      {"La etapa MEM se encarga de:",
       {"Cargar operandos de registros.", "Escribir en el banco de registros.",
        "Lectura/Escritura en memoria de datos.", "Calculos logicos."},
       2,
       "[cite: 161-162]"},
      {"Ventaja principal del pipeline frente al no segmentado:",
       {"Menor latencia por instruccion.",
        "Mayor throughput (instrucciones por segundo).",
        "Menor consumo de energia.", "Hardware mas simple."},
       1,
       ""},

      // --- BLOQUE 3: SUPERESCALAR Y GRADO (7 preguntas) ---
      {"Diferencia entre superescalar y segmentado simple:",
       {"No tiene pipeline.", "Inicia varias instrucciones por ciclo.",
        "Solo una UP.", "Un solo hilo."},
       1,
       "[cite: 263-264]"},
      {"Para un procesador superescalar es necesario:",
       {"Reducir etapas.", "Replicar elementos funcionales (UPs).",
        "Memoria compartida.", "Sin cache."},
       1,
       "[cite: 266-267]"},
      {"Definicion de 'Grado' superescalar:",
       {"Etapas del cauce.",
        "Instrucciones iniciadas simultaneamente por etapa.", "Memoria RAM.",
        "Nº de hilos."},
       1,
       "[cite: 268-272]"},
      {"Si un procesador inicia 4 instrucciones por ciclo, su grado es:",
       {"1", "2", "4", "5"},
       2,
       "[cite: 268-272]"},
      {"¿Que permite alcanzar el ILP (Instruction Level Parallelism)?",
       {"Un camino de datos segmentado (pipeline).", "Mas memoria RAM.",
        "Un disco duro SSD.", "Software antivirus."},
       0,
       "[cite: 219-222]"},
      {"En el diagrama superescalar (p. 30), varias instrucciones estan en la "
       "misma etapa:",
       {"En ciclos distintos.", "En el mismo ciclo de reloj.",
        "Solo si son iguales.", "Solo en la etapa IF."},
       1,
       "[cite: 258-261]"},
      {"¿Que limite fisico restringe el grado superescalar?",
       {"La capacidad del disco.",
        "El numero de unidades funcionales replicadas.",
        "El tamaño de la pantalla.", "El bus de datos."},
       1,
       ""},

      // --- BLOQUE 4: MULTITHREADING Y AVANZADOS (8 preguntas) ---
      {"El Multithreading convierte un procesador fisico en:",
       {"Varios procesadores logicos.", "Arquitectura SISD.",
        "Supercomputador.", "Bus de mayor ancho."},
       0,
       "[cite: 273-276]"},
      {"Tipo de paralelismo del Multithreading:",
       {"ILP", "DLP", "TLP (Thread Level Parallelism)", "Segmentacion."},
       2,
       "[cite: 278]"},
      {"Tipo de multithreading mencionado en el PDF:",
       {"Vectorial.", "Simultaneous Multithreading (SMT).", "Estatico.",
        "Global."},
       1,
       "[cite: 293-297]"},
      {"En el SMT (Simultaneous Multithreading):",
       {"Se alterna un hilo por ciclo.",
        "Se ejecutan instrucciones de varios hilos en el mismo ciclo.",
        "Se para el procesador al cambiar de hilo.", "No hay segmentacion."},
       1,
       "[cite: 292, 297]"},
      {"Multithreading de grano fino (Fine-Grained):",
       {"Cambia de hilo en cada ciclo.",
        "Cambia solo en fallos de cache largos.", "No usa hilos logicos.",
        "Es igual al superescalar."},
       0,
       "[cite: 285, 294]"},
      {"¿Que componente realiza la vectorizacion del codigo?",
       {"Hardware.", "Sistema Operativo.", "Compilador.",
        "Banco de registros."},
       2,
       "[cite: 73-74]"},
      {"El cluster CAI de la UCA es:",
       {"SISD.", "Monociclo.", "Supercomputador (MIMD).", "SIMD simple."},
       2,
       "[cite: 132-135]"},
      {"En el diagrama de hilos (p. 36), los 'Idle slots' son:",
       {"Ciclos de maxima potencia.",
        "Ciclos donde el procesador no ejecuta nada por dependencias o "
        "esperas.",
        "Memoria libre.", "Instrucciones de salto."},
       1,
       "[cite: 291]"}};

  random_device rd;
  mt19937 g(rd());
  shuffle(banco.begin(), banco.end(), g);

  int puntuacion = 0;
  const int numPreguntas = 10; // Selecciona 10 al azar cada vez

  cout << "====================================================" << endl;
  cout << "   EXAMEN FINAL ARQUITECTURA (30 PREGUNTAS TOTAL)  " << endl;
  cout << "====================================================\n" << endl;

  for (int i = 0; i < numPreguntas; i++) {
    cout << "P" << i + 1 << ": " << banco[i].enunciado << endl;
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

  cout << "RESULTADO: " << puntuacion << "/" << numPreguntas << endl;
  if (puntuacion >= 9)
    cout << "Nivel: SOBRESALIENTE. Dominas el Tema 1." << endl;
  else if (puntuacion >= 7)
    cout << "Nivel: NOTABLE. Repasa detalles de Multithreading." << endl;
  else
    cout << "Nivel: NECESITA MEJORAR. Vuelve a leer el PDF." << endl;
}

int main() {
  mostrarTest();
  return 0;
}