#include "GrafoDirigido.h"
#include <queue>

using namespace std;

struct Par {
	int dist;
	bool escalera;
};

void ResuelveProblema(const GrafoDirigido& grafo, int K) {
	vector<bool> marked;
	marked.resize(grafo.V());
	vector<int>distTo;
	distTo.resize(grafo.V());
	queue<int> q;
	distTo[0] = 0;
	marked[0] = true;
	q.push(0);
	int tiradas = 0;
	while (!q.empty()) {
		int v = q.front(); q.pop();
		int tirada2 = 1;
		for (int w : grafo.ady(v)) {
			if (!marked[w]) {
				distTo[w] = distTo[v] + 1;
				if (distTo[w] > K*tirada2)tirada2++;
				if (w > v + 1)tirada2++;
				marked[w] = true;
				q.push(w);
			}
			tiradas += tirada2;
		}
	}
	cout << tiradas << endl;
}

int main() {
	int N, K, S, E;
	cin >> N >> K >> S >> E;

	while (N != 0 || K != 0 || S != 0 || E != 0) {
		GrafoDirigido grafo(N*N); 
		vector<Par>distTo;
		distTo.resize(grafo.V());
		int ini, fin, dist = 0;
		for (int i = 0; i < N*N - 1; i++) {
			distTo[i].dist = dist;
			distTo[i].escalera = false;
			dist++;
		}
		for (int i = 0; i < S; i++) {
			cin >> ini >> fin;
		}
		for (int i = 0; i < E; i++) {
			cin >> ini >> fin;
			distTo[ini - 1].escalera = true;
			distTo[fin].dist = distTo[ini - 1].dist;
		}
		ResuelveProblema(grafo, K);

		cin >> N >> K >> S >> E;
	}

	return 0;
}