#include <chrono>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <iomanip> // fixed y setprecision
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

// Colores para el texto
#define Negro "\033[0;30m"
#define Rojo "\033[0;31m"
#define Verde "\033[0;32m"
#define Amarillo "\033[0;33m"
#define Azul "\033[0;34m"
#define Magenta "\033[0;35m"
#define Cyan "\033[0;36m"
#define Blanco "\033[0;37m"
#define RESET_COLOR "\033[0m"

struct tabla {
  int numero[37];
  string color[37];
  int columna[37];
  int fila[37];
};

struct Apuesta {
  string tipo;  // "numero", "color", "docena", "caballo"
  int numero;   // Para "numero"
  int numero1;  // Para caballo
  int numero2;  // Para caballo
  string color; // Para "color"
  int docena;   // Para "docena"
  string par;   // Para "par o impar"
  double cantidad;
};
int i = 0;
int numero1;
int numero2; // numeros de caballo

void pantallaCarga() {
  const int totalSteps = 20;
  cout << "CARGANDO...\n";
  cout << "====================\n";
  for (int i = 0; i <= totalSteps; i++) {
    cout << "[";
    for (int j = 0; j < i; j++) {
      cout << "#";
    }
    for (int j = i; j < totalSteps; j++) {
      cout << " ";
    }
    cout << "] " << (i * 100) / totalSteps << "%\r";
    cout.flush();
    Sleep(100); // 100 milisegundos
  }
  cout << "\n====================\n";
  cout << "Carga completa!\n";
}

int girarRuleta() {
  srand(time(NULL));
  return rand() % 37;
}

double seleccionarFicha() { // Funcion para determinar la cantidad de dinero que se apuesta
  vector<double> fichas = {30, 60, 150, 300, 600, 1000, 2000, 3000, 6000};
  int opcionFicha;
  cout << "Seleccione la ficha a apostar:\n";
  for (int i = 0; i < fichas.size(); ++i) {
    cout << i + 1 << ". " << fichas[i] << " unidades\n";
  }
  cout << "Seleccione una opcion: ";
  cin >> opcionFicha;

  if (opcionFicha < 1 || opcionFicha > fichas.size()) {
    cout << "Opcion de ficha invalida!\n";
    return 0;
  }

  return fichas[opcionFicha - 1];
}

