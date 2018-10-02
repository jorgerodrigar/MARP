//Jorge Rodríguez García
#include "PriorityQueue.h"
#include<iostream>

using namespace std;


void recoloca(PriorityQueue<int>& colaMin, PriorityQueue<int, greater<int>>& colaMax);

// metodo que ayuda a hallar la mediana segun el ejercicio 24 en O(log n)
// apoyandose de dos colas de prioridad que dividen los datos en dos partes
void mediana(PriorityQueue<int>& colaMin, PriorityQueue<int, greater<int>>& colaMax, vector<int>& v, const int& dato) {
	if (colaMax.empty())colaMax.push(dato);              // por defecto metemos el dato en la cola de maximos (si ambas colas estan vacias)
	else if (dato < colaMax.top())colaMax.push(dato);    // si no, todos los datos menores que el top de la cola de maximos iran a esta
	else colaMin.push(dato);                             // mientras que los datos mayores iran a la de minimos. Este paso funcionaria tambien a la inversa

	recoloca(colaMin, colaMax);                          // recolocamos ambas colas para que nunca haya una diferencia de mas de 1 en su num de nodos. O(log n)

	if (colaMax.size() > colaMin.size())v.push_back(colaMax.top() * 2);         // si la colaMax es mayor, los datos son impares y su top sera justo la mitad
	else if (colaMax.size() < colaMin.size())v.push_back(colaMin.top() * 2);    // si la colaMin es mayor, los datos son impares y su top sera justo la mitad
	else v.push_back(colaMax.top() + colaMin.top());                            // si son iguales, los datos son pares y sus dos tops seran la mitad
}

void recoloca(PriorityQueue<int>& colaMin, PriorityQueue<int, greater<int>>& colaMax) {
	int recoloca;
	if (colaMax.size() - colaMin.size() > 1) {
		colaMax.pop(recoloca);
		colaMin.push(recoloca);
	}
	else if (colaMin.size() - colaMax.size() > 1) {
		colaMin.pop(recoloca);
		colaMax.push(recoloca);
	}
}

int main() {
	int n, dato;
	cin >> n;

	while (n != 0) {
		PriorityQueue<int> colaMin;                   // colaMin tendra la mitad correspondiente a los mayores datos (segunda mitad)
		PriorityQueue<int, greater<int>> colaMax;     // colaMax tendra la mitad correspondiente a los menores datos (primera mitad)
		vector<int> v;
		
		for (int i = 0; i < n; i++) {                 // todo el conjunto en O(n*log n), siendo n el numero de nodos a insertar
			cin >> dato;
			mediana(colaMin, colaMax, v, dato);       // O(log n)
		}

		for (int i = 0; i < v.size(); i++)cout << v[i] << " ";
		cout << endl;
		cin >> n;
	}

	return 0;
}