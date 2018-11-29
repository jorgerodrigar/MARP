// Jorge Rodriguez García
// Laboratorio 4 puesto 2

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include <queue>
using namespace std;

// resuelvo el problema utilizando un recorrido en altura. Para mi, el grafo sera como
// un bipartito en el que hay dos tipos de amigos (A y B) que cumplen las propiedades del
// problema, puesto que cada amigo A estara rodeado de enemigos B y viceversa
// O(V)*O(E+V)
int resuelve(const Grafo& grafo) {
	vector<bool>marked;
	marked.resize(grafo.V());
	vector<int>distTo;
	distTo.resize(grafo.V());
	queue<int> c;
	int numAmigosA = 0, numAmigosB = 0;   // numero de amigos de los dos tipos
	int amigosTotales = 0;                // amigos maximos que salen de cada componente conexa

	for (int i = 0; i < grafo.V(); i++) { // O(V), siendo V el numero de personas
		if (!marked[i]) {                 // utilizo recorrido en anchura apoyandome en una cola
			marked[i] = true;             // al encontrar una nueva componente conexa la recorrere de esta forma
			distTo[i] = 0;
			c.push(i);
		}

		while (!c.empty()) {                        // recorrido en anchura del grafo->O(E+V), siendo E num aristas
			int a = c.front(); c.pop();             // y V num de vertices (o personas en este caso)
			for (int w : grafo.ady(a)) {
				if (!marked[w]) {
					distTo[w] = distTo[a] + 1;      // distancia del vertice w al vertice inicial
					marked[w] = true;
					c.push(w);
					if (distTo[w] % 2)numAmigosA++; // si la distancia de w al inicial es par, formara parte de un grupo
					else numAmigosB++;              // si la distancia es par, formara parte del otro
				}
			}
		}
		amigosTotales += max(numAmigosA, numAmigosB); // añado al total de invitados el maximo obetenido de la ultima
		numAmigosA = 0;   // componente conexa
		numAmigosB = 0;   // restablezco valores para nuevas componentes conexas
	}
	return amigosTotales; // numero de invitados maximo
}

// Lectura de datos
bool resuelveCaso () {
    int numPersonas, numPeleas;
    std::cin >> numPersonas;
    if (!std::cin) return false;
    std::cin >> numPeleas;

	Grafo grafo(numPersonas);  // utilizo un grafo para representar los amigos y enemigos
	for (int i = 0; i < numPeleas; i++) {
		int a, b;
		cin >> a >> b;
		grafo.ponArista(a - 1, b - 1); // pongo una arista por cada par de enemigos
	}

	cout << resuelve(grafo) << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    
    while (resuelveCaso())
        ;
    
    // Para restablecer entrada
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}

