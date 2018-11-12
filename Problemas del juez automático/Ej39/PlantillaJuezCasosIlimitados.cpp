// Jorge Rodriguez Garcia
// VJ24

#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>

using namespace std;

void relax(AristaDirigida<int> a, vector<int>& distTo, IndexPQ<int>& priCola)
{
	int v = a.from(), w = a.to();
	if (distTo[w] > distTo[v] + a.valor())
	{
		distTo[w] = distTo[v] + a.valor();
		priCola.update(w, distTo[w]);
	}
}

// uso dijkstra para encontrar el camino mas corto a una casa partiendo del origen (o al reves cuando utilizo el inverso del grafo)
void resolver(const GrafoDirigidoValorado<int>& grafo, vector<int>& distTo, const int& origen) {
	IndexPQ<int> priCola(grafo.V());
	for (int v = 0; v < grafo.V(); v++) 
		distTo[v] = INT_MAX;
	distTo[origen] = 0;
	priCola.push(origen, 0);

	while (!priCola.empty())
	{
		int v = priCola.top().elem; priCola.pop();
		for (AristaDirigida<int> a : grafo.ady(v))
			relax(a, distTo, priCola);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, C, O, P;
	cin >> N >> C;
    
    if (! std::cin)
        return false;

	// construyo el pueblo con sus casas (vertices) y sus caminos (aristas)
	GrafoDirigidoValorado<int> grafo(N);
	for (int i = 0; i < C; i++) {
		int ini, fin, esfuerzo;
		cin >> ini >> fin >> esfuerzo;
		AristaDirigida<int> arista(ini - 1, fin - 1, esfuerzo);
		grafo.ponArista(arista);
	}

	cin >> O >> P;
	int esfuerzoTotal = 0;
	bool imposible = false;

	vector<int>distTo; distTo.resize(N);         // distancias del origen al destino
	vector<int>distToInv; distToInv.resize(N);   // distancias del destino al origen

	resolver(grafo, distTo, O - 1);              // hallo el camino minimo con el grafo y el grafo inverso
	resolver(grafo.inverso(), distToInv, O - 1); // para rellenar los dos tipos de distancia

	// y para cada destinatario sumo la distancia que cuesta ir hasta el y la vuelta (distToInv)
	// si alguna de las dos distancias no ha sido modificada significa que no se puede ir o volver a esa casa
	for (int i = 0; i < P; i++) {
		int destinatario;
		cin >> destinatario;
		if (distTo[destinatario - 1] == INT_MAX)imposible = true;
		esfuerzoTotal += distTo[destinatario - 1];
		if (distToInv[destinatario - 1] == INT_MAX)imposible = true;
		esfuerzoTotal += distToInv[destinatario - 1];
	}
	if (imposible)cout << "Imposible" << endl;
	else cout << esfuerzoTotal << endl;

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