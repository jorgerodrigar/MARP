//Jorge Rodríguez García
#include "iostream"
#include "bintree_eda.h"
using namespace std;

struct Solution {
	bool AVL;
	int h;
	int max;
	int min;
};

template<typename T>  //dado un arbol de tipo T indica si es AVL o no y devuelve su altura
Solution EsAVLRecursivo(const bintree<T>& tree) {
	if (tree.empty()) return { true, 0, -1, 5000 };   //si esta vacio, es AVL y su h, min y max son 0
	else if (!tree.left().empty() && tree.right().empty()) {    //si su hijo izquierdo no esta vacio y su hijo derecho si
		Solution solIz = EsAVLRecursivo(tree.left());           //recursion por la izquierda
		return{ solIz.AVL && solIz.h <= 1 && solIz.max < tree.root(),  //devolvemos si el izq es AVL y esta equilibrado y es de busqueda
			solIz.h + 1, max(solIz.max, tree.root()), min(solIz.min, tree.root()) };//su altura mas 1, su maximo y su minimo
	}
	else if (tree.left().empty() && !tree.right().empty()) {    //si su hijo derecho no esta vacio y su hijo izquierdo si
		Solution solDr = EsAVLRecursivo(tree.right());           //recursion por la derecha
		return{ solDr.AVL && solDr.h <= 1 && solDr.min > tree.root(),  //devolvemos si el dr es AVL y esta equilibrado y es de busqueda
			solDr.h + 1, max(solDr.max, tree.root()), min(solDr.min, tree.root()) };//su altura mas 1, su maximo y su minimo
	}
	else {
		Solution solIz = EsAVLRecursivo(tree.left());           //recursion por la izquierda
		Solution solDr = EsAVLRecursivo(tree.right());           //recursion por la derecha
		return{ solIz.AVL && solDr.AVL && abs(solDr.h - solIz.h) <= 1 && 
			solIz.max < tree.root() && (solDr.min > tree.root()),     //devolvemos si iz y dr son AVL y estan equilibrados y son de busqueda
			max(solIz.h, solDr.h) + 1, max(solIz.max, tree.root()), min(solDr.min, tree.root()) };//su altura mas 1, su maximo y su minimo
	}
}

template<typename T>  //dado un arbol de tipo T indica si es AVL o no
bool EsAVL(const bintree<T>& tree) {
	return EsAVLRecursivo(tree).AVL;
}

int main() {
	int numTrees;

	cin >> numTrees;  //numero de arboles por comprobar

	for (int i = 0; i < numTrees; i++) {
		bintree<int> tree = leerArbol(-1);  //-1 valor nulo	
		if (EsAVL(tree))cout << "SI" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}