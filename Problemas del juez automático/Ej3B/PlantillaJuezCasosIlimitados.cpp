// Jorge Rodriguez Garcia
// VJ24

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

class Cole {                      // clase Cole que resuelve el ejercicio
private:
	vector<int>distTo;            // distancia de una interseccion al origen
	IndexPQ<int>pq;
	vector<int>numCaminos;        // numero de caminos que hay para llegar a cada interseccion

	void relax(const AristaDirigida<int>& a) {
		int v = a.from(); int w = a.to();
		if (distTo[w] > distTo[v] + a.valor()) {
			distTo[w] = distTo[v] + a.valor();
			pq.update(w, distTo[w]);
			numCaminos[w] = numCaminos[v];
		}
		else if (distTo[w] == distTo[v] + a.valor()) {
			numCaminos[w] += numCaminos[v];
		}
	}

public:
	Cole(const GrafoDirigidoValorado<int>& grafo) :distTo(grafo.V(), numeric_limits<int>::max()),
		pq(grafo.V()), numCaminos(grafo.V(), 0) {
		pq.push(0, 0);
		distTo[0] = 0;
		numCaminos[0] = 1;

		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (AristaDirigida<int>a : grafo.ady(v))
				relax(a);
		}
	}

	vector<int> NumCaminos() { return numCaminos; }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, C;
	cin >> N >> C;
    
    if (! std::cin)
        return false;

	GrafoDirigidoValorado<int> grafo(N);
	for (int i = 0; i < C; i++) {
		int ini, fin, valor;
		cin >> ini >> fin >> valor;
		AristaDirigida<int> aIda(ini - 1, fin - 1, valor);
		AristaDirigida<int> aVuelta(fin - 1, ini - 1, valor);
		grafo.ponArista(aIda);
		grafo.ponArista(aVuelta);
	}
    
	Cole cole(grafo);
	cout << cole.NumCaminos()[N - 1] << endl;
    
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