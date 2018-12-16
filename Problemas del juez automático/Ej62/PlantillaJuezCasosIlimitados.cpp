// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <algorithm>

using namespace std;

// establece la casilla i, j al maximo entre las tres casillas adyacentes de su fila de arriba mas ella misma (si se puede)
// asi, al llegar la ultima fila tendra los valores acumulados de los maximos de sus adyacentes de arriba
void estableceCasilla(const int& i, const int& j, Matriz<int>& tablero) {
	if (i - 1 >= 0) {
		if (j - 1 >= 0 && j + 1 < tablero.numcols())
			tablero[i][j] += max(tablero[i - 1][j - 1], max(tablero[i - 1][j], tablero[i - 1][j + 1]));
		else if (j - 1 >= 0)
			tablero[i][j] += max(tablero[i - 1][j - 1], tablero[i - 1][j]);
		else
			tablero[i][j] += max(tablero[i - 1][j], tablero[i - 1][j + 1]);
	}
}

int maxCantidad(Matriz<int>& tablero) {
	int max = -1, columna = -1;

	for (int i = 0; i < tablero.numfils(); i++) {
		for (int j = 0; j < tablero.numcols(); j++) {
			estableceCasilla(i, j, tablero);
			// si es la ultima fila, elegimos el valor mayor (resultado) y guardamos su columna
			if (i == tablero.numfils() - 1 && tablero[i][j] > max) {
				max = tablero[i][j];
				columna = j;
			}
		}
	}
	return columna;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;
	cin >> N;
    
    if (! std::cin)
        return false;

	Matriz<int> tablero(N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int numero;
			cin >> numero;
			tablero[i][j] = numero;
		}
	}

	int columna = maxCantidad(tablero); // escribimos el valor maximo y la columna en la que se encuentra
	cout << tablero[N - 1][columna] << " " << columna + 1 << endl;
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}