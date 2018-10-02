#include "PriorityQueue.h"
#include <iostream>

using namespace std;

struct Tarea {
	int inicio;
	int fin;
	int periodo;
};

struct ComparadorTareas {
	bool operator()(const Tarea& _Left, const Tarea& _Right) const {
		return _Left.inicio < _Right.inicio;
	}
};

void HayConflictos(PriorityQueue<Tarea, ComparadorTareas>& priCola, const Tarea& tarea, const int& tiempo, bool& conflicto) {
	if (priCola.empty())return;
	if (conflicto)return;
	Tarea t1;
	priCola.pop(t1);
	if (tarea.inicio > tiempo || t1.inicio > tiempo)return;
	if (tarea.inicio <= t1.inicio && tarea.fin > t1.inicio) conflicto = true;
	if (t1.periodo != 0)priCola.push({ t1.inicio + t1.periodo, t1.fin + t1.periodo, t1.periodo });
	HayConflictos(priCola, t1, tiempo, conflicto);
}

bool resuelveCaso() {
	int tareasUnicas, tareasPeriodicas, tiempoConflicto;
	PriorityQueue<Tarea, ComparadorTareas> priCola;

	cin >> tareasUnicas;
	cin >> tareasPeriodicas;
	cin >> tiempoConflicto;

	for (int i = 0; i < tareasUnicas; i++) {
		Tarea tareaUnica;
		cin >> tareaUnica.inicio;
		cin >> tareaUnica.fin;
		tareaUnica.periodo = 0;
		priCola.push(tareaUnica);
	}
	for (int i = 0; i < tareasPeriodicas; i++) {
		Tarea tareaPeriodica;
		cin >> tareaPeriodica.inicio;
		cin >> tareaPeriodica.fin;
		cin >> tareaPeriodica.periodo;
		priCola.push(tareaPeriodica);
	}

	if (!std::cin) // fin de la entrada
		return false;

	bool conflicto = false;
	Tarea tarea;
	priCola.pop(tarea);
	if (tarea.periodo != 0)priCola.push({ tarea.inicio + tarea.periodo, tarea.fin + tarea.periodo, tarea.periodo });
	HayConflictos(priCola, tarea, tiempoConflicto, conflicto);
	if (conflicto) cout << "SI" << endl;
	else cout << "NO" << endl;
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}