//Jorge Rodriguez Garcia
#include "Grafo.h"

using namespace std;

void amigosRecursivo(const Grafo & grafo, const int& vertice, vector<bool>& marcados, int& tam) {
	marcados[vertice] = true;             // marcamos como visitado el vertice recibido
	tam++;                                // aumentamos el tamaño de vertices conexos que tiene
	for (int i : grafo.ady(vertice))      // y recorremos sus adyacentes en busca de mas-> O(ady), siendo ady el numero de adyacentes
		if (!marcados[i])                 // en caso de no haber sido visitado haremos lo mismo con cada vertice adyacente
			amigosRecursivo(grafo, i, marcados, tam);
}

// escribe por pantalla el grupo mas grande de vertices conexos que haya en el grafo
void amigos(const Grafo& grafo) {
	vector<bool> marcados;                 // para cada vertice del grafo, indica si ya ha sido visitado o no
	marcados.resize(grafo.V());
	int maximo = 0;

	for (int i = 0; i < grafo.V(); i++) {  // para cada vertice del grafo-> O(V), siendo V el numero de vertices
		if (!marcados[i]) {                // si no ha sido visitado ya
			int tam = 0;                   // calcularemos el numero de grafos conexos que tiene recursivamente
			amigosRecursivo(grafo, i, marcados, tam);
			if (tam > maximo)maximo = tam; // si supera al maximo actual, se convertira en el nuevo maximo
		}
	}
	cout << maximo << endl;
}

bool resuelveCaso() {
	int numCasos, numPersonas, numParejas;
	cin >> numCasos;
	if (!cin)return false;

	for (int i = 0; i < numCasos; i++) {
		cin >> numPersonas >> numParejas;
		Grafo grafo(numPersonas);

		for (int j = 0; j < numParejas; j++) {
			int a, b;
			cin >> a >> b;
			grafo.ponArista(a - 1, b - 1);
		}

		amigos(grafo);
	}

	return true;
}

int main() {
	while (resuelveCaso());

	return 0;
}