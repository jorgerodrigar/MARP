//************************************************
 // IMPORTANTE:
 // Jorge Rodriguez Garcia
 //
//************************************************


// Comentar las librerias que no se usen
//#include "PriorityQueue.h"
//#include "Grafo.h"
//#include "GrafoDirigido.h"
#include "GrafoDirigidoValorado.h"
//#include "ConjuntosDisjuntos.h"
#include "IndexPQ.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// *********************************
// Explicación de la solucion del problema
// Coste de la solucion
// Poner comentarios en el codigo
// **********************************

class PerseoLLaves   // utilizo Dijkstra para resolver el problema (camino minimo) O(max(E, V)*logV),
{                    // siendo E los caminos a las islas y V las islas
private:
	vector<int> distTo;
	IndexPQ<int> pq;

	// relax original, pero teniendo en cuenta los tiempos que tarda en recorrer cada isla
	void relax(AristaDirigida<int> e, const vector<int>& tiempoIslas)
	{
		int v = e.from(), w = e.to();
		if (distTo[w] > distTo[v] + e.valor() + tiempoIslas[w])
		{
			distTo[w] = distTo[v] + e.valor() + tiempoIslas[w];
			pq.update(w, distTo[w]);
		}
	}

public:
	PerseoLLaves(GrafoDirigidoValorado<int> G, int s, const vector<int>& tiempoIslas, const vector<bool>& llaves, bool& llave):
		distTo(G.V(), numeric_limits<int>::max()), pq(G.V())
	{
		distTo[s] = tiempoIslas[s];  // tiempo que tarda en recorrer la primera isla
		pq.push(s, distTo[s]);

		while (!pq.empty())
		{
			int v = pq.top().elem; pq.pop();
			for (AristaDirigida<int> e : G.ady(v))
				relax(e, tiempoIslas);

			// si esa isla tiene llave la marcamos como cogida
			// si al final la llave no esta cogida no podremos entrar al Olimpo
			if (llaves[v])llave = true;
		}
	}

	vector<int> getDists() { return distTo; }
};

bool resuelveCaso () {
    int I,N,L,Perseo, Puerta;
    std::cin >> I;
    if (!std::cin) return false;
    std::cin >> N >> L >> Perseo >> Puerta;
    --Perseo; --Puerta;
    //Lectura del tiempo de atravesar las islas
    std::vector<int> tiempoIslas(I);
    for (int &t : tiempoIslas) std::cin >> t;
    // Lectura del tiempo entre islas (creacion del grafo)
    GrafoDirigidoValorado<int> g(I);
    for (int i = 0; i < N; ++i) {
        int n1, n2, n3; std::cin >> n1 >> n2 >> n3;
        AristaDirigida<int> e(n1-1,n2-1,n3); 
        g.ponArista(e);
    }
    // Lectura de la posicion de las llaves
    std::vector<bool> llaves(I, false);
    for (int l = 0; l < L; ++l) {int aux; std::cin >> aux; llaves[aux-1] = true;}
    

	bool llaveIda = false;  // encuentro el camino mas corto de ida y de vuelta (grafo inverso)
	bool llaveVuelta = false;
	PerseoLLaves ida(g, Perseo, tiempoIslas, llaves, llaveIda);
	PerseoLLaves vuelta(g.inverso(), Perseo, tiempoIslas, llaves, llaveVuelta);
    
	int distanciaIda = ida.getDists()[Puerta];       // si no se ha encontrado llave a la ida o no se ha podido llegar a algun destino, el rescate es imposible
	int distanciaVuelta = vuelta.getDists()[Puerta]; // si alguna de las distancias no ha sido modificada significa que no se puede llegar al destino

	if (!llaveIda || distanciaIda == numeric_limits<int>::max() || distanciaVuelta == numeric_limits<int>::max())cout << "Rescate imposible" << endl;
	else cout << distanciaIda << " " << distanciaVuelta << " " << distanciaIda + distanciaVuelta << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
    #ifndef DOMJUDGE
     std::ifstream in("casos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
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
