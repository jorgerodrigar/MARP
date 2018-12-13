// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 100000000;

bool esPosible(const vector<pair<int, int>>& v, const int& L) {
	int n = v.size() - 1;
	vector<vector<bool>> matriz(n + 1, vector<bool>(L + 1, false));
	matriz[0][0] = true;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = true;
		for (int j = 1; j <= L; j++) {
			if (v[i].first > j)matriz[i][j] = matriz[i - 1][j];
			else matriz[i][j] = matriz[i - 1][j] || matriz[i - 1][j - v[i].first];
		}
	}

	return matriz[n][L];
}

int formasPosibles(const vector<pair<int, int>>& v, const int& L) {
	int n = v.size() - 1;
	vector<vector<int>> matriz(n + 1, vector<int>(L + 1, 0));
	matriz[0][0] = 1;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 1;
		for (int j = 1; j <= L; j++) {
			if (v[i].first > j)matriz[i][j] = matriz[i - 1][j];
			else matriz[i][j] = matriz[i - 1][j] + matriz[i - 1][j - v[i].first];
		}
	}

	return matriz[n][L];
}

int numeroMinimo(const vector<pair<int, int>>& v, const int& L) {
	int n = v.size() - 1;
	vector<vector<int>> matriz(n + 1, vector<int>(L + 1, 0));
	matriz[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= L; j++) {
			matriz[0][j] = INF;
			if (v[i].first > j)matriz[i][j] = matriz[i - 1][j];
			else matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - v[i].first] + 1);
		}
	}

	return matriz[n][L];
}

int costeMinimo(const vector<pair<int, int>>& v, const int& L) {
	int n = v.size() - 1;
	vector<vector<int>> matriz(n + 1, vector<int>(L + 1, 0));
	matriz[0][0] = 0;

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = 0;
		for (int j = 1; j <= L; j++) {
			matriz[0][j] = INF;
			if (v[i].first > j)matriz[i][j] = matriz[i - 1][j];
			else matriz[i][j] = min(matriz[i - 1][j], matriz[i - 1][j - v[i].first] + v[i].second);
		}
	}

	return matriz[n][L];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, L;
	cin >> N >> L;
    
    if (! std::cin)
        return false;
    
	vector<pair<int, int>> v;
	v.push_back({ 0, 0 });     // NO OLVIDAR!! luego empezamos a comprobar a partir de la posicion 1
	for (int i = 0; i < N; i++) {
		int longitud, coste;
		cin >> longitud >> coste;
		v.push_back({ longitud, coste });
	}

	bool posible = esPosible(v, L);
	if (posible)cout << "SI" << " " << formasPosibles(v, L) << " " << numeroMinimo(v, L) << " " << costeMinimo(v, L) << endl;
	else cout << "NO" << endl;
    
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