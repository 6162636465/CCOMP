#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#define INF 1000000;

using namespace std;


template<class G>
struct CNodo
{
	//____________desempaqueta  la clase g________________________
	typedef typename G::N N;
	typedef typename G::edge edge;
	//____________________________________________________________
	N m_n;
	N m_data;
	list<edge*>m_edges;
	CNodo(N x) {
		m_data = x;
	}
};

template <class G>
struct Cedge {
	//____________desempaqueta  la clase g________________________
	typedef typename G::E E;
	typedef typename G::node node;
	//____________________________________________________________
	E m_e;
	node* m_nodes[2];
	E m_data;
	bool m_dir;//cuando es 0 es bi direccional y cuando es 1 solo apunta a una direccion
	Cedge(E x, node* A, node* B, bool dir)
	{
		m_data = x;
		m_nodes[0] = A;
		m_nodes[1] = B;
		m_dir = dir;
	}

};

template<class _N, class _E>
class CGraf
{
public:
	//ESTA definicion de tipo lo que ase es que el tipo N Y E de privado se pasa a publico
	typedef typename _E E;
	typedef typename _N N;
	//____________________________________________________________
	//dentro del grafo defino al grafo dentro de otro para pasar el "N"y "E" a las otras clases 
	typedef  CGraf<_N,_E>G;
	typedef  CNodo<G>node;
	typedef  Cedge<G>edge;
	//____________________________________________________________
	vector<node*>m_nodes;


	//metodos basicos

	void InsertNode(N n_value);
	bool InsertEdge(E e_value, node*& A, node*& B, bool dir);
	void printGraph();
	bool RemoveEdge(E e_value, node*& A, node*& B);
	bool RemoveNode(N e_value);

	E DijkstraFunc(node* A, node* B, list<edge*>* Path = NULL);

	//_____________________________________________________________________________________________
};
template <class N, class E>
void CGraf<N, E>::InsertNode(N m_value)
{
	m_nodes.push_back(new CNodo<CGraf<N, E> >(m_value));
}

template <class N, class E>
bool CGraf<N, E>::InsertEdge(E e_value, node*& A, node*& B, bool dir) {

	Cedge<CGraf<N, E>>* my_edge = new Cedge<CGraf<N, E> >(e_value, A, B, dir);
	(A->m_edges).push_back(my_edge);

	if (dir == 0) {
		Cedge<CGraf<N, E> >* my_edge2 = new Cedge<CGraf<N, E> >(e_value, B, A, dir);
		(B->m_edges).push_back(my_edge2);
	}

	else {
		(B->m_edges).push_back(my_edge);
	}
	return 1;
}

template<class N, class E>
void CGraf<N, E>::printGraph() {
	for (int i = 0; i < m_nodes.size(); i++) 
	{//ingreso al vector de nodos del grafo
		node* temp_node = m_nodes[i]; // cada nodo
		cout << temp_node->m_data;// etiqueta-valor de cada nodo

		for (typename list<edge*>::iterator it = temp_node->m_edges.begin(); it != temp_node->m_edges.end(); ++it)
		{//recorrer la lista de punteros a aristas del nodo
			if (temp_node->m_data != (*it)->m_nodes[1]->m_data) {
				cout << " ---> " << (*it)->m_data << "(" << ((*it)->m_nodes[1])->m_data << ")";
				cout << endl;
			}
		}
		cout << "\n";
	}
}

template <class N, class E>
bool CGraf<N, E>::RemoveEdge(E e_value, node*& A, node*& B) {
	for (typename list<edge*>::iterator it = A->m_edges.begin(); it != A->m_edges.end(); ++it) {
		if (e_value == (*it)->m_data && (*it)->m_nodes[0]->m_data == A->m_data && (*it)->m_nodes[1]->m_data == B->m_data) {
			A->m_edges.erase(it);
			break;
		};
	}
	for (typename list<edge*>::iterator it = B->m_edges.begin(); it != B->m_edges.end(); ++it) {
		if (e_value == (*it)->m_data &&
			((*it)->m_nodes[0]->m_data == B->m_data &&
				(*it)->m_nodes[1]->m_data == A->m_data) ||
			((*it)->m_nodes[0]->m_data == A->m_data &&
				(*it)->m_nodes[1]->m_data == B->m_data)
			) {
			B->m_edges.erase(it);
			break;
		};
	}
}

