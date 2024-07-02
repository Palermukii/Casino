#include "ruleta.h"
#include "blackjack.h"
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

int main() {
  int opcion;
  string eleccion;
  while (true) {
      cout << "Bienvenido al casino, que juego desea jugar: " << endl;
      cout << "1. Ruleta" << 
      endl << "2. Blackjack" << endl;
      cin >> eleccion;

      // Comparar la opcion con los numeros permitidos
      if (eleccion == "1" || eleccion == "2") {
        opcion = stoi(eleccion); // Convertir la cadena a entero
        break;                   // Salir del bucle si la opcion es valida
      } else {
        // Explicar al usuario que los datos no son correctos
        cout << "Los datos ingresados no son validos, por favor revise su eleccion e ingrese el numero de nuevo\n";
        // continue; no es necesario ya que el bucle while se repetirá
        // automáticamente
      }
    }

  switch (opcion) {


  case 1:
    ruleta();
    break;
  case 2:
    blackjack();
    break;
  default:
    cout << "Opción no válida." << endl;
    return 0;
  }

  return 0;
}
