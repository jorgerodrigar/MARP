// Jorge Rodriguez Garcia
// VJ24

#include "Matriz.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int maxOro(const vector<pair<int, int>>& cofres, const int& T) {
	int n = cofres.size() - 1;
	Matriz<int> matriz(n + 1, T + 1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= T; j++) {
			if (3 * cofres[i].first > j)matriz[i][j] = matriz[i - 1][j];
			else matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - 3 * cofres[i].first] + cofres[i].second);
		}
	}
	return matriz[n][T];
}

int numCofres(const vector<pair<int, int>>& cofres, const int& T, Matriz<int>& matriz) {
	int n = cofres.size() - 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= T; j++) {
			if (3 * cofres[i].first > j)matriz[i][j] = matriz[i - 1][j];
			else matriz[i][j] = max(matriz[i - 1][j], matriz[i - 1][j - 3 * cofres[i].first] + 1);
		}
	}
	return matriz[n][T];
}

vector<int> calcularCofresCogidos(const vector<pair<int, int>>& cofres, const int& T, const Matriz<int>& matriz) {
	int n = cofres.size() - 1;
	vector<int> cualesCofres(n + 1, 0);
	int i = n; int j = T;

	while (j > 0 && i > 0) {
		if (cofres[i].first <= j && matriz[i][j] != matriz[i - 1][j]) {
			cualesCofres[i]++;
			j -= cofres[i].first;
		}
		else --i;
	}

	return cualesCofres;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int T, N;
	cin >> T >> N;
    
    if (! std::cin)
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
	cout << maxOro(cofres, T) << endl << numCofres(cofres, T, matriz) << endl;
	vector<int> cualesCofres = calcularCofresCogidos(cofres, T, matriz);

	for (int i = 0; i < cualesCofres.size(); i++) {
		if (cualesCofres[i] != 0) cout << cofres[i].first << " " << cofres[i].second << endl;
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