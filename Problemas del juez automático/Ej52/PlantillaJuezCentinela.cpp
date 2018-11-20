// Jorge Rodriguez Garcia
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

using namespace std;

// función que resuelve el problema
void resolver(priority_queue<int, vector<int>, less<int>>& rivales, priority_queue<int, vector<int>, greater<int>>& broncos) {
	int maxExito = 0;

	while (!rivales.empty()) {
		if (broncos.top() > rivales.top())maxExito += abs(rivales.top() - broncos.top());
		rivales.pop(); broncos.pop();
	}
    
	cout << maxExito << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;
	cin >> N;
    
	if (N == 0)
		return false;

	priority_queue<int, vector<int>, less<int>> rivales;
	priority_queue<int, vector<int>, greater<int>> broncos;

	for (int i = 0; i < N; i++) {
		int puntos;
		cin >> puntos;
		rivales.push(puntos);
	}

	for (int i = 0; i < N; i++) {
		int puntos;
		cin >> puntos;
		broncos.push(puntos);
	}
    
	resolver(rivales, broncos);
    
    // escribir sol
    
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