template <class N, class E>
bool CGraf<N, E>::RemoveNode(N n_value) {
	bool flag = false;
	node* Searched_Node;
	int count = 0;
	for (unsigned int i = 0; i < m_nodes.size() && !flag; i++) {///entra al vector de nodos
		if (n_value == m_nodes[i]->m_data) { /// si es igual al dato pedido
			Searched_Node = m_nodes[i]; /// salvo
			flag = true; ///para detener el bucle
			count++;///salvar la posicion para luego hacer erase
		}
	}
	cout << "Nodo encontrado" << endl;
	node* temp;
	///recorrer mi propia lista de arista (soy el nodo a eliminar)
	for (typename list<edge*>::iterator it = Searched_Node->m_edges.begin(); it != Searched_Node->m_edges.end(); ++it) {
		if (n_value == (*it)->m_nodes[0]->m_data) {///preguntar si yo estoy en m_nodes[0]
			temp = (*it)->m_nodes[1];///como estoy en el nodo[0] salvo el otro nodo[1] para entrar a la lista con el seegundo for
		}
		else {
			temp = (*it)->m_nodes[0];///salvar el otro nodo[0] para recorrer en 2do for
		}
		//recorrer el otro nodo
		for (typename list<edge*>::iterator it2 = temp->m_edges.begin(); it2 != temp->m_edges.end(); ++it2) {
			if ((*it2)->m_nodes[0]->m_data == Searched_Node->m_data || (*it2)->m_nodes[1]->m_data == Searched_Node->m_data) {
				it2 = temp->m_edges.erase(it2);
				cout << "Borré arista de la otra lista" << endl;
			}
		}
		it = Searched_Node->m_edges.erase(it);
		cout << "borré todas las aristas conectadas al nodo a eliminar" << endl;
	}
	m_nodes.erase(m_nodes.begin() + (count - 1));
	cout << "nodo A y B eliminado" << endl;
}
template <class N, class E>
E CGraf<N, E>::DijkstraFunc(node* A, node* B, list<edge*>* Path)
{
	priority_queue<pair<E, node*>, vector<pair<E, node*> >, greater<pair<E, node*> > > Q;//pair, vector donde se almacena, funcion de prioridad
	map<node*, E> dist;///map de distancias
	map<node*, edge*> Ant; /// map de aristas anteriores
	for (unsigned int i = 0; i < m_nodes.size(); i++) { /// recorro el vector grafo
		dist[m_nodes[i]] = INF; /// distancia infinitas
	}
	dist[A] = 0;/// distancia del nodo inicial va a ser 0, es el parametro que paso
	Ant[A] = NULL; /// no tiene arista anterior
	Q.push(make_pair(0, A));///insertar a la cola de mi primer distancia, nodo a visitar sus adjacentes
	while (!Q.empty()) { /// mientras no este vacio
		pair<E, node*> top = Q.top(); ///guardo el primer elemento de la priority kiwi
		Q.pop();///elimino elemento de la cola
		E distance = top.first;/// guardo la distancia
		node* u = top.second;/// guardo segundo elemento, que es el nodo
		if (u == B) { /// if llego al destino, me voy, acabe, aprobe, ok no
			break;
		}

		if (dist[u] == distance) { ///si la distancia que tengo de ese nodo ya hizo el procedimiento con otra distancia menor
			for (typename list<edge*>::iterator it = u->m_edges.begin(); it != u->m_edges.end(); ++it) {///recorrer la lista de punteros a aristas del nodo
				node* v = (*it)->m_nodes[1]; ///visito adyancentes
				if (v != u) { /// si yo mismo , no hago nada
					E new_dist = dist[u] + (*it)->m_data; /// peso que acarrea mi nodo + arista visitada
					if (new_dist < dist[v]) { /// si es menor
						dist[v] = new_dist; /// update distancia en map distancia
						Ant[v] = (*it);///update anterior arista
						Q.push(make_pair(new_dist, v));/// push a la queue
					}
				}
			}
		}
	}
	if (Path) {///si el vector , me sirve para imprimir
		edge* actual = Ant[B]; /// ultima de las arista del camino
		while (actual) { /// mientras la arista sea ! de NULL
			Path->push_front(actual); /// agrego al inicio de list camino
			actual = Ant[actual->m_nodes[0]]; /// voy a la anterior arista
		}
		for (typename list<edge*>::iterator it = Path->begin(); it != Path->end(); ++it) {///recorrer la lista de punteros a aristas del nodo
			node* u = (*it)->m_nodes[0];///print
			cout << u->m_data << "--- ";
			node* v = (*it)->m_nodes[1];
			cout << " [ W(E): " << (*it)->m_data << " ] -->" << v->m_data << endl;
		}
	}
	cout << "Peso total del camino óptimo : ";
	return dist[B]; // retornar el camino minimo
}
int main()
{
	CGraf<int, int>A;

	for (int i = 1; i < 7; i++) 
	{
		A.InsertNode(i);
	}
	//(distancia u peso,nodo[i],nodo[j],direccion: 1 unic , 0 bi dir)
	A.InsertEdge(7, A.m_nodes[0], A.m_nodes[1], 1);
	A.InsertEdge(9, A.m_nodes[0], A.m_nodes[2], 0);
	A.InsertEdge(14, A.m_nodes[0], A.m_nodes[5], 0);
	A.InsertEdge(10, A.m_nodes[1], A.m_nodes[2], 0);
	A.InsertEdge(15, A.m_nodes[1], A.m_nodes[3], 0);
	A.InsertEdge(2, A.m_nodes[2], A.m_nodes[5], 0);
	A.InsertEdge(11, A.m_nodes[2], A.m_nodes[3], 0);
	A.InsertEdge(6, A.m_nodes[3], A.m_nodes[4], 1);
	A.InsertEdge(9, A.m_nodes[4], A.m_nodes[5], 0);
	
	list<Cedge<CGraf<int, int> >*> Path;
	cout << "grafo :" << endl;
	A.printGraph();
	cout << "algoritmo dyxtra" << endl;
	cout << A.DijkstraFunc(A.m_nodes[0], A.m_nodes[4], &Path) << endl;
}