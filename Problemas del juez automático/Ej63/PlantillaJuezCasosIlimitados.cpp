// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// función que resuelve el problema
void resolver(const string& p1, const string& p2) {
	vector<vector<int>> subsec;       // matriz de palabra1 x palabra2
	subsec.resize(p1.size() + 1);     // la fila y la columna 0 valdran 0 
	subsec[0].resize(p2.size() + 1);  // (no hay ninguna subsecuencia entre el elemento de una palabra y nada de la otra)
	subsec[0][0] = 0;

	for (int i = 1; i <= p1.size(); i++) {
		subsec[i].resize(p2.size() + 1);
		subsec[i][0] = 0;
		for (int j = 1; j <= p2.size(); j++) {
			subsec[0][j] = 0;

			// para cada posicion de la matriz
			if (p1[i - 1] == p2[j - 1]) // si el elemento i de p1 coincide con el elemento j de p2
				                        // hacemos lo que mas nos convenga->maximo entre añadirlo como nueva subsecuencia o no hacerlo
				subsec[i][j] = max(subsec[i - 1][j - 1] + 1, max(subsec[i - 1][j], subsec[i][j - 1]));
			else                        // si no coinciden, hacemos el maximo beneficio entre comprobar por i o por j
				subsec[i][j] = max(subsec[i - 1][j], subsec[i][j - 1]);
		}
	}
    
	cout << subsec[p1.size()][p2.size()] << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	string palabra1, palabra2;
	cin >> palabra1 >> palabra2;
    
    if (! std::cin)
        return false;
    
    resolver(palabra1, palabra2); 
    
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