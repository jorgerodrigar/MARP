// Jorge Rodriguez Garcia
// VJ24

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

class Teclado {
private:
	vector<int>distTo;                                      // vector de distancias al origen
	IndexPQ<int> priCola;

	void relax(const AristaDirigida<int>& a, const vector<int>& cargas) {
		int v = a.from();
		int w = a.to();

		// relajamos las distancias de las adyacentes actualizandolas tambien con el tiempo de carga de cada una
		if (distTo[w] > distTo[v] + a.valor() + cargas[w]) {
			distTo[w] = distTo[v] + a.valor() + cargas[w];
			priCola.update(w, distTo[w]);
		}
	}

public:
	Teclado(const GrafoDirigidoValorado<int>& grafo, const vector<int>& cargas):
		distTo(grafo.V(), numeric_limits<int>::max()), priCola(grafo.V()) {

		distTo[0] = cargas[0];        // la distancia del origen sera su tiempo de carga
		priCola.push(0, distTo[0]);

		while (!priCola.empty()) {    // para cada vertice relajamos sus adyacentes
			int v = priCola.top().elem; priCola.pop();
			for (AristaDirigida<int> a : grafo.ady(v)) {
				relax(a, cargas);
			}
		}
	}

	int getDistTo(int i) { return distTo[i]; }
};

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
    Teclado teclado(grafo, cargas);
	int dist = teclado.getDistTo(grafo.V() - 1);
	if (dist == numeric_limits<int>::max())cout << "IMPOSIBLE" << endl;
	else cout << dist << endl;
    
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
