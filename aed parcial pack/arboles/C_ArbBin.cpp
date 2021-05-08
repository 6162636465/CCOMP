#include <iostream>   
#include <ctime>
#include <cstdlib>



struct CBinNode
{
    int v;
    CBinNode* nodes[2];
    CBinNode(int v)
        : v(v) {
        nodes[0] = nodes[1] = 0;
    }
};

struct CBinTree
{
    CBinTree() { root = 0; b = 0; }
    ~CBinTree() {}

    bool insert(int x);
    bool remove(int x);
    void print();
    void printInver();
    void printNivel(int x);

private:

    bool find(int x, CBinNode**& p);

    CBinNode** Rep(CBinNode** p);
    void PreOreden(CBinNode* n);
    void InOrden(CBinNode* n);
    void PostOrden(CBinNode* n);
    void InReverse(CBinNode* n);
    void PorNiveles(CBinNode* n, int nivel);
    CBinNode* root;
    bool b;
};

bool CBinTree::find(int x, CBinNode**& p)
{
    for (p = &root; *p && (*p)->v != x; p = &((*p)->nodes[x > (*p)->v]));
    return (*p) != 0;
}

bool CBinTree::insert(int x)
{
    CBinNode** p;
    if (find(x, p)) { return 0; }
    *p = new CBinNode(x);
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    for (b = !b, q = &((*q)->nodes[b]); (*q)->nodes[!b]; q = &((*q)->nodes[!b]));
    return q;
}

bool CBinTree::remove(int x)
{
    CBinNode** p;
    if (!find(x, p)) { return 0; }

    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

void CBinTree::PreOreden(CBinNode* n)
{
    if (!n) return;
    std::cout << n->v << " ";
    InOrden(n->nodes[0]);
    InOrden(n->nodes[1]);
}

void CBinTree::InOrden(CBinNode* n)
{
    if (!n) return;
    InOrden(n->nodes[0]);
    std::cout << n->v << " ";
    InOrden(n->nodes[1]);
}

void CBinTree::PostOrden(CBinNode* n)
{
    if (!n) return;
    InOrden(n->nodes[0]);
    InOrden(n->nodes[1]);
    std::cout << n->v << " ";
}

void CBinTree::InReverse(CBinNode* n)
{
    if (!n) return;
    InReverse(n->nodes[1]);
    std::cout << n->v << " ";
    InReverse(n->nodes[0]);
}

void CBinTree::PorNiveles(CBinNode* n, int nivel)
{
    if (!n || nivel <= 0) { return; }
    PorNiveles(n->nodes[0], nivel-1);
    if (nivel == 1) { std::cout << n->v << " "; }
    PorNiveles(n->nodes[1], nivel-1);
}

void CBinTree::printNivel(int x)
{
    PorNiveles(root, x);
    std::cout << std::endl;
}

void CBinTree::print()
{
    InOrden(root);
    std::cout << std::endl;
}

void CBinTree::printInver()
{
    InReverse(root);
    std::cout << std::endl;
}

int main()
{
    CBinTree t;
    t.insert(50); t.print(); 
    t.insert(30); t.print(); 
    t.insert(60); t.print();
    t.insert(80); t.print(); 
    t.insert(55); t.print(); 
    t.insert(11); t.print();
    t.insert(33); t.print(); 
    t.insert(5); t.print(); 
    t.insert(14); t.print();
    t.insert(31); t.print(); 
    t.insert(48);
    
    std::cout << std::endl;
    
    t.print();
    t.printInver();
    t.printNivel(4);

    t.remove(31); t.print();
    t.remove(14); t.print();

    t.remove(11); t.print();
    t.remove(33); t.print();

    t.remove(50); t.print();

    t.remove(60); t.print();
    t.remove(48); t.print();
    t.remove(55); t.print();
    t.remove(5); t.print();
    t.remove(80); t.print();

    t.remove(30);

    t.print();

    return 0;
}
