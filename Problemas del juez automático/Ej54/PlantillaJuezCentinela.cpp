// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

// función que resuelve el problema
void resolver(priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>>& edificios) {
	int maxTuneles = 1;   // un tunel como minimo (1 edificio)
	pair<int, int> actual = edificios.top();
	edificios.pop();

	while (!edificios.empty()) {
		if (actual.first >= edificios.top().second) {
			actual = edificios.top();
			maxTuneles++;
		}
		edificios.pop();
	}
    
	cout << maxTuneles << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, izq, der;
	cin >> N;
    
	if (N == 0)
		return false;
    
	// edificios ordenados de mayor a menor segun sus posiciones
	priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> edificios;
	for (int i = 0; i < N; i++) {
		cin >> izq >> der;
		pair<int, int> par = { izq, der };
		edificios.push(par);
	}

    resolver(edificios);
    
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