int ruleta() {
  cout << fixed << setprecision(0); // Permite que en las salidas con numeros
                                    // grandes se muestre completa
  struct tabla tabla1 = {
      {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
       13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
       26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36},
      {"VERDE", "ROJO",  "NEGRO", "ROJO",  "NEGRO", "ROJO",  "NEGRO", "ROJO",
       "NEGRO", "ROJO",  "NEGRO", "NEGRO", "ROJO",  "NEGRO", "ROJO",  "NEGRO",
       "ROJO",  "NEGRO", "ROJO",  "ROJO",  "NEGRO", "ROJO",  "NEGRO", "ROJO",
       "NEGRO", "ROJO",  "NEGRO", "ROJO",  "NEGRO", "NEGRO", "ROJO",  "NEGRO",
       "ROJO",  "NEGRO", "ROJO",  "NEGRO", "ROJO"},
      {0, 1, 1, 1, 2, 2, 2, 3, 3, 3,  4,  4,  4,  5,  5,  5,  6,  6, 6,
       7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12},
      {0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
       1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}};

  int opcion;
  string eleccion;
  double saldo = 1000.0; // Saldo inicial
  vector<Apuesta> apuestas;
  cout << Cyan "\t Bienvenido a la ruleta \t" RESET_COLOR<< endl;
  do {

    while (true) {
      cout << endl <<Magenta " === MENU DE APUESTAS === "  RESET_COLOR << endl;
      cout << "Su saldo es de " << saldo << endl;
      cout << "1. Apostar a un numero" << endl;
      cout << "2. Apostar a un color" << endl;
      cout << "3. Apostar a una docena" << endl;
      cout << "4. Apostar a un caballo" << endl;
      cout << "5. Apostar a par o impar" << endl;
      cout << "6. Girar la ruleta" << endl;
      cout << "7. Ingresar mas fichas" << endl;
      cout << "8. Salir" << endl;
      cout <<Magenta "Seleccione una opcion: " RESET_COLOR;
      cin >> eleccion;

      // Comparar la opcion con los numeros permitidos
      if (eleccion == "1" || eleccion == "2" || eleccion == "3" ||
          eleccion == "4" || eleccion == "5" || eleccion == "6" ||
          eleccion == "7" || eleccion == "8") {
        opcion = stoi(eleccion); // Convertir la cadena a entero
        break;                   // Salir del bucle si la opcion es valida
      } else {
        // Explicar al usuario que los datos no son correctos
        cout << "Los datos ingresados no son validos, por favor revise su "
                "eleccion e ingrese el numero de nuevo\n";
        // continue; no es necesario ya que el bucle while se repetirá
        // automáticamente
      }
    }

    switch (opcion) {
    case 1: { // Apuesta de pleno
      int numero;
      double cantidad;
      cout << "Ingrese el numero al que desea apostar (0-36): ";

      // Verificar que la entrada es un número
      while (!(cin >> numero) || numero < 0 || numero > 36) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Descartar la entrada incorrecta
        cout << "Numero invalido! Ingrese un numero entre 0 y 36: ";
      }

      cantidad = seleccionarFicha();
      if (cantidad > saldo || cantidad == 0) {
        cout << "Saldo insuficiente o ficha invalida!\n";
        break;
      }

      saldo -= cantidad;
      apuestas.push_back({"numero", numero, 0, 0, "", 0, "", cantidad});
      break;
    }

    case 2: { // Apuesta por color
      string color;
      double cantidad;
      cout << "Ingrese el color al que desea apostar (ROJO/NEGRO/VERDE): ";
      cin >> color;
      for (auto &c : color)
        c = toupper(c); // Convertir a mayúsculas
      if (color != "ROJO" && color != "NEGRO" && color != "VERDE") {
        cout << "Color invalido!\n";
        break;
      }
      cantidad = seleccionarFicha();
      if (cantidad > saldo || cantidad == 0) {
        cout << "Saldo insuficiente o ficha invalida!\n";
        break;
      }
      saldo -= cantidad;
      apuestas.push_back({"color", 0, 0, 0, color, 0, "", cantidad});
      break;
    }
    case 3: { // Apuesta por docena
      int docena;
      double cantidad;
      cout << "Ingrese la docena a la que desea apostar (1-3): ";
      while (!(cin >> docena) || docena < 1 || docena > 3) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Descartar la entrada incorrecta
        cout << "Docena invalida! Ingrese un numero entre 1 y 3: ";
      }
      cantidad = seleccionarFicha();
      if (cantidad > saldo || cantidad == 0) {
        cout << "Saldo insuficiente o ficha invalida!\n";
        break;
      }
      saldo -= cantidad;
      apuestas.push_back({"docena", 0, 0, 0, "", docena, "", cantidad});
      break;
    }
    case 4: { // Apuesta de caballo
      int numero1, numero2;
      double cantidad;
      cout << "Ingrese el primer numero del caballo (1-36): ";
      while (!(cin >> numero1) || numero1 < 1 || numero1 > 36) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Descartar la entrada incorrecta
        cout << "Numero invalido! Ingrese un numero entre 1 y 36: ";
      }
      cout << "Ingrese el segundo numero del caballo (1-36): ";
      while (!(cin >> numero2) || numero2 < 1 || numero2 > 36) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Descartar la entrada incorrecta
        cout << "Numero invalido! Ingrese un numero entre 1 y 36: ";
      }
      // Validar si los números son contiguos horizontalmente o verticalmente
      bool valido = false;
      if (numero1 >= 0 && numero1 <= 36 && numero2 >= 0 && numero2 <= 36) {
        if ((abs(numero1 - numero2) == 1 &&
             tabla1.columna[numero1] == tabla1.columna[numero2]) ||
            (abs(numero1 - numero2) == 3 &&
             tabla1.fila[numero1] == tabla1.fila[numero2])) {
          valido = true;
        }
      }

      if (!valido) {
        cout << "Numero de caballo invalido!\n";
        break;
      }

      cantidad = seleccionarFicha();
      if (cantidad > saldo || cantidad == 0) {
        cout << "Saldo insuficiente o ficha invalida!\n";
        break;
      }
      saldo -= cantidad;
      apuestas.push_back({"caballo", 0, numero1, numero2, "", 0, "", cantidad});
      break;
    }
    case 5: { // Apuesta por par o impar
      string par;
      double cantidad;
      cout << "Ingrese si desea apostarle a un par o impar (par-impar): ";
      cin >> par;
      for (auto &c : par)
        c = toupper(c); // Convertir a mayúsculas
      if (par != "PAR" && par != "IMPAR") {
        cout << "Apuesta invalida!\n";
        break;
      }
      cantidad = seleccionarFicha();
      if (cantidad > saldo || cantidad == 0) {
        cout << "Saldo insuficiente o ficha invalida!\n";
        break;
      }
      saldo -= cantidad;
      apuestas.push_back({"par", 0, 0, 0, "", 0, par, cantidad});
      break;
    }
    case 6: { // En caso de elegrir girar la ruleta
      pantallaCarga();
      int resultado = girarRuleta();
      cout <<Verde "El numero que salio es " RESET_COLOR << tabla1.numero[resultado]
           << ", el color es " << tabla1.color[resultado] << ", la columna es "
           << tabla1.columna[resultado] << " y la fila es "
           << tabla1.fila[resultado] << endl;

      for (const auto &apuesta : apuestas) { // Se recorre el vector para poder hacer las comprobaciones y determinar si gano o perdio la apuesta.
        if (apuesta.tipo == "numero" &&
            tabla1.numero[resultado] == apuesta.numero) { // Verificacion de apuesta por pleno
          double ganancia = apuesta.cantidad * 35;
          cout << "Felicitaciones! Ha ganado " << ganancia
               << " apostando al numero " << apuesta.numero << "!\n";
          saldo += ganancia;
        } else if (apuesta.tipo == "color" &&
                   tabla1.color[resultado] == apuesta.color) { // Verificacion de apuesta por color
          double ganancia = apuesta.cantidad * 2;
          cout << "Felicitaciones! Ha ganado " << ganancia
               << " apostando al color " << apuesta.color << "!\n";
          saldo += ganancia;
        } else if (apuesta.tipo == "docena" &&
                   ((apuesta.docena - 1) * 12 < tabla1.numero[resultado] &&
                    tabla1.numero[resultado] <= (apuesta.docena * 12))) { // Verificacion de apuesta por docena
          double ganancia = apuesta.cantidad * 3;
          cout << "Felicitaciones! Ha ganado " << ganancia
               << " apostando a la docena " << apuesta.docena << "!\n";
          saldo += ganancia;
        } else if (apuesta.tipo == "caballo" &&
                       tabla1.numero[resultado] == apuesta.numero1 ||
                   tabla1.numero[resultado] == apuesta.numero2) { // Verificacion de apuesta por caballo
          double ganancia = apuesta.cantidad * 17;
          cout << "Felicitaciones! Ha ganado " << ganancia
               << " apostando al caballo " << apuesta.numero1 << "-"
               << apuesta.numero2 << "!\n";
          saldo += ganancia;
        } else if (apuesta.tipo == "par" &&
                       (tabla1.numero[resultado] % 2 == 0 &&
                        apuesta.par == "PAR") ||
                   (tabla1.numero[resultado] % 2 == 1 &&
                    apuesta.par == "IMPAR")) { // Verificacion de apuesta de par
          double ganancia = apuesta.cantidad * 2;
          cout << "Felicitaciones! Ha ganado " << ganancia
               << " apostando a los muneros " << apuesta.par << "es!\n";
          saldo += ganancia;
        } else { // En caso de no ganar ninguna apuesta
          cout << "Lo siento, ha perdido la apuesta de tipo " << apuesta.tipo
               << ".\n";
        }
      }
      apuestas.clear(); // Se vacia el vector apuestas
      cout << "Saldo actual: " << saldo << endl;
      break;
    }

    case 7: {
      int ingreso;
      cout << "Ingrese la cantidad de dinero que desea añadir a su saldo: "
           << endl;
      while (!(cin >> ingreso) || ingreso < 0 || ingreso > 1000000) {
        cin.clear(); // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Descartar la entrada incorrecta
        cout << "Numero invalido! Ingrese un numero entre 1 y 100.000: ";
      }
      saldo += ingreso;
      break;
    }
    case 8:
      cout << "Gracias por jugar! Su saldo final es " << saldo << endl;
      break;
    default:
      cout << "Opcion invalida!\n";
      break;
    }
  } while (opcion != 8); // Si la opcion es 8, se sale del while

  return 0;
}