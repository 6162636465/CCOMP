#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class Nodo {
public:
	int valor;
	Nodo* next;
	Nodo(int _valor, Nodo* _next = NULL) {
		valor = _valor;
		next = _next;
	}
};

class Lista {
public:
	Nodo* head;
	Lista() {
		head = NULL;
	}
	bool Buscar(int valor) {
		Nodo* temp = head;
		if (head != 0) {
			if (temp->valor == valor) {
				return 1;
			}
			temp = temp->next;
			while (temp != head) {
				if (temp->valor == valor) {
					return 1;
				}
				temp = temp->next;
			}
		}
		return 0;
	}
	void Agregar(int valor) {
		if (Buscar(valor) == 0) {
			if (head == 0) {
				head = new Nodo(valor);
				head->next = head;
				return;
			}
			if (valor > head->valor && head->next == head) // dos elementos
			{
				head->next = new Nodo(valor, head);
				return;
			}
			Nodo* temp = head;
			do
			{
				if (temp->next == head && temp->valor < valor)        //dos elementos
				{
					temp->next = new Nodo(valor, head);
					return;
				}

				else if (temp->valor > valor)      //inicio
				{

					Nodo* last = head;
					if (temp == head) {
						while (last->next != head)
						{
							last = last->next;
						}
						head = new Nodo(valor, temp);
						last->next = head;
						return;
					}
					temp = new Nodo(valor, temp);
				}
				else if (temp->next->valor > valor)
				{
					temp->next = new Nodo(valor, temp->next);
					return;
				}
				temp = temp->next;
			} while (temp != head);
		}

	}
	void Eliminar(int valor)
	{
		if (head != 0 and Buscar(valor))
		{
			Nodo* temp = head;
			if (head->valor == valor)
			{
				Nodo* last = head;
				while (last->next != head)
				{
					last = last->next;
				}
				last->next = head->next;
				delete head;
				head = last->next;
				return;
			}
			do
			{
				if (temp->next->next == head) // MEDIO
				{
					delete temp->next;
					temp->next = head;
					return;
				}
				else if (temp->next->valor == valor) // FINAL
				{
					Nodo* next = temp->next->next;
					delete temp->next;
					temp->next = next;
					return;
				}
				temp = temp->next;
			} while (temp != head);
		}

	}
	~Lista()
	{
		if (head != 0)
		{
			Nodo* temp = head;
			while (temp)
			{
				Nodo* next = temp->next;
				delete temp;
				temp = next;
			}
		}

	}
	void Imprimir()
	{
		if (head != 0)
		{
			Nodo* temp = head;
			do
			{
				cout<< temp->valor << " ";
				if (temp->next)
					cout << "-> " << temp->next->valor << endl;
				temp = temp->next;
			} while (temp != head);
		}
	}
};

int main(){
	Lista* listita = new Lista();

	listita->Agregar(5);
	listita->Agregar(3);
	listita->Agregar(7);
	listita->Agregar(10);
	listita->Agregar(9);
	listita->Agregar(1);
	listita->Agregar(-1);
	listita->Agregar(-100);
	listita->Agregar(0);

	listita->Imprimir();

	return 0;
}