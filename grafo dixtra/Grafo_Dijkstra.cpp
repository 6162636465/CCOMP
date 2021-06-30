
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#define INF 1000000;
using namespace std;

template <class G>
struct CNode {
	typedef typename G::Edge Edge;
	typedef typename G::n N;
	N m_data;
	list<Edge*>m_edges;
	CNode(N x) {
		m_data = x;
	}
};

template <class G>
struct CEdge {
	typedef typename G::Node Node;
	typedef typename G::e E;
	Node* m_nodes[2];
	E m_data;
	bool m_dir;//0, <->; 1, m_nodes[0] -> m_nodes[1]
	CEdge(E x, Node* A, Node* B, bool dir) {
		m_data = x;
		m_nodes[0] = A;
		m_nodes[1] = B;
		m_dir = dir;
	}
};

template <class N, class E>
class CGraph {
public:
	typedef CGraph <N, E> self;
	typedef CNode <self> Node;
	typedef CEdge <self> Edge;
	typedef N n;
	typedef E e;
	vector <Node*> m_nodes;
	bool InsertNode(N n_value);
	bool InsertEdge(E e_value, Node*& A, Node*& B, bool dir);
	void printGraph();
	bool RemoveEdge(E e_value, Node*& A, Node*& B);
	bool RemoveNode(N e_value);
	E DijkstraFunc(Node* A, Node* B, list<Edge*>* Path = NULL);
};

template <class N, class E>
bool CGraph<N, E>::InsertNode(N m_value) {
	m_nodes.push_back(new CNode< CGraph<N, E> >(m_value));
}

template <class N, class E>
bool CGraph<N, E>::InsertEdge(E e_value, Node*& A, Node*& B, bool dir) {

	CEdge<CGraph<N, E> >* my_edge = new CEdge<CGraph<N, E> >(e_value, A, B, dir);
	(A->m_edges).push_back(my_edge);

	if (dir == 0) {
		CEdge<CGraph<N, E> >* my_edge2 = new CEdge<CGraph<N, E> >(e_value, B, A, dir);
		(B->m_edges).push_back(my_edge2);
	}

	else {
		(B->m_edges).push_back(my_edge);
	}
	return 1;
}

template<class N, class E>
void CGraph<N, E>::printGraph() {
	for (int i = 0; i < m_nodes.size(); i++) {//ingreso al vector de nodos del grafo
		Node* temp_node = m_nodes[i]; // cada nodo
		cout << temp_node->m_data;// etiqueta-valor de cada nodo

		for (typename list<Edge*>::iterator it = temp_node->m_edges.begin(); it != temp_node->m_edges.end(); ++it) {//recorrer la lista de punteros a aristas del nodo
			if (temp_node->m_data != (*it)->m_nodes[1]->m_data) {
				cout << " ---> " << (*it)->m_data << "(" << ((*it)->m_nodes[1])->m_data << ")";
				cout << endl;
			}
		}
		cout << "\n";
	}
}

template <class N, class E>
bool CGraph<N, E>::RemoveEdge(E e_value, Node*& A, Node*& B) {
	for (typename list<Edge*>::iterator it = A->m_edges.begin(); it != A->m_edges.end(); ++it) {
		if (e_value == (*it)->m_data && (*it)->m_nodes[0]->m_data == A->m_data && (*it)->m_nodes[1]->m_data == B->m_data) {
			A->m_edges.erase(it);
			break;
		};
	}
	for (typename list<Edge*>::iterator it = B->m_edges.begin(); it != B->m_edges.end(); ++it) {
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
bool CGraph<N, E>::RemoveNode(N n_value) {
	bool flag = false;
	Node* Searched_Node;
	int count = 0;
	for (unsigned int i = 0; i < m_nodes.size() && !flag; i++) {///entra al vector de nodos
		if (n_value == m_nodes[i]->m_data) { /// si es igual al dato pedido
			Searched_Node = m_nodes[i]; /// salvo
			flag = true; ///para detener el bucle
			count++;///salvar la posicion para luego hacer erase
		}
	}
	cout << "Nodo encontrado" << endl;
	Node* temp;
	///recorrer mi propia lista de arista (soy el nodo a eliminar)
	for (typename list<Edge*>::iterator it = Searched_Node->m_edges.begin(); it != Searched_Node->m_edges.end(); ++it) {
		if (n_value == (*it)->m_nodes[0]->m_data) {///preguntar si yo estoy en m_nodes[0]
			temp = (*it)->m_nodes[1];///como estoy en el nodo[0] salvo el otro nodo[1] para entrar a la lista con el seegundo for
		}
		else {
			temp = (*it)->m_nodes[0];///salvar el otro nodo[0] para recorrer en 2do for
		}
		//recorrer el otro nodo
		for (typename list<Edge*>::iterator it2 = temp->m_edges.begin(); it2 != temp->m_edges.end(); ++it2) {
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
E CGraph<N, E>::DijkstraFunc(Node* A, Node* B, list<Edge*>* Path) {

	priority_queue<pair<E, Node*>, vector<pair<E, Node*> >, greater<pair<E, Node*> > > Q;//pair, vector donde se almacena, funcion de prioridad
	map<Node*, E> dist;///map de distancias
	map<Node*, Edge*> Ant; /// map de aristas anteriores
	for (unsigned int i = 0; i < m_nodes.size(); i++) { /// recorro el vector grafo
		dist[m_nodes[i]] = INF; /// distancia infinitas
	}
	dist[A] = 0;/// distancia del nodo inicial va a ser 0, es el parametro que paso
	Ant[A] = NULL; /// no tiene arista anterior
	Q.push(make_pair(0, A));///insertar a la cola de mi primer distancia, nodo a visitar sus adjacentes
	while (!Q.empty()) { /// mientras no este vacio
		pair<E, Node*> top = Q.top(); ///guardo el primer elemento de la priority kiwi
		Q.pop();///elimino elemento de la cola
		E distance = top.first;/// guardo la distancia
		Node* u = top.second;/// guardo segundo elemento, que es el nodo
		if (u == B) { /// if llego al destino, me voy, acabe, aprobe, ok no
			break;
		}

		if (dist[u] == distance) { ///si la distancia que tengo de ese nodo ya hizo el procedimiento con otra distancia menor
			for (typename list<Edge*>::iterator it = u->m_edges.begin(); it != u->m_edges.end(); ++it) {///recorrer la lista de punteros a aristas del nodo
				Node* v = (*it)->m_nodes[1]; ///visito adyancentes
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
		Edge* actual = Ant[B]; /// ultima de las arista del camino
		while (actual) { /// mientras la arista sea ! de NULL
			Path->push_front(actual); /// agrego al inicio de list camino
			actual = Ant[actual->m_nodes[0]]; /// voy a la anterior arista
		}
		for (typename list<Edge*>::iterator it = Path->begin(); it != Path->end(); ++it) {///recorrer la lista de punteros a aristas del nodo
			Node* u = (*it)->m_nodes[0];///print
			cout << u->m_data << "--- ";
			Node* v = (*it)->m_nodes[1];
			cout << " [ W(E): " << (*it)->m_data << " ] -->" << v->m_data << endl;
		}
	}
	cout << "Peso total del camino óptimo : ";
	return dist[B]; // retornar el camino minimo
}

int main() {


	CGraph<int, int> A;

	for (int i = 1; i < 7; i++) {
		A.InsertNode(i);
	}
	A.InsertEdge(7, A.m_nodes[0], A.m_nodes[1], 0);
	A.InsertEdge(9, A.m_nodes[0], A.m_nodes[2], 0);
	A.InsertEdge(14, A.m_nodes[0], A.m_nodes[5], 0);
	A.InsertEdge(10, A.m_nodes[1], A.m_nodes[2], 0);
	A.InsertEdge(15, A.m_nodes[1], A.m_nodes[3], 0);
	A.InsertEdge(2, A.m_nodes[2], A.m_nodes[5], 0);
	A.InsertEdge(11, A.m_nodes[2], A.m_nodes[3], 0);
	A.InsertEdge(6, A.m_nodes[3], A.m_nodes[4], 1);
	A.InsertEdge(9, A.m_nodes[4], A.m_nodes[5], 0);
	list<CEdge<CGraph<int, int> >*> Path;
	cout << A.DijkstraFunc(A.m_nodes[0], A.m_nodes[4], &Path) << endl;

	return 0;
}