
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
	Nodo<T>* prev;
	Nodo(T x) {
		valor = x;
		next = prev = 0;
	}
};

template<class T, class O>
class Lista {
public:
	Nodo<T>* head;
	Nodo<T>* tail;
	O op;
	Lista() { head = tail = NULL; }
	~Lista(){
		if (head != 0) {
			Nodo<T>* temp = head;
			while (temp) {
				Nodo<T>* next = temp->next;
				delete temp;
				temp = next;
			}
		}
	}
	bool Buscar(T x, Nodo<T>**& p_next, Nodo<T>**& p_prev);
	bool Agregar(T x);
	bool Eliminar(T x);
	void Imprimir_1();
	void Imprimir_2();
};

template<class T, class O>
bool Lista<T, O>::Buscar(T x, Nodo<T>**& p_next, Nodo<T>**& p_prev) {
	for (p_next = &head; (*p_next) && op((*p_next)->valor, x); p_next = &((*p_next)->next));
	for (p_prev = &tail; (*p_prev) && op(x, (*p_next)->valor); p_prev = &((*p_prev)->prev));
	return (*p_next) && (*p_next)->valor == x;
}

template<class T, class O>
bool Lista<T, O>::Agregar(T x) {
	Nodo<T>** p;
	Nodo<T>** q;
	if (Buscar(x, p, q)) { return 0; }
	Nodo<T>* temp = new Nodo<T>(x);
	temp->next = *p;
	temp->prev = *q;
	*p = temp;
	return 1;
}

template<class T, class O>
bool Lista<T, O>::Eliminar(T x) {
	Nodo<T>** p;
	Nodo<T>** q;
	if (!Buscar(x, p, q)) { return 0; }
	Nodo<T>* temp = *p;
	*p = temp->next;
	*q = temp->prev;
	delete temp;
	return 1;
}

template<class T, class O>
void Lista<T, O>::Imprimir_1() {
	Nodo<T>* temp = head;
	while (temp) {
		cout << temp->valor << ' ';
		temp = temp->next;
	}
}

template<class T, class O>
void Lista<T, O>::Imprimir_2() {
	Nodo<T>* temp = head;
	while (temp) {
		temp->prev;
		cout << temp->valor << ' ';
		temp=temp->prev;
	}
}

int main(int argc, char* argv[]) {
	Lista<int, descendente<int>> listita;
	int opcion, opcion_2, opcion_3, opcion_4,opcion_5;
	do
	{
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
			do {
				cout << "Has elegido Mostrar la Lista.\n";
				cout << "-----------" << endl << endl;
				cout << "\t1 .- Ida: " << endl;
				cout << "\t2 .- Reversa" << endl;
				cout << "Elige una opcion: \n";

				cin >> opcion_5;
				switch (opcion_5)
				{
				case 1:
					listita.Imprimir_1();
					break;

				case 2:
					listita.Imprimir_2();
					break;
				}
			} while (opcion != 3);
			cout << "\nPresiona 1 para volver a Menu....\n";
			cin >> opcion_4;
			break;
		}
	} while (opcion != 4);
	return 0;
}