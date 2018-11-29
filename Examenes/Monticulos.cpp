//*****************
// IMPORTANTE
//
// Jorge Rodriguez Garcia
// MARP02
//
//***************************************************

#include <iostream>
#include <fstream>
#include <queue>
#include "PriorityQueue.h"
using namespace std;

struct InfoHangar {
	float hueco;
	float ocupado;
};

struct ComparaHangares
{	
	bool operator()(const InfoHangar& _Left, const InfoHangar& _Right) const
	{	
		if (_Left.ocupado == 0 && _Right.ocupado == 0)return (_Left.hueco > _Right.hueco);
		else return (_Left.hueco/_Left.ocupado > _Right.hueco/_Right.ocupado);
	}
};

void resuelveCaso() {
	int H, N;
    cin >> H;

	while (H != 0) {
		bool posible = true;
		PriorityQueue<InfoHangar, ComparaHangares> hangares;

		// para cada hangar los ordeno en una cola de prioridad. Si el hangar esta vacio
		// tendrá prioridad el que mas tamaño tenga. Si no, tendrá prioridad el que mas espacio libre tenga
		// O(H*log h)
		for (int i = 0; i < H; i++) { // O(H), siendo H el numero de hangares totales
			InfoHangar info;
			cin >> info.hueco;
			info.ocupado = 0;         // inicialmente los hangares estan vacios
			hangares.push(info);      // O(log h), siendo h el numero de hangares ya introducidos
		}

		cin >> N;

		// para cada nave la introduzco en el hangar mas prioritario
		// O(N*log h)
		for (int i = 0; i < N; i++) {                       // O(N), siendo N el numero de naves a introducir
			int tam;
			cin >> tam;
			InfoHangar info;
			hangares.pop(info);                             // info sera el hangar mas prioritario. O(log h)
			info.ocupado += tam;                            // le incrementamos "ocupado"
			if (info.ocupado > info.hueco)posible = false;  // si esta mas ocupado que el hueco que tenia, ya no caben más
			else hangares.push(info);                       // si no, vuelvo a introducir el hangar. O(log h)
		}

		if (posible)
			cout << "SI\n";
		else
			cout << "NO\n";
		cin >> H;
	}
}

int main() {
    resuelveCaso();

    return 0;
}

/*
2
12 20
3
10 11 10
2
12 20
3
10 10 11
3
20 5 10
5
14 3 4 6 5
0
 */


