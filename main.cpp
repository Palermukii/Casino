#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Definición de la estructura para las cartas
struct Cartas {
  int numero[52];
  string simbolo[52];
  string nombre[52];
};

// Función para obtener un valor numérico de la carta
int valorCarta(int numero) { return (numero > 10) ? 10 : numero; }

// Función para ajustar el valor del As en caso necesario
int ajustarValorAs(int total, int asCount) {
  while (asCount > 0 && total + 10 <= 21) {
    total += 10;
    asCount--;
  }
  return total;
}

// Función que simula el juego del crupier
int jugarCrupier(const Cartas &cartas, int total, int asCount) {
  // Ajustar el valor del As si es necesario
  total = ajustarValorAs(total, asCount);

  // Jugar del crupier según reglas estándar (debe alcanzar al menos 17)
  while (total < 17) {
    int nueva_carta = rand() % 52;
    int valor = valorCarta(cartas.numero[nueva_carta]);
    total += valor;
    if (cartas.numero[nueva_carta] == 1) {
      asCount++;
    }
    cout << "El crupier saca una carta: " << cartas.nombre[nueva_carta]
         << " de " << cartas.simbolo[nueva_carta] << endl;

    // Ajustar el valor del As si es necesario
    total = ajustarValorAs(total, asCount);
  }

  cout << "Total del crupier: " << total << endl;
  return total;
}

// Función principal para el jugador
void jugarJugador(const Cartas &cartas, double &saldo) {
  srand(time(NULL));

  double apuesta;

  cout << "Tu saldo actual es: $" << saldo << endl;
  cout << "¿Cuánto quieres apostar? ";
  cin >> apuesta;

  if (apuesta > saldo) {
    cout << "No tienes suficiente saldo para esa apuesta." << endl;
    return;
  }

  saldo -= apuesta;

  // Cartas del jugador
  int carta1_jugador = rand() % 52;
  int carta2_jugador = rand() % 52;

  cout << "Tus cartas son: " << cartas.nombre[carta1_jugador] << " de "
       << cartas.simbolo[carta1_jugador] << " y "
       << cartas.nombre[carta2_jugador] << " de "
       << cartas.simbolo[carta2_jugador] << endl;

  int total_jugador = valorCarta(cartas.numero[carta1_jugador]) +
                      valorCarta(cartas.numero[carta2_jugador]);
  int asCount_jugador = (cartas.numero[carta1_jugador] == 1) +
                        (cartas.numero[carta2_jugador] == 1);

  // Ajustar el valor del As si es necesario
  total_jugador = ajustarValorAs(total_jugador, asCount_jugador);
  cout << "Total: " << total_jugador << endl;

  // Cartas del crupier
  int carta1_crupier = rand() % 52;
  int carta2_crupier = rand() % 52;

  int total_crupier = valorCarta(cartas.numero[carta1_crupier]) +
                      valorCarta(cartas.numero[carta2_crupier]);
  int asCount_crupier = (cartas.numero[carta1_crupier] == 1) +
                        (cartas.numero[carta2_crupier] == 1);

  cout << "Cartas del crupier: " << cartas.nombre[carta1_crupier] << " de "
       << cartas.simbolo[carta1_crupier] << " y "
       << cartas.nombre[carta2_crupier] << " de "
       << cartas.simbolo[carta2_crupier] << endl;

  // Mostrar total visible del crupier
  cout << "Total visible del crupier: " << total_crupier << endl;

  char choice;
  do {
    cout << "¿Quieres otra carta? (s/n): ";
    cin >> choice;

    if (choice == 's') {
      int nueva_carta = rand() % 52;
      int valor = valorCarta(cartas.numero[nueva_carta]);
      total_jugador += valor;
      if (cartas.numero[nueva_carta] == 1) {
        asCount_jugador++;
      }
      cout << "Nueva carta: " << cartas.nombre[nueva_carta] << " de "
           << cartas.simbolo[nueva_carta] << endl;
      // Ajustar el valor del As si es necesario
      total_jugador = ajustarValorAs(total_jugador, asCount_jugador);
      cout << "Total: " << total_jugador << endl;

      if (total_jugador > 21) {
        cout << "Te has pasado de 21. Pierdes." << endl;
        cout << "Tu saldo actual es: $" << saldo << endl;
        return;
      }
    }
  } while (choice == 's');

  // Una vez el jugador se planta, se determina el resultado comparando con el
  // crupier
  total_crupier = jugarCrupier(cartas, total_crupier, asCount_crupier);

  // Comparación de resultados
  if (total_jugador > total_crupier || total_crupier > 21) {
    cout << "¡Ganaste!" << endl;
    saldo += 2 * apuesta;
  } else if (total_jugador < total_crupier) {
    cout << "Perdiste." << endl;
  } else {
    cout << "Empate." << endl;
    saldo += apuesta;
  }

  cout << "Tu saldo actual es: $" << saldo << endl;
}

int main() {
  srand(time(NULL));

  // Inicialización de la baraja de cartas
  Cartas baraja = {
      {1,  2,  3,  4, 5,  6,  7,  8,  9, 10, 10, 10, 10, 1,  2,  3, 4, 5,
       6,  7,  8,  9, 10, 10, 10, 10, 1, 2,  3,  4,  5,  6,  7,  8, 9, 10,
       10, 10, 10, 1, 2,  3,  4,  5,  6, 7,  8,  9,  10, 10, 10, 10},
      {"♠", "♠", "♠", "♠", "♠", "♠", "♠", "♠", "♠", "♠", "♠", "♠", "♠",
       "♥", "♥", "♥", "♥", "♥", "♥", "♥", "♥", "♥", "♥", "♥", "♥", "♥",
       "♣", "♣", "♣", "♣", "♣", "♣", "♣", "♣", "♣", "♣", "♣", "♣", "♣",
       "♦", "♦", "♦", "♦", "♦", "♦", "♦", "♦", "♦", "♦", "♦", "♦", "♦"},
      {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
       "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
       "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
       "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}};

  double saldo = 1000.0; // Saldo inicial del jugador
  char jugarDeNuevo;

  do {
    jugarJugador(baraja, saldo);
    if (saldo <= 0) {
      cout << "Te has quedado sin saldo. Fin del juego." << endl;
      break;
    }
    cout << "¿Quieres jugar otra mano? (s/n): ";
    cin >> jugarDeNuevo;
  } while (jugarDeNuevo == 's');

  cout << "Gracias por jugar. Tu saldo final es: $" << saldo << endl;

  return 0;
}
