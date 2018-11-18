// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"

using namespace std;

// función que resuelve el problema
void resolver(PriorityQueue<int>& alturas, PriorityQueue<int>& longitudes) {
	int min = 0;

	while(!alturas.empty()) {
		min += abs(alturas.top() - longitudes.top());
		alturas.pop(); longitudes.pop();
	}
    
	cout << min << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;
	cin >> N;

	if (N == 0)
		return false;

	PriorityQueue<int> alturas;
	for (int i = 0; i < N; i++) {
		int altura;
		cin >> altura;
		alturas.push(altura);
	}

	PriorityQueue<int>longitudes;
	for (int i = 0; i < N; i++) {
		int longitud;
		cin >> longitud;
		longitudes.push(longitud);
	}
    
    resolver(alturas, longitudes);
    
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
