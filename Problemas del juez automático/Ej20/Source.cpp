//Jorge Rodríguez García
#include "PriorityQueue.h"
#include <iostream>

using namespace std;

//dada una cola de prioridad, calcula el esfuerzo minimo para sumar sus elementos -> O(n*log n), siendo n el numero de elementos
void esfuerzoMinimo(PriorityQueue<long long int> priCola) {
	long long int num1 = 0, num2 = 0, suma = 0, esfuerzo = 0;

	//mientras la cola sea de mas de un elemento -> O(n), siendo n el numero de elementos
	while (priCola.size() > 1) {
		priCola.pop(num1);       //extraemos sus dos primeros y los sumamos -> O(log n), siendo n el numero de elementos
		priCola.pop(num2);       //O(log n), siendo n el numero de elementos
		suma = num1 + num2;      //O(1)
		priCola.push(suma);      //pusheamos la suma, es decir, el esfuerzo de sumar esos dos numeros -> O(log n), siendo n el numero de elementos
		esfuerzo += suma;        //actualizamos el esfuerzo -> O(1)
	}
	cout << esfuerzo << endl;
}

int main() {
	long long int N, num;

	cin >> N;

	while (N != 0) {
		PriorityQueue<long long int> priCola;
		for (long i = 0; i < N; i++) {
			cin >> num;
			priCola.push(num);     //asi quedan ordenados de mayor a menor
		}
		esfuerzoMinimo(priCola);   //calculamos el esfuerzo minimo para sumar todos los valores
		cin >> N;
	}

	return 0;
}