// Jorge Rodriguez Garcia
// VJ24

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>

using namespace std;

void relax(const AristaDirigida<int>& a, vector<int>& distTo, 
	IndexPQ<int>& priCola, const vector<int>& cargas) {
	int v = a.from(); 
	int w = a.to();

	// relajamos las distancias de las adyacentes actualizandolas tambien con el tiempo de carga de cada una
	if (distTo[w] > distTo[v] + a.valor() + cargas[w]) {
		distTo[w] = distTo[v] + a.valor() + cargas[w];
		priCola.update(w, distTo[w]);
	}
}

void resolver(const int& dest, const GrafoDirigidoValorado<int>& grafo, const vector<int>& cargas) {
	vector<int>distTo;                                      // vector de distancias al origen
	distTo.resize(grafo.V());
	IndexPQ<int> priCola(grafo.V());

	for (int i = 0; i < grafo.V(); i++)distTo[i] = INT_MAX; // inicialmente todas al maximo
	distTo[0] = cargas[0];                                  // la distancia del origen sera su tiempo de carga
	priCola.push(0, distTo[0]);

	while (!priCola.empty()) {                              // para cada vertice relajamos sus adyacentes
		int v = priCola.top().elem; priCola.pop();
		for (AristaDirigida<int> a : grafo.ady(v)) {
			relax(a, distTo, priCola, cargas);
		}
	}

	// si la distancia destino no ha sido modificada, significa que no se puede llegar a esa pagina
	if (distTo[dest] == INT_MAX)cout << "IMPOSIBLE" << endl;
	else cout << distTo[dest] << endl;
}

bool resuelveCaso() {
	int N, M;
	cin >> N;
    
    if (N==0)
        return false;

	vector<int> cargas;  // almaceno las cargas de cada pagina
	GrafoDirigidoValorado<int> grafo(N);
	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		cargas.push_back(t);
	}

	cin >> M;            // establezco los enlaces de pagina a pagina
	for (int i = 0; i < M; i++) {
		int ini, fin, valor;
		cin >> ini >> fin >> valor;
		AristaDirigida<int> arista(ini-1, fin-1, valor);
		grafo.ponArista(arista);
	}
    
	// resuelvo el problema usando dijkstra (camino mas corto en un grafo dirigido y valorado)
    resolver(grafo.V() - 1, grafo, cargas); 
    
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
