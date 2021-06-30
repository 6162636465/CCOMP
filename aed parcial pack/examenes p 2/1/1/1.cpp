#include <iostream>

using namespace std;

template<typename T>
struct nodo
{
    T valor;
    nodo* next;
    nodo(T _valor, nodo* _next = nullptr)
    {
        valor = _valor; next = _next;
    };
};

template<typename T>
class pila
{

public:
    bool vacio(); //indica si la pila está vacía
    void push(T elemento); //agrega un elemento
    T pop(); //retira un elemento y devuelve su valor 
    void print(); //imprime el contenido de la pila
    ~pila();
private:
    nodo<T>* top = nullptr;

};

template<typename T>
bool pila<T>::vacio()
{
    if (top)//si top no es nulo retorno falso
        return false;
    else
        return true;
}

template<typename T>
void pila<T>::print()
{
    nodo<T>* tmp = top;
    cout << "cima" << endl;
    for (; tmp; tmp = tmp->next)
        cout << tmp->valor << endl;
    cout << "base" << endl;
}

template<typename T>
void pila<T>::push(T elemento)
{
    nodo<T>* aux = 0;
    aux = new nodo<T>(elemento);
    aux->next = top;
    top = aux;
}

template<typename T>
T pila<T>::pop()
{
    nodo<T>* aux = 0;
    T val = 0;

    if (vacio()) {
        cout << "no hay elementos" << endl;
    }

    else {
        aux = top;
        val = top->valor;
        top = top->next;
        return val;
        delete aux;
    }
}

template<typename T>
pila<T>::~pila()
{
    nodo<T>* temp;
    while (top != nullptr) {
        temp = top;
        top = top->next;
        delete temp;
    }
    cout << "pila muerta" << endl;
}

int main() {
    pila<int> intPila;
    pila<char> charPila;
    cout << "hola" << endl;

    intPila.push(1);
    intPila.push(2);
    intPila.push(3);

    intPila.print();

    cout << endl;
    cout << "sale: " << intPila.pop() << endl;
    intPila.print();

    cout << "sale: " << intPila.pop() << endl;
    intPila.print();

    cout << "sale: " << intPila.pop() << endl;
    intPila.print();

    cout << endl;

    charPila.push('A');
    charPila.push('B');
    charPila.push('C');

    charPila.print();
    cout << endl;
    cout << "sale: " << charPila.pop() << endl;
    charPila.print();
    cout << endl;
}