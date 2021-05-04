

#include <iostream>
using namespace std;

template<class T>
class ascendente {
public:
	inline bool operator() (T a, T b) { return a > b; }
};

template<class T>
class descendente {
public:
	inline bool operator() (T a, T b) { return a < b; }
};

template<class T>
class Nodo {
public:
	T valor;
	Nodo<T>* next;
	Nodo(T x){
		valor = x; 
		next = nullptr; 
	}
};

template<class T, class O>
class Lista {
public:	
	Nodo<T>* head;
	O op;
	Lista() { head = NULL; };

	bool Buscar(T x, Nodo<T>**& p);
	bool Agregar(T x);
	bool Eliminar(T x);
	void Imprimir();
	~Lista() {
		Nodo<T>* t = head->next;
		while (!(t->next)) {
			Nodo<T>* p = head;
			head = t;
			delete[]p;
			t = t->next;
		}
		delete[]t;
	}
};

template<class T, class O>
bool Lista<T, O>::Buscar(T x, Nodo<T>**& p) {
	p = &head;
	if (!(*p))
		return 0;
	if (op(x, (*p)->valor))
		return 0;
	if ((*p)->valor == x)
		return 1;
	p = &((*p)->next);
	for (; op((**p).valor, x) && (*p) != head; p = &((*p)->next));
	return *p != head && (*p)->valor == x;
}

template<class T, class O>
bool Lista<T, O>::Agregar(T x) {
	Nodo<T>** p;
	if (Buscar(x, p))
		return 0;
	Nodo<T>* t = new Nodo<T>(x);
	if (!(*p)) {
		t->next = t;
		(*p) = t;
	}
	else if (*p) {
		t->next = *p;
		if (op(x, head->valor)) {
			*p = t;
			p = &((*p)->next->next);
			while (*p != t->next)
				p = &((*p)->next);
		}
		*p = t;
	}
	return 1;
}

template<class T, class O>
bool Lista<T, O>::Eliminar(T x) {
	Nodo<T>** p;
	if (!Buscar(x, p))
		return 0;
	if (*p == head) {
		if (*p == (*p)->next) {
			head = NULL;
			delete[] head;
			return 1;
		}
		*p = (*p)->next;
		while ((*p)->next != head)
			p = &((*p)->next);
		Nodo<T>* t = *p;
		*p = head;
		delete[]t;
	}
	else {
		Nodo<T>* t = *p;
		*p = t->next;
		delete[] t;
	}
	return 1;
}

template<class T, class O>
void Lista<T,O>::Imprimir() {
	if (head) {
		cout << head->valor << " ";
		for (Nodo<T>* i = head->next; i != head && head; i = i->next)
			cout << i->valor << " ";
	}
}

int main(){
	Lista <int, descendente<int>> listita;
	int opcion, opcion_2, opcion_3, opcion_4;
	do{
		system("cls");
		cout << "Lista Enlazada Simple (next y prev): " << endl;
		cout << "-----------" << endl << endl;
		cout << "\t1 .- Agregar" << endl;
		cout << "\t2 .- Eliminar" << endl;
		cout << "\t3 .- Mostrar" << endl;
		cout << "\t4 .- Salir" << endl; 
		cout << "Elige una opcion: \n";

		cin >> opcion;
		switch (opcion)
		{
		case 1:
			system("cls");
			cout << "Has elegido Agregar en la Lista.\n";
			cout << "Agrega el numero que desees: \n";
			cin >> opcion_2;
			listita.Agregar(opcion_2);
			break;

		case 2:
			system("cls");
			cout << "Has elegido Remover de la Lista.\n";
			cout << "Elimina el numero que desees: \n";
			cin >> opcion_3;
			listita.Eliminar(opcion_3);;
			break;

		case 3:
			system("cls");
			cout << "Has elegido Mostrar la Lista.\n"; 
			listita.Imprimir();
			cout << "\nPresiona 1 para volver a Menu....\n";
			cin >> opcion_4;
			break;
		}
	} while (opcion != 4);
	return 0;
}