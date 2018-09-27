#include "IndexPQ.h"
#include <iostream>
#include <string>

using namespace std;

struct InfoPaciente {
	string nombre;
	int gravedad;
	int ordenLlegada;
};

struct ComparadorInfo {
	bool operator()(const InfoPaciente& _Left, const InfoPaciente& _Right) const {
		if (_Left.gravedad == _Right.gravedad)return _Left.ordenLlegada < _Right.ordenLlegada;
		else return _Left.gravedad > _Right.gravedad;
	}
};

int main() {
	int N, prioridad;
	string nombre;
	char evento;
	cin >> N;

	while (N != 0) {
		IndexPQ<InfoPaciente, ComparadorInfo> priCola(200000);
		for (int i = 0; i < N; i++) {
			cin >> evento;
			if (evento == 'I') {
				cin >> nombre;
				cin >> prioridad;
				InfoPaciente info = { nombre, prioridad, i };
				priCola.push(i, info);
			}
			else if (evento == 'A') {
				cout << priCola.top().prioridad.nombre << endl;
				priCola.pop();
			}
		}
		cout << "----" << endl;
		cin >> N;
	}

	return 0;
}