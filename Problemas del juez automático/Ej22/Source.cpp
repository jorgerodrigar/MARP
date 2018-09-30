//Jorge Rodríguez García
#include "PriorityQueue.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct InfoPaciente {
	string nombre;
	int gravedad;
	int posicion;   //posicion en la que entro el paciente
};

struct ComparadorInfo {   //si ambas gravedades son iguales sera menor el que menor posicion tenga
	bool operator()(const InfoPaciente& _Left, const InfoPaciente& _Right) const {
		if (_Left.gravedad == _Right.gravedad)return _Left.posicion < _Right.posicion;
		else return _Left.gravedad > _Right.gravedad;
	}
};

int main() {
	int N, prioridad;
	string nombre;
	char evento;
	cin >> N;

	while (N != 0) {
		PriorityQueue<InfoPaciente, ComparadorInfo> priCola;
		vector <InfoPaciente> info;
		for (int i = 0; i < N; i++) {
			cin >> evento;
			if (evento == 'I') {
				cin >> nombre;
				cin >> prioridad;
				InfoPaciente info = { nombre, prioridad, i };
				priCola.push(info);
			}
			else if (evento == 'A') {
				info.push_back(priCola.top());
				priCola.pop();
			}
		}
		for (int i = 0; i < info.size(); i++)cout << info[i].nombre << endl;
		cout << "----" << endl;
		cin >> N;
	}

	return 0;
}