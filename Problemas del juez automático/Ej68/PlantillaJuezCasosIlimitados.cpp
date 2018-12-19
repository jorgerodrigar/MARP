// Jorge Rodriguez Garcia
// VJ24

#include "Matriz.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// devuelve el numero minimo de monedas de los tipos del vector de monedas,
// teniendo en cuenta la cantidad de cada tipo, para pagar un precio P
int minMonedas(const vector<pair<int, int>>& monedas, const int& P) {
	int n = monedas.size() - 1;
	Matriz<int> tabla(n + 1, P + 1, INF);  // minMonedas para pagar P con 0 monedas->imposible
	tabla[0][0] = 0;                       // minMonedas para pagar 0

	for (int i = 1; i <= n; i++) {
		tabla[i][0] = 0;                   // minMonedas para pagar 0
		for (int j = 1; j <= P; j++) {
			int minimo = tabla[i - 1][j];  // equivale a k = 0
			for (int k = 1; k <= monedas[i].second && k*monedas[i].first <= j; k++) {
				minimo = min(minimo, tabla[i - 1][j - k * monedas[i].first] + k);
			}
			tabla[i][j] = minimo;
		}
	}
    
	return tabla[n][P];
}

// mismo metodo, pero mejorado en espacio
int minMonedasMejoraEspacio(const vector<pair<int, int>>& monedas, const int& P) {
	int n = monedas.size() - 1;
	vector<int> tabla(P + 1, INF);  // minMonedas para pagar P con 0 monedas->imposible
	tabla[0] = 0;                       // minMonedas para pagar 0

	for (int i = 1; i <= n; i++) {
		for (int j = P; j >= 1; j--) {
			int minimo = tabla[j];  // equivale a k = 0
			for (int k = 1; k <= monedas[i].second && k*monedas[i].first <= j; k++) {
				minimo = min(minimo, tabla[j - k * monedas[i].first] + k);
			}
			tabla[j] = minimo;
		}
	}

	return tabla[P];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, precio;
	cin >> N;

    if (! std::cin)
        return false;

	vector<pair<int, int>> monedas;
	monedas.push_back({ 0, 0 }); // NO OLVIDAR QUE EMPIEZA EN 1
	for (int i = 0; i < N; i++) {
		int valor;
		cin >> valor;
		monedas.push_back({ valor, 0 });
	}
	for (int i = 1; i <= N; i++) {
		int cantidad;
		cin >> cantidad;
		monedas[i].second = cantidad;
	}

	cin >> precio;

	int numMin = minMonedasMejoraEspacio(monedas, precio);
	if (numMin == INF)cout << "NO" << endl;
	else cout << "SI " << numMin << endl;
    
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}