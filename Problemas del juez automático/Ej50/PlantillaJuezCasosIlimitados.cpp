// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

/*Demostración
Dadas la solución voraz y la solución óptima con las posiciones donde se deben poner los parches (p1, p2, ..., pi):
Si en la voraz hay una posición distinta a la óptima (pi != pj), sabemos que pi no puede ser menor que pj, ya que en
ese caso la solución óptima no taparía el agujero que tapa pi, y no sería óptima.
Por tanto, podemos decir que pi > pj y que entre ellos no habria agujeros, ya que la solución voraz los habría tapado.
En este caso, podríamos intercambiar pi y pj para que la voraz fuese igual que la óptima.
*/

// función que resuelve el problema
void resolver(const vector<int>& posiciones, const int& L) {
	int minParches = 0, tapados = 0;

	for (int i = 0; i < posiciones.size(); i++) {
		if (tapados < posiciones[i]) {
			tapados = posiciones[i] + L;
			minParches++;
		}
	}

	cout << minParches << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N, L;
	cin >> N >> L;
    
    if (! std::cin)
        return false;
    
	vector<int>posiciones;
	for (int i = 0; i < N; i++) {
		int pos;
		cin >> pos;
		posiciones.push_back(pos);
	}

    resolver(posiciones, L);    
    
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