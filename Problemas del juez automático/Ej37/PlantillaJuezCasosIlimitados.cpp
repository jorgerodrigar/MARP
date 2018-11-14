// Jorge Rodríguez García
// VJ24

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// utilizo kruskal para resolver el problema -> O(max(V, E)*logE), siendo E el numero de aristas
void resolver(PriorityQueue<Arista<int>>& pq, const int& I) {
	ConjuntosDisjuntos disj(I);
	int coste = 0;

	while (!pq.empty()) {             // hallo el arbol de recubrimiento minimo
		Arista<int> arista = pq.top(); pq.pop();
		int v = arista.uno(); int w = arista.otro(v);
		if (!disj.unidos(v, w)) {
			disj.unir(v, w);
			coste += arista.valor();  // actualizo el coste de los puentes
		}
	}

	// si hay mas de un cjto disjunto significa que no habia puentes suficientes para unir todas las islas
	if (disj.num_cjtos() > 1)cout << "No hay puentes suficientes" << endl;
	else cout << coste << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int I, P;
	cin >> I >> P;
    
    if (! std::cin)
        return false;

	PriorityQueue<Arista<int>> pq;
	for (int i = 0; i < P; i++) {
		int ini, fin, valor;
		cin >> ini >> fin >> valor;
		Arista<int>arista(ini - 1, fin - 1, valor);
		pq.push(arista);
	}
    
    resolver(pq, I);
    
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