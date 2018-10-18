// Jorge Rodriguez Garcia
#include "Grafo.h"
#include <queue>

using namespace std;

bool bipartito(const Grafo& grafo) {
	bool bipartito = true;
	queue<int> q;
	vector<int>distTo;
	vector<bool> marked;
	marked.resize(grafo.V());
	distTo.resize(grafo.V());
	distTo[0] = 0; 
	q.push(0);
	marked[0] = true;
	int i = 0;
	 // voy maracndo los niveles de cada vertice
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int w : grafo.ady(v)) {
			if (!marked[w]) {
				distTo[w] = distTo[v] + 1;
				marked[w] = true;
				q.push(w);
			}                // si algun adyacente esta al mismo nivel que el vertice, ya no es bipartito
			else if (distTo[w] == distTo[v])bipartito = false;
		}
		i++;                 // si se ha acabado la componente conexa pero aun quedan nodos por comprobar metemos el siguiente
		if (q.empty() && i < grafo.V()) q.push(i);
	}

	return bipartito;
}

bool resuelveCaso() {
	int V, A;
	cin >> V;
	if (!cin)return false;

	cin >> A;

	Grafo grafo(V);
	for (int i = 0; i < A; i++) {
		int a, b;
		cin >> a >> b;
		grafo.ponArista(a, b);
	}

	if (bipartito(grafo))cout << "SI" << endl;
	else cout << "NO" << endl;

	return true;
}

int main() {
	while (resuelveCaso());

	return 0;
}