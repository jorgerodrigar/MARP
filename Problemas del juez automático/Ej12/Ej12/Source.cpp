//Jorge Rodríguez García y Gonzalo Sanz Lastra
#pragma once
#include "iostream"
#include "TreeMap_AVL.h"
#include <vector>

using namespace std;

//clase map extendida: igual que la clase map pero con un metodo extra que resuelve el problema
class mapExt : public map<int, int> {
public:
		map<int, int>::Link getRoot() { return raiz; }

		//este metodo resuelve el problema, devolviendo en v los elementos que aparecen en el rango [k1, k2] en el arbol
		void rango(const int& k1, const int& k2, vector<int>& v, const map<int, int>::Link& root) {
			if (root == nullptr)return;                                   //si la raiz es nula no hacemos nada
			else if (root->cv.clave > k2) rango(k1, k2, v, root->iz);     //si no, si la raiz es mayor que el extremo derecho del rango significa que este estara por la izq
			else if (root->cv.clave < k1) rango(k1, k2, v, root->dr);     //si la raiz es menor que el extremo izquierdo del rango significa que este estara por la der
			else {                                                        //si no, es que el rango esta repartido entre izq y der, y que la raiz esta en el
				rango(k1, k2, v, root->iz);                               //primero izq, raiz, der, para ir insertandolos en orden en v
				v.push_back(root->cv.clave);                              //insertamos en v la raiz
				rango(k1, k2, v, root->dr);
			}
		}
		virtual ~mapExt() {}
};

int main() {
	int numClaves, valor, k1, k2;

	cin >> numClaves;        //meter una clave = 0 supone el fin del programa
	while (numClaves != 0) {
		mapExt tree;
		for (int i = 0; i < numClaves; i++) {
			cin >> valor;    //creamos el arbol con las claves insertadas
			tree.insert(valor);
		}
		vector<int> v;
		cin >> k1;
		cin >> k2;
		tree.rango(k1, k2, v, tree.getRoot());  //obtenemos el vector del resultado

		//lo escribimos por pantalla
		for (int j = 0; j < v.size(); j++) {
			cout << v[j] << " ";
		}
		cout << endl;
		cin >> numClaves;
	}

	return 0;
}