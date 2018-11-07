// Nombre del alumno .....
// Usuario del Juez ......

#include <iostream>
#include <iomanip>
#include <fstream>
#include "ConjuntosDisjuntos.h"
#include <vector>
#include <string>

using Foto = std::vector<std::string>;

using Dirs = std::vector<std::pair<int, int>>;

using Marked = std::vector<std::vector<bool>>;

bool esCorrecta(int x, int y, int F, int C) {
	return (x >= 0 && x < F && y >= 0 && y < C);
}

void dfs(const Foto& foto, ConjuntosDisjuntos& disjunto, const Dirs& dirs, Marked& marked, const int& F, const int& C, int i, int j) {
	marked[i][j] = true;

	for (int w = 0; w < dirs.size(); w++) {
		int ni, nj;
		ni = i + dirs[w].first;
		nj = j + dirs[w].second;
		if (esCorrecta(ni, nj, F, C) && foto[ni][nj] == '#' && !marked[ni][nj]) {
			disjunto.unir(i*C + j, ni*C + nj);
			dfs(foto, disjunto, dirs, marked, F, C, ni, nj);
		}
	}
}

// función que resuelve el problema
int resolver(const Foto& foto, ConjuntosDisjuntos& disjunto, const Dirs& dirs) {
	const int F = foto.size();
	const int C = foto[0].size();
	Marked marked(F, std::vector<bool>(C, false));
	int tamMax = 0;

	for (int i = 0; i < F; i++) {
		marked[i].resize(C);
		for (int j = 0; j < C; j++) {
			if (foto[i][j] == '#' && !marked[i][j]) {
				dfs(foto, disjunto, dirs, marked, F, C, i, j);
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

	for (int i = 0; i < F; i++) {
		foto[i].resize(C);
		for (int j = 0; j < C; j++) {
			char c;
			std::cin.get(c);
			if (c == '\n') std::cin.get(c);
			foto[i][j] = c;
		}
	}

	int tamMax = resolver(foto, disjunto, dirs);
	std::vector<int>maxTams;
	maxTams.push_back(tamMax);

	std::cin >> N;

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
				tam = disjunto.tam(x*C + y);
			}
		}
		if (tam > tamMax)tamMax = tam;
		maxTams.push_back(tamMax);
	}

	for (int i = 0; i < maxTams.size(); i++)std::cout << maxTams[i] << " ";
	std::cout << std::endl;
    
    return true;   
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    /*#ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif */
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     /*#ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif*/
    
    return 0;
}