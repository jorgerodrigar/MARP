// Jorge Rodríguez García
// VJ24

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

bool resuelveCaso() {
	int V, E, K;
	cin >> V >> E;
    
    if (! std::cin)
        return false;

	// guardo las aristas en un vector de aristas
	vector<Arista<int>> aristas;
	for (int i = 0; i < E; i++) {
		int ini, fin, anchura;
		cin >> ini >> fin >> anchura;
		Arista<int> arista(ini - 1, fin - 1, anchura);
		aristas.push_back(arista);
	}

	// para cada caso de prueba, añado las aristas por las que podria pasar el camion a un cto. disjunto
	// asi me aseguro de que el camion puede pasar por todo "grafo", solo  faltaria comprobar si puede llegar a su destino
	cin >> K;
	for (int i = 0; i < K; i++) {
		ConjuntosDisjuntos grafo(V);
		int ini, fin, anchura;
		cin >> ini >> fin >> anchura;
		for (int j = 0; j < aristas.size(); j++) {
			if (aristas[j].valor() >= anchura)grafo.unir(aristas[j].uno(), aristas[j].otro(aristas[j].uno()));
		}

		// si el inicio y el destino pertenecen al mismo conjunto es que el camion puede realizar su recorrido
		if (grafo.unidos(ini - 1, fin - 1))cout << "SI" << endl;
		else cout << "NO" << endl;
	}

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