// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// función que resuelve el problema
void resolver(vector<int>& voltajes, const int& V) {
	int maximoCoches = 0;
	int maximos = voltajes.size() - 1;
	int minimos = 0;

	while (minimos - maximos < 0) {
		if (voltajes[minimos] + voltajes[maximos] >= V) {
			maximoCoches++;
			minimos++;
			maximos--;
		}
		else minimos++;
	}

	cout << maximoCoches << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int N, V;
	cin >> N >> V;

	vector<int> voltajes;
	for (int i = 0; i < N; i++) {
		int voltaje;
		cin >> voltaje;
		voltajes.push_back(voltaje);
	}
	sort(voltajes.begin(), voltajes.end());
    
    resolver(voltajes, V);
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}