//Jorge Rodríguez García
#include "iostream"
#include "bintree_eda.h"
using namespace std;

template<typename T>  //dado un arbol de tipo T indica si esta equilibrado o no y devuelve su altura
int EstaEquilibradoRecursivo(const bintree<T>& tree, bool& equilibrado) {
	if (tree.empty()) return 0;  //si se llega a una hoja vacia su altura sera 0
	else {  //si no, hallamos la altura de sus hijos recursivamente
		int alturaIzq = EstaEquilibradoRecursivo(tree.left(), equilibrado);
		int alturaDer = EstaEquilibradoRecursivo(tree.right(), equilibrado);
		if (abs(alturaIzq - alturaDer) > 1)equilibrado = false;  //condicion de arbol equilibrado
		return max(alturaIzq, alturaDer) + 1;  //la altura de esa hoja sera la maxima entre sus hijos + 1
	}
}

template<typename T>  //dado un arbol de tipo T indica si esta equilibrado o no
bool EstaEquilibrado(const bintree<T>& tree) {
	bool equilibrado = true;
	EstaEquilibradoRecursivo(tree, equilibrado);
	return equilibrado;
}

int main() {
	int numTrees;

	cin >> numTrees;  //numero de arboles por comprobar
	
	for (int i = 0; i < numTrees; i++) {
		bintree<char> tree = leerArbol('.');  //'.' valor nulo	
		if (EstaEquilibrado(tree))cout << endl << "SI" << endl;
		else cout << endl << "NO" << endl;
	}
	return 0;
}