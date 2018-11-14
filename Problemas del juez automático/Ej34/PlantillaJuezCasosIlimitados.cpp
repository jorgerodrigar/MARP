// Jorge Rodríguez García
// VJ24

#include <iostream>
#include <iomanip>
#include <fstream>
#include "ConjuntosDisjuntos.h"
#include <vector>
#include <string>

using Foto = std::vector<std::string>;

using Dirs = std::vector<std::pair<int, int>>;

bool esCorrecta(int x, int y, int F, int C) {
	return (x >= 0 && x < F && y >= 0 && y < C);
}

// recorro la foto uniendo con conjuntos disjuntos y hallo el tamaño de la maxima componente resultante
int resolver(const Foto& foto, ConjuntosDisjuntos& disjunto, const Dirs& dirs) {
	const int F = foto.size();
	const int C = foto[0].size();
	int tamMax = 0;

	for (int i = 0; i < F; i++) {
		for (int j = 0; j < C; j++) {
			if (foto[i][j] == '#') {
				for (int w = 0; w < dirs.size(); w++) {
					int ni, nj;
					ni = i + dirs[w].first;
					nj = j + dirs[w].second;
					if (esCorrecta(ni, nj, F, C) && foto[ni][nj] == '#')
						disjunto.unir(i*C + j, ni*C + nj);
				}
				if (disjunto.tam(i*C + j) > tamMax)tamMax = disjunto.tam(i*C + j);
			}
		}
	}

	return tamMax;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int F, C, N;
	std::cin >> F >> C;
    
    if (! std::cin)
        return false;

	Foto foto(F);
	ConjuntosDisjuntos disjunto(F*C);
	Dirs dirs = { {0, 1}, {0, -1} , {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

	//guardo la info en la foto
	for (int i = 0; i < F; i++) {
		foto[i].resize(C);
		for (int j = 0; j < C; j++) {
			char c;
			std::cin.get(c);
			if (c == '\n') std::cin.get(c);
			foto[i][j] = c;
		}
	}

	// hallo el tamaño del mayor de sus componentes
	int tamMax = resolver(foto, disjunto, dirs);
	std::vector<int>maxTams;
	maxTams.push_back(tamMax);  // y lo guardo

	std::cin >> N;

	// para cada coord de nuevo petroleo lo uno a los demas conjuntos adyacentes
	for (int i = 0; i < N; i++) {
		int x, y;
		std::cin >> x >> y;
		x--; y--;
		foto[x][y] = '#';
		int tam = 0;

		for (int w = 0; w < dirs.size(); w++) {
			int ni, nj;
			ni = x + dirs[w].first;
			nj = y + dirs[w].second;
			if (esCorrecta(ni, nj, F, C) && foto[ni][nj] == '#') {
				disjunto.unir(x*C + y, ni*C + nj);
			}
		}

		tam = disjunto.tam(x*C + y);
		if (tam > tamMax)tamMax = tam;  // si su tamaño es mayor que el actual lo guardo
		maxTams.push_back(tamMax);      // si no, guardo el anterior, que sigue siendo el mayor
	}

	for (int i = 0; i < maxTams.size(); i++)std::cout << maxTams[i] << " ";
	std::cout << std::endl;
    
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