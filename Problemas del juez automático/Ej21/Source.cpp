//Jorge Rodríguez García
#include <iostream>
#include "PriorityQueue.h"

using namespace std;

//  recoge la informacion de los usuarios registrados
struct InfoUsuario {
	int id;
	int periodo;    //se usa para actualizar la prioridad cada periodo
	int prioridad;
};

//  redefino un comparador que compare la informacion de los usuarios segun las especs. del problema
//  en caso de tener misma prioridad, se comparan identificadores
struct ComparadorInfo {
	bool operator()(const InfoUsuario& _Left, const InfoUsuario& _Right) const {
		if (_Left.prioridad == _Right.prioridad) return _Left.id < _Right.id;
		else return _Left.prioridad < _Right.prioridad;
	}
};

//  calcula quienes seran los k proximos usuarios a los que se les enviara informacion teniendo en cuenta su prioridad
//  y periodo -> en O(k*log n), siendo k el numero de usuarios a comprobar y n el numero de usuarios de la cola
void kPrimerosEnvios(PriorityQueue<InfoUsuario, ComparadorInfo>& priCola, int k) {
	InfoUsuario infoUser;
	for (int i = 0; i < k; i++) {                 //  O(k), siendo k el numero de usuarios a comprobar
		priCola.pop(infoUser);                    //  O(log n), siendo n el numero de usuarios de la cola
		cout << infoUser.id << endl;
		infoUser.prioridad += infoUser.periodo;
		priCola.push(infoUser);                   //  O(log n)
	}
	cout << "----" << endl;
}

int main() {
	int N, idUsuario, perUsuario, prioridad, k;
	cin >> N;

	while (N != 0) {
		PriorityQueue<InfoUsuario, ComparadorInfo> priCola;
		for (int i = 0; i < N; i++) {
			cin >> idUsuario;
			cin >> perUsuario;
			prioridad = perUsuario;
			InfoUsuario info = { idUsuario, perUsuario, prioridad };
			priCola.push(info);
		}
		cin >> k;
		kPrimerosEnvios(priCola, k);
		cin >> N;
	}

	return 0;
}