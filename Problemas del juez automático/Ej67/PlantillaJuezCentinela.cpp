// Jorge Rodriguez Garcia
// VJ24

#include "Matriz.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int maxComida(const vector<int>& cubos) {
	int n = cubos.size();
	Matriz<int>tabla(n, n, 0);

	for (int i = 0; i < n; i++)tabla[i][i] = cubos[i];
	for (int i = 0; i < n - 1; i++)tabla[i][i + 1] = max(cubos[i], cubos[i + 1]);

	for (int d = 2; d < n; d++) {
		for (int i = 0; i < n - d; i++) {
			int j = i + d;
			int izq = (cubos[i + 1] > cubos[j]) ? tabla[i + 2][j] : tabla[i + 1][j - 1];
			int der = (cubos[i] > cubos[j - 1]) ? tabla[i + 1][j - 1] : tabla[i][j - 2];
			tabla[i][j] = max(izq, der);
		}
	}

	return tabla[0][n-1];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;
	cin >> N;
    
    if (N == 0)
        return false;
    
	vector<int>cubos;
	//cubos.push_back(0);
	for (int i = 0; i < N; i++) {
		int comida;
		cin >> comida;
		cubos.push_back(comida);
	}

	cout << maxComida(cubos) << endl;

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
