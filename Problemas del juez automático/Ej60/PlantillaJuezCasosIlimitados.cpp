// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
void varillas(const vector<pair<int, int>>& v, const int& L) {
	int n = v.size() - 1;
	vector<vector<bool>> matriz(false);
	matriz.resize(n + 1);

	for (int i = 0; i <= n; i++)
		matriz[i].resize(L + 1);

	for (int i = 1; i <= n; i++) {
		matriz[i][0] = true;
		for (int j = 1; j <= L; j++) {
			if (v[i].first > L)matriz[i - 1][j];
			else matriz[i][j] = (matriz[i - 1][j] || (j - v[i].first >= 0 && matriz[i - 1][j - v[i].first]));
		}
	}

	cout << matriz[n][L] << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, L;
	cin >> N >> L;
    
    if (! std::cin)
        return false;
    
	vector<pair<int, int>> v;
	for (int i = 0; i < N; i++) {
		int longitud, coste;
		cin >> longitud >> coste;
		v.push_back({ longitud, coste });
	}

    varillas(v, L);
    
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