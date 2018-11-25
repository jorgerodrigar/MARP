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
void resolver(const vector<pair<int, int>>& horarios) {
	int maxVistas = 1;                                                 // como minimo vera una pelicula
	pair<int, int> peli = horarios[0];                                 // la que primero empieza sera nuestro primer candidato

	for (int i = 1; i < horarios.size(); i++) {
		if (peli.second + 10 <= horarios[i].first) {                   // si nuestro candidato no se superpone con la siguiente pelicula
			maxVistas++;                                               // (teniendo en cuenta lo que tarda entre pelicula y pelicula = 10)
			peli = horarios[i];                                        // la vemos, y nuestro candidato sera la siguiente pelicula
		}                                                              // si nuestro candidato se superpone y la siguiente pelicula acaba antes
		else if (peli.second > horarios[i].second)peli = horarios[i];  // nuestro nuevo candidato sera la siguiente pelicula
	}
    
	cout << maxVistas << endl;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int N;
	cin >> N;
    
    if (N==0)
        return false;

	vector<pair<int, int>> horarios;
	for (int i = 0; i < N; i++) {
		string hora;
		int duracion;
		cin >> hora >> duracion;
		int horaInicio = (((hora[0] - '0') * 10 + (hora[1] - '0')) * 60) + ((hora[3] - '0') * 10 + (hora[4] - '0'));
		int horaFin = horaInicio + duracion;
		horarios.push_back({ horaInicio, horaFin });
	}

	sort(horarios.begin(), horarios.end());  // ordenos los horarios por orden de inicio de las peliculas
    
	resolver(horarios);
    
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
