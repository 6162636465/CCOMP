#include <iostream>
#include <thread>
#include <deque>
#include <list>
#include <vector>
#include <ctime> 
using namespace std;

template <class T>
int Localizar(T a, std::deque<T> Q);
bool isAllTrue(std::vector<bool> l);
int indiceDelMinimoNoVisto(std::vector<int> l, std::vector<bool> visto);

template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;
    N value;
    std::list<Edge*> edges;
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;
    E value;
    Node* nodes[2];
    bool dir; 
};

template<class _N, class _E>
class CGraph
{
public:
    typedef CGraph<_N, _E>   G;
    typedef CNode<G>        Node;
    typedef CEdge<G>        Edge;
    typedef _N              N;
    typedef _E              E;
    bool InsNode(N n, Node*& x);
    bool InsEdge(Node* a, Node* b, E e, bool d);
    bool RemEdge(Node* a, Node* b, E e);
    bool RemNode(N n);
    std::deque<Node*> nodes;
};

template<class _N, class _E>
bool CGraph<_N, _E>::InsNode(N n, Node*& x)
{
    Node* node = new Node;
    node->value = n;
    nodes.push_back(node);
    x = node;
    return 1;
}

template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(Node* a, Node* b, E e, bool d)
{
    Edge* edge = new Edge;
    edge->value = e;
    edge->dir = d;
    edge->nodes[0] = a;
    edge->nodes[1] = b;
    a->edges.push_back(edge);
    b->edges.push_back(edge);
    return 1;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemEdge(Node* a, Node* b, E e)
{
    typename std::list<Edge*>::iterator it;
    for (it = a->edges.begin();
        it != a->edges.end() && it->value != e;
        it++);
    a->edges.erase(it);
    for (it = b->edges.begin();
        it != b->edges.end() && it->value != e;
        it++);
    CEdge<G>* edge = b->edges.erase(it);
    delete[] edge;
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemNode(N n)
{
    typename std::deque<Node*>::iterator itN;
    for (itN = nodes.begin();
        itN != nodes.end() && itN->value != n;
        itN++);
    typename std::list<Edge*>::iterator itE;
    for (itE = itN->edges.begin();
        itE != itN->edges.end();
        itE++)
    {
        Node* a = itE->nodes[0], * b = itE->nodes[1];
        RemEdge(a, b, itE->value);
    }
    nodes.erase(itN);
    delete[] itN;
    return 1;
}

struct CGraphChar : public CGraph<char, int>
{
    void Print();
    void camino(int dest, std::vector<int> prev, std::vector<Node*>& path);
    std::deque<Node*> adyacentes(Node* a, std::deque<Node*> Q, std::vector<bool> visto);
    bool isConnected(Node* a, Node* b, Edge*& p);
    bool isConnected(Node* a, Node* b);
    int pesoEntre(Node* a, Node* b);
    void Preprocesado();
    void Dijkstra(int a);
    void CaminoMasCorto(Node* a, Node* b);
    void printPreprocesado();
private:
    struct infoNode
    {
        Node* ptr;
        std::vector<int> dist;
        std::vector<std::vector<Node*>> paths;
    };
    std::vector<infoNode*> iNode;
    bool estaPreprocesado = false;
};

void CGraphChar::Print()
{
    typename std::deque<Node*>::iterator itN;
    for (itN = nodes.begin();
        itN != nodes.end();
        itN++)
    {
        std::cout << (*itN)->value << std::endl;
        typename std::list<Edge*>::iterator itE;
        for (itE = (*itN)->edges.begin();
            itE != (*itN)->edges.end();
            itE++)
        {
            if ((*itE)->dir == false)
            {
                std::cout << "  ";
                std::cout << "<";
                std::cout << "-(" << (*itE)->value << ")->";
                std::cout << (*itE)->nodes[0]->value << std::endl;
            }
            else
            {
                if ((*itE)->nodes[0] == *itN)
                {
                    std::cout << "  ";
                    std::cout << "-(" << (*itE)->value << ")->";
                    std::cout << (*itE)->nodes[1]->value << std::endl;
                }
            }
        }
    }
    std::cout << "\n\n" << std::endl;
}

void CGraphChar::camino(int dest, std::vector<int> prev, std::vector<Node*>& path)
{
    if (prev[dest] != -1)
        camino(prev[dest], prev, path);
    path.push_back(nodes[dest]);
}

typename std::deque<CGraphChar::Node*> CGraphChar::adyacentes(Node* a, std::deque<Node*> Q, std::vector<bool> visto)
{
    std::deque<Node*> ady;
    typename std::vector<bool>::iterator vis = visto.begin();
    typename std::deque<Node*>::iterator it;
    for (it = Q.begin(); it != Q.end(); it++, vis++)
    {
        if (!(*vis) && isConnected(a, *it))
        {
            ady.push_back(*it);
        }
    }
    return ady;
}

bool CGraphChar::isConnected(Node* a, Node* b, Edge*& p)
{
    typename std::list<Edge*>::iterator it = a->edges.begin();
    for (; it != a->edges.end(); it++)
    {
        if ((*it)->nodes[1] == b || (*it)->nodes[0] == b)
        {
            if ((*it)->dir == false)
            {
                p = *it;
                return true;
            }
            else
            {
                if ((*it)->nodes[1] == b)
                {
                    p = *it;
                    return true;
                }
            }
        }
    }
    return false;
}

bool CGraphChar::isConnected(Node* a, Node* b)
{
    typename std::list<Edge*>::iterator it = a->edges.begin();
    for (; it != a->edges.end(); it++)
    {
        if ((*it)->nodes[1] == b || (*it)->nodes[0] == b)
        {
            if ((*it)->dir == false)
            {
                return true;
            }
            else
            {
                if ((*it)->nodes[1] == b)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


int CGraphChar::pesoEntre(Node* a, Node* b)
{
    Edge* p;
    isConnected(a, b, p);
    return p->value;
}

void CGraphChar::Dijkstra(int a)
{
    std::vector<bool> visto;
    std::vector<int> prev;
    infoNode* iN = iNode[a];
    int source = a;
    typename std::deque<Node*>::iterator it;
    int n = 0;
    for (; n < nodes.size(); n++)
    {
        std::vector<Node*> path;
        Edge* p = nullptr;
        if (!isConnected(nodes[source], nodes[n], p))
        {
            iN->dist.push_back(100000);
        }
        else
        {
            iN->dist.push_back(p->value);
        }
        iN->paths.push_back(path);
        iN->paths[n].push_back(nodes[a]);
        visto.push_back(false);
        prev.push_back(-1);
    }

    iN->paths[source].pop_back();
    iN->dist[source] = 0;
    visto[source] = true;

    while (!isAllTrue(visto))
    {
        int u = indiceDelMinimoNoVisto(iN->dist, visto);
        visto[u] = true;
        std::deque<Node*> vecinos = adyacentes(nodes[u], nodes, visto);
        typename std::deque<Node*>::iterator it;
        int p = 0;
        for (it = vecinos.begin(); it != vecinos.end(); it++, p++)
        {
            int alt = iN->dist[u] + pesoEntre(nodes[u], *it);
            int v = Localizar<Node*>(*it, nodes);
            if (iN->dist[v] > alt)
            {
                iN->dist[v] = alt;
                prev[v] = u;
            }
        }
        camino(u, prev, iN->paths[u]);
    }
}

void CGraphChar::Preprocesado()
{
    //aca uso de threads
    int i = 0, nThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> ths(nThreads);
    int n = 0, t = 0;
    for (; n < nodes.size(); n++, t++)
    {
        if (t == nThreads)
        {
            for (int i = 0; i < nThreads; i++)
            {
                ths[i].join();
            }
            t = 0;
        }
        infoNode* iN = new infoNode;
        iN->ptr = nodes[n];
        iNode.push_back(iN);
        unsigned t0, t1;
        t0 = clock();
        ths[t] = std::thread(&CGraphChar::Dijkstra, this, n);
        t1 = clock();
        double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    }
    estaPreprocesado = true;


    if (t != nThreads)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            unsigned t0, t1;

            t0 = clock();
            ths[i].join();
            t1 = clock();
            double time = (double(t1 - t0) / CLOCKS_PER_SEC);
          
        }
    }
}
int indiceDelMinimoNoVisto(std::vector<int> l, std::vector<bool> visto)
{
    int unsigned i = 0, min = l[0], indx = 0;

    int unsigned ini = 0;
    while (visto[ini])
    {
        ini++;
    }

    min = l[ini];
    indx = ini;

    for (; i < l.size(); i++)
    {
        if (!(visto[i]) && min > l[i]) {
            min = l[i];
            indx = i;
        }
    }
    return indx;
}

bool isAllTrue(std::vector<bool> l)
{
    typename std::vector<bool>::iterator it = l.begin();
    for (; it != l.end(); it++)
    {
        if (!*it)
        {
            return false;
        }
    }
    return true;
}

template <class T>
int Localizar(T a, std::deque<T> Q)
{
    int indx = 0;
    for (; indx < Q.size(); indx++)
    {
        if (a == Q[indx])
        {
            return indx;
        }
    }
    return 0;
}
void CGraphChar::printPreprocesado()
{
    if (!estaPreprocesado) return;
    std::deque<Node*>::iterator itnodes = nodes.begin();
    std::vector<infoNode*>::iterator itin = iNode.begin();
    for (; itnodes != nodes.end(); itnodes++, itin++)
    {
        std::cout << "__________________Preprocesado_________________________" << std::endl;

        typename std::vector<std::vector<Node*>>::iterator itpaths = (*itin)->paths.begin();
        typename std::vector<int>::iterator itdist = (*itin)->dist.begin();
        int indx = 0;
        for (; itpaths != (*itin)->paths.end(); itpaths++, itdist++, indx++)
        {
            std::cout << (*itnodes)->value << " - " << nodes[indx]->value << " - " << *(itdist) << " -> ";

            typename std::vector<Node*>::iterator itcamino = (*itpaths).begin();
            for (; itcamino != (*itpaths).end(); itcamino++)
            {
                std::cout << (*itcamino)->value << " ";
            }
            std::cout << std::endl;
        }

     
    }
}

void CGraphChar::CaminoMasCorto(Node* a, Node* b)
{
    if (!estaPreprocesado) return;
    std::cout << "CaminoMasCorto" << std::endl;

    std::cout << a->value << " - " << b->value << " - ";

    int source = Localizar<Node*>(a, nodes);
    int destiny = Localizar<Node*>(b, nodes);

    std::cout << iNode[source]->dist[destiny] << " -> ";

    typename std::vector<Node*>::iterator itcamino = iNode[source]->paths[destiny].begin();
    for (; itcamino != iNode[source]->paths[destiny].end(); itcamino++)
    {
        std::cout << (*itcamino)->value << " ";
    }
}




int main()
{
    CGraphChar g;
    CNode<CGraph<char, int>>* a, * b, * c, * d, * e;
    g.InsNode('1', a);
    g.InsNode('2', b);
    g.InsNode('3', c);
    g.InsNode('4', d);
    g.InsNode('5', e);
    g.InsEdge(a, b, 2, true);
    g.InsEdge(a, e, 10, true);
    g.InsEdge(b, c, 3, true);
    g.InsEdge(b, e, 7, true);
    g.InsEdge(c, a, 4, true);
    g.InsEdge(c, d, 4, true);
    g.InsEdge(d, e, 5, true);
    g.InsEdge(e, c, 3, true);
    cout << "___________________grafo imprimido :____________________" << endl;
    g.Print();
    unsigned t0, t1;
    t0 = clock();
    g.Preprocesado(); 
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    g.printPreprocesado();

    t0 = clock();
    g.CaminoMasCorto(d, b);
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);

    t0 = clock();
    g.CaminoMasCorto(e, b);
    t1 = clock();
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << endl;
}