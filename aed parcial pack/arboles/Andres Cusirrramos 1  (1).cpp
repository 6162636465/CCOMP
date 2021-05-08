#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(){}; // Agregue constructor por defecto
    CBinNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0;  }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void PrintLevelX(int x);
    void PrintRange(int from, int to);
    void PrintOneChildNodes();

private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
};


// Mis metodos
struct NodeCola{
    CBinNode *v;
    NodeCola *next;
    NodeCola(CBinNode *V){
        v=V;
    }
};

struct Cola{
    NodeCola * forward;
    NodeCola *back;
    void push(Cola q,CBinNode *a);
    CBinNode* pop(Cola q);
};

void Cola::push(Cola q,CBinNode *a){
    NodeCola *p;
    p= new NodeCola(a);
    p->next=nullptr;
    if(q.forward==nullptr){
        q.forward=p;
    }
    else{
        (q.back)->next=p;
        q.back=p;
    }
}

CBinNode* Cola::pop(Cola q){
    NodeCola *p;
    p=q.forward;
    CBinNode *n=p->v;
    q.forward=(q.forward)->next;
    delete (p);
    return n;
}
    

// Fin de mis metos

CBinTree::CBinTree()
{   m_root = 0; }

CBinTree::~CBinTree()
{}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for ( p = &m_root ; *p && (*p)->value != x ; p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[ !(*p)->nodes[0] ];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** p)
{
    bool b = rand()%2;
    for( p = &( (*p)->nodes[b] ); (*p)->nodes[!b]; p = &( (*p)->nodes[!b] ) );
    return p;
}

void CBinTree::InOrder(CBinNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}

void CBinTree::PrintLevelX(int x)
{
    cout<<"\nLevel: "<<x<<endl;
       Cola q;
     q.forward=nullptr;
     q.back=nullptr;
       cout << "\t";

       if(m_root!=NULL)
       {
           q.push(q,m_root);

           while(q.forward!=NULL)
           {
               m_root= q.pop(q);
               cout << m_root->value << ' ';

               if(m_root->nodes[1]!=NULL)
                   q.pop(q);
               if(m_root->nodes[0]!=NULL)
                   q.push(q,m_root->nodes[0]);
           }
       }
}

void CBinTree::PrintRange(int from, int to)
{
    cout<<"\nRange("<<from<<","<<to<<")\n";
    CBinNode **n, **t;
    Find(from,n);
    Find(to, t);
    
    //for(CBinTree*i=*n;i<)

}

void CBinTree::PrintOneChildNodes(void)
{
    cout<<"\nOneChildNodes:\n";
    //...

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    
    t.Insert(47); t.Insert(15); t.Insert(83); t.Insert(59); t.Insert(36); t.Insert(44); t.Insert(41);
    t.Insert(75); t.Insert(62); t.Insert(7); t.Insert(21); t.Insert(65); t.Insert(85); t.Insert(4);
    t.Insert(97); t.Insert(47); t.Insert(87); t.Insert(56); t.Insert(42); t.Insert(32); t.Insert(13);
    t.PrintLevelX(0);
    t.PrintLevelX(1);
    t.PrintLevelX(2);
    t.PrintLevelX(3);
    t.PrintLevelX(4);
    t.PrintRange(20,75);
    t.PrintRange(56,97);
    t.PrintRange(2,30);
    t.PrintOneChildNodes();
}

