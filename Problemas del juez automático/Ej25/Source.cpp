// Jorge Rodriguez Garcia
#include "PriorityQueue.h"
#include <cmath>

using namespace std;

struct InfoMusico {
	float numMusicos;
	float partituras;
};

struct ComparadorInfos {
	bool operator()(const InfoMusico& _Left, const InfoMusico& _Right) const {
		return ceil(_Left.numMusicos / _Left.partituras) > ceil(_Right.numMusicos / _Right.partituras);
	}
};

// va repartiendo partituras entre los que tienen mas prioridad de ello
// el ultimo que se quede sin repartir sera la solucion->O(p*log n), siendo p el numero de partituras y n el de instrumentos
void Solucion(PriorityQueue<InfoMusico, ComparadorInfos>& priCola, const int& partituras) {
	for (int i = 0; i < partituras; i++) {  //O(p)
		InfoMusico nuevaInfo;
		priCola.pop(nuevaInfo);             //O(log n)
		nuevaInfo.partituras++;
		priCola.push(nuevaInfo);            //O(log n)
	}
	cout << ceil(priCola.top().numMusicos/ priCola.top().partituras) << endl;
}

bool resuelveCaso() {
	int partituras, instrumentos, musicos;

	cin >> partituras;
	cin >> instrumentos;
	if (!cin)return false;

	PriorityQueue<InfoMusico, ComparadorInfos> priCola;

	//al meter en la cola ya repartimos una partitura a cada uno
	for (int i = 0; i < instrumentos; i++) {
		cin >> musicos;
		InfoMusico info = { musicos, 1 };
		priCola.push(info);
	}
	Solucion(priCola, partituras-instrumentos); //repartimos las que quedan

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}