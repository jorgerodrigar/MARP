// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void cogeCandidato(int& minTrabajos, int&actual, pair<int, int>& candidato, pair<int, int>& trabajo) {
	minTrabajos++;
	actual = candidato.second;
	candidato = trabajo;
}

// función que resuelve el problema
void resolver(vector<pair<int, int>>& trabajos, const int& C, const int& F) {
	int minTrabajos = 0;
	int actual = C;                          // inicio actual
	bool imposible = false;
	pair<int, int> candidato = trabajos[0];  // candidato a considerar

	// si solo hay un trabajo y abarca todo el tiempo, la solucion sera coger ese
	if (trabajos.size() == 1) {              
		if (candidato.first <= C && candidato.second >= F)cout << 1 << endl;
		else cout << "Imposible" << endl;   
	}

	// si hay mas de uno
	else {
		int i = 1;
		if (candidato.first > C)imposible = true;                                   // si el primer candidato no abarca el comienzo, imposible

		while (i < trabajos.size() && actual < F && !imposible) {
			if (candidato.first <= actual) {                                        // si el candidato abarca el inicio actual
				if (trabajos[i].first <= actual) {                                  // y el siguiente trabajo tambien
					if (candidato.second > trabajos[i].second)                      // si nuestro candidato abarca mas tiempo que el siguiente trabajo lo cogemos
						cogeCandidato(minTrabajos, actual, candidato, trabajos[i]);
					else candidato = trabajos[i];                                   // si no, nuestro nuevo candidato a comprobar sera el siguiente trabajo
				}
				else cogeCandidato(minTrabajos, actual, candidato, trabajos[i]);    // si el siguiente trabajo no lo abarca, cogemos nuestro candidato
				i++;
			}
			else imposible = true;                                                  // si nuestro candidato no lo abarca, imposible
		}

		if (actual < F && candidato.first <= actual && candidato.second >= F) {
			minTrabajos++;
			actual = candidato.second;
		}

		if (imposible || actual < F)cout << "Imposible" << endl;
		else cout << minTrabajos << endl;
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int C, F, N;
	cin >> C >> F >> N;
    
    if (C==0 && F==0 && N==0)
        return false;

	vector<pair<int, int>> trabajos;
	for (int i = 0; i < N; i++) {
		int comienzo, final;
		cin >> comienzo >> final;
		trabajos.push_back({ comienzo, final });
	}

	sort(trabajos.begin(), trabajos.end());
    
	if (N==0)cout << "Imposible" << endl;
    else resolver(trabajos, C, F);
    
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
