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

  // Jugar del crupier según reglas estandar (debe alcanzar al menos 17)
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
  cout << "¿Cuanto quieres apostar? ";
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

  // Verificar si el jugador tiene un blackjack
  if ((cartas.numero[carta1_jugador] == 1 &&
       cartas.numero[carta2_jugador] > 10) ||
      (cartas.numero[carta2_jugador] == 1 &&
       cartas.numero[carta1_jugador] > 10)) {
    cout << "¡Blackjack! Ganaste 1.5 veces tu apuesta." << endl;
    saldo += 2.5 * apuesta;
    cout << "Tu saldo actual es: $" << saldo << endl;
    return;
  }

  // Cartas del crupier
  int carta1_crupier = rand() % 52;
  int carta2_crupier = rand() % 52;

  int total_crupier = valorCarta(cartas.numero[carta1_crupier]) +
                      valorCarta(cartas.numero[carta2_crupier]);
  int asCount_crupier = (cartas.numero[carta1_crupier] == 1) +
                        (cartas.numero[carta2_crupier] == 1);

  cout << "Cartas del crupier: " << cartas.nombre[carta1_crupier] << " de "
       << cartas.simbolo[carta1_crupier] << " y una carta oculta" << endl;

  // Mostrar total visible del crupier (solo la primera carta)
  int total_visible_crupier = valorCarta(cartas.numero[carta1_crupier]);
  cout << "Total visible del crupier: " << total_visible_crupier << endl;

  char choice;
  do {
    cout << "Quieres otra carta? (s/n): ";
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

  // Una vez el jugador se planta, mostrar la carta oculta del crupier
  cout << "La carta oculta del crupier es: " << cartas.nombre[carta2_crupier]
       << " de " << cartas.simbolo[carta2_crupier] << endl;
  total_crupier = ajustarValorAs(total_crupier, asCount_crupier);
  cout << "Total del crupier: " << total_crupier << endl;

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
      {"Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica", "Pica",
       "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones", "Corazones",
       "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol", "Trebol",
       "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante", "Diamante"},
      {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
       "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
       "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
       "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}};

  double saldo;

  // Solicitar la cantidad de dinero con la que el jugador desea ingresar
  cout << "Bienvenido al casino. ¿Con cuanto dinero deseas ingresar? $";
  cin >> saldo;

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
