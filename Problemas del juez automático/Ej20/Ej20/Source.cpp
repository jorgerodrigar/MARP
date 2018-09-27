#include "PriorityQueue.h"
#include <iostream>

using namespace std;

void esfuerzoMinimo(PriorityQueue<long long int> priCola) {
	long long int num1 = 0, num2 = 0, suma = 0, esfuerzo = 0;
	while (priCola.size() != 1) {
		priCola.pop(num1);
		priCola.pop(num2);
		suma = num1 + num2;
		priCola.push(suma);
		esfuerzo += suma;
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
			priCola.push(num);
		}
		esfuerzoMinimo(priCola);
		cin >> N;
	}

	return 0;
}