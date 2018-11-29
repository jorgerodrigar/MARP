//*****************
// IMPORTANTE
//
// Jorge Rodriguez Garcia
// VJ24
// MARP23
//
//***************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Estrategia voraz:
/*Ordeno los aviones segun el combustible que les queda por rellenar en orden ascendente.
De esta forma, empiezo rellenando los que menos combustible necesitan, para gastar el minimo
posible y asi llenar un numero maximo de aviones: mientras no haya recorrido todos los aviones
y no me haya quedado sin combustible por repartir, si al llenar el avion actual no se me acaba
el combustible, lo lleno y le resto al combustible el que he depositado en el avion. En el momento
en que al llenar un avion me quede sin combustible, paro (lineas 57-64).
*/


// Demostrar optimalidad:
/*Dadas una solucion voraz y una solucion optima, con los combustibles c1, c2, ..., cn que les
ha repartido a los aviones: si en una posicion dada el combustible repartido por la voraz es distinto 
que el de la optima (ci != cj, respectivamente), ci no podria ser menor que cj, ya que habria repartido
menos combustible en esa posicion que la solucion optima, y por tanto seria una solucion
mejor, lo cual es IMPOSIBLE. Por tanto, ci tendria que ser mayor que cj, y cj se encontraria mas adelante
en la solucion voraz, por lo que podria intercambiarlos y asi igualarse a la optima.
*/


bool  resuelveCaso() {
    int N, L;

	cin >> N >> L;

	if (!cin)return false;

	vector<int> aviones;
	for (int i = 0; i < N; i++) { //O(N), siendo N el numero de aviones
		int capacidad, ocupado;
		cin >> capacidad >> ocupado;
		aviones.push_back(capacidad - ocupado);
	}
	sort(aviones.begin(), aviones.end());

    // Algoritmo -> O(N), siendo N el numero de aviones
	int i = 0;
	int maxAviones = 0;
	bool sinCombustible = false;

	while (i < aviones.size() && !sinCombustible) {
		if (L - aviones[i] >= 0) {
			maxAviones++;
			L -= aviones[i];
		}
		else sinCombustible = true;
		i++;
	}
    
	cout << maxAviones << endl;
    
    
    return true;
}

int main() {
    
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    
   while (resuelveCaso()) {} //Resolvemos todos los casos

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
