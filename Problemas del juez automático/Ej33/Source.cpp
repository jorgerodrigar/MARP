// Jorge Rodriguez Garcia
#include <string>
#include <vector>
#include <iostream>

using namespace std;

using Mapa = vector<string>;

class Ovejas {
private:
	int F, C;                      // dimensiones que tendra la entrada
	vector<vector<bool>> marked;   // casillas ya visualizadas
	int numBlancas;                // numero de ovejas blancas
	bool esBlanca;                 // indica si una obeja es blanca o no
	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1} };

	bool correcto(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	void dfs(Mapa const& M, int i, int j) {
		marked[i][j] = true;                           // marcamos como visitada
		for (auto d : dirs) {                          // para cada una de sus casillas adyacentes
			int ni = i + d.first, nj = j + d.second;   // si esta dentro del marco, es blanca y no ha sido visualizada ya
			if (correcto(ni, nj) && M[ni][nj] == '.' && !marked[ni][nj]) 
			{   
				// si esta al lado del borde ya no puede formar parte de una oveja (no puede tener negras alrededor)
				if (ni == 1 || ni == F - 1 || nj == 1 || nj == C - 1)esBlanca = false; 
				dfs(M, ni, nj); // y seguimos mirando su componente conexa
			}
		}
	}

public:
	Ovejas(Mapa const& M) : F(M.size()), C(M[0].size()), marked(F, vector<bool>(C, false)), numBlancas(0), esBlanca(true) 
	{
		for (int i = 2; i < F - 2; i++) {              // miramos todo el mapa saltandonos el marco y la posicion de al lado
			for (int j = 2; j < C - 2; j++) {
				if (M[i][j] == '.' && !marked[i][j]) { // si encontramos un punto blanco no marcado hallamos su componente conexa
					dfs(M, i, j);
					if(esBlanca)numBlancas++;          // si se nos indica que esta componente conexa es una oveja blanca la añadimos a la cuenta
					esBlanca = true;                   // reiniciamos el flag
				}
			}
		}
	}

	int numero() const { return numBlancas; }
};

bool resuelveCaso() {
	int ancho, alto;
	cin >> ancho >> alto;
	if (!cin)return false;

	if (ancho == 0 || alto == 0)return false; // tablero no valido

	Mapa mapa(alto);

	for (string & linea : mapa) cin >> linea;

	Ovejas manchas(mapa);
	cout << manchas.numero() << endl;

	return true;
}

int main() {
	while (resuelveCaso());

	return 0;
}