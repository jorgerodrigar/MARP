// Jorge Rodriguez Garcia
// VJ24

#include "Matriz.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// calcula el maximo de oro que se puede coger de los cofres del vector "cofres", en el tiempo T
int maxOro(const vector<pair<int, int>>& cofres, const int& T, Matriz<int>& matriz) {
	int n = cofres.size() - 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= T; j++) {
			if (3 * cofres[i].first > j)matriz[i][j] = matriz[i - 1][j]; // si no te da tiempo a bajar a por el, no lo coges (tardas 1 profundidad en bajar y 2 en subir)
			else matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - 3 * cofres[i].first] + cofres[i].second); // si no, el maximo resultado de cogerlo o no cogerlo
		}
	}
	return matriz[n][T];
}

// devuelve un vector con las posiciones de los cofres que he cogido
vector<int> calcularCofresCogidos(const vector<pair<int, int>>& cofres, const int& T, const Matriz<int>& matriz) {
	int n = cofres.size() - 1;
	vector<int> cualesCofres;                   // guarda las posiciones de los cofres que he cogido
	int i = n; int j = T;

	for (int i = n; i >= 1; i--)
	{
		if (matriz[i][j] != matriz[i - 1][j]) { // si lo he cogido
			cualesCofres.push_back(i);          // añado su posicion al vector
			j = j - 3 * cofres[i].first;
		}
	}

	return cualesCofres;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int T, N;
	cin >> T >> N;

	if (!std::cin)
		return false;

	vector<pair<int, int>> cofres;
	cofres.push_back({ 0, 0 }); // porque luego se empieza a recorrer desde el 1
	for (int i = 0; i < N; i++) {
		int profundidad, oro;
		cin >> profundidad >> oro;
		cofres.push_back({ profundidad, oro });
	}

	int n = cofres.size() - 1;
	Matriz<int> matriz(n + 1, T + 1, 0);
	int maxOroCogido = maxOro(cofres, T, matriz);
	vector<int> cualesCofres = calcularCofresCogidos(cofres, T, matriz);
	int cuantosCofres = cualesCofres.size();

	cout << maxOroCogido << endl << cuantosCofres << endl;

	for (int i = cualesCofres.size() - 1; i >= 0; i--) {
		cout << cofres[cualesCofres[i]].first << " " << cofres[cualesCofres[i]].second << endl;
	}
	cout << "----" << endl;

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