//Jorge Rodriguez Garcia
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

//indica si hay conflictos entre tareas en O(T*log n), siendo T el Tiempo recibido por el usuario y n el numero de intervalos
void HayConflictos(PriorityQueue<Tarea, ComparadorTareas>& priCola, int tiempo, const int& T, bool& conflicto) {
	if (priCola.empty())return;                                       // si la cola esta vacia paro
	if (conflicto)return;                                             // si hay conflicto paro

	Tarea t1;
	priCola.pop(t1);
	if (t1.inicio >= T)return;                                        // si el intervalo actual se pasa de T paro
	if (tiempo > t1.inicio) conflicto = true;                         // si el intervalo actual se superpone al anterior hay conflicto
	                                                                  // guardo el intervalo actual otra vez en caso de ser periodico
	if (t1.periodo != 0)priCola.push({ t1.inicio + t1.periodo, t1.fin + t1.periodo, t1.periodo });

	if(!conflicto)HayConflictos(priCola, t1.fin, T, conflicto);       //actualizo el tiempo para el siguiente intervalo
}

bool resuelveCaso() {
	int tareasUnicas, tareasPeriodicas, tiempoConflicto;
	PriorityQueue<Tarea, ComparadorTareas> priCola;

	cin >> tareasUnicas;
	cin >> tareasPeriodicas;
	cin >> tiempoConflicto;

	if (!std::cin) // fin de la entrada
		return false;

	// introduzco las tareas unicas
	for (int i = 0; i < tareasUnicas; i++) {
		Tarea tareaUnica;
		cin >> tareaUnica.inicio;
		cin >> tareaUnica.fin;
		tareaUnica.periodo = 0;
		priCola.push(tareaUnica);
	}

	// introduzco las tareas periodicas
	for (int i = 0; i < tareasPeriodicas; i++) {
		Tarea tareaPeriodica;
		cin >> tareaPeriodica.inicio;
		cin >> tareaPeriodica.fin;
		cin >> tareaPeriodica.periodo;
		priCola.push(tareaPeriodica);
	}

	bool conflicto = false;
	Tarea t1;                // saco el primer intervalo para usar su tiempo de finalizacion en la llamada
	priCola.pop(t1);         // lo guardo otra vez en caso de ser periodico
	if (t1.periodo != 0)priCola.push({ t1.inicio + t1.periodo, t1.fin + t1.periodo, t1.periodo });

	HayConflictos(priCola, t1.fin, tiempoConflicto, conflicto);
	if (conflicto) cout << "SI" << endl;
	else cout << "NO" << endl;
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}