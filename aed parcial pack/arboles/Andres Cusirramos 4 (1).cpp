
#include <iostream>
using namespace std;

template <class T>
struct CLess
{
    inline bool operator()(T a, T b)
    {   return a < b;   }
};

template <class T>
struct CGreater
{
    inline bool operator()(T a, T b)
    {   return a > b;   }
};

template <class T>
struct CNode
{
    CNode(T _v) { v = _v; next = 0; }
    T v;
    CNode<T>* next;
};

template <class T, class C>
class CList
{
public:
    CList();
    ~CList();
    bool Find(T x, CNode<T>**& p);
    bool Insert(T x);
    bool Remove(T x);
    void Print();
    void ReverseList();
private:
    CNode<T>* m_head;
    C m_c;
};

template <class T, class C>
CList<T,C>::CList()
{    m_head = 0;    }

template <class T, class C>
CList<T,C>::~CList()
{
    CNode<T> *a = m_head ,*b;
    while(a)
    {
        b = a->next;
        delete a;
        a = b;
    }
}

template <class T, class C>
bool CList<T,C>::Find(T x, CNode<T>**& p)
{
    for ( p = &m_head;
         *p && m_c( (*p)->v , x ); // (*p)->v < x
         p = &((*p)->next) );
    return *p && (*p)->v == x;
}

template <class T, class C>
bool CList<T,C>::Insert(T x)
{
    CNode<T>** p;
    if ( Find(x,p) ) return 0;
    CNode<T>* n = new CNode<T>(x);
    n->next = *p;
    *p = n;
    return 1;
}

template <class T, class C>
bool CList<T,C>::Remove(T x)
{
    CNode<T>** p;
    if ( ! Find(x,p) ) return 0;
    CNode<T>* t = *p;
    *p = (*p)->next;
    delete t;
    return 1;
}

template <class T, class C>
void CList<T,C>::Print()
{
    for ( CNode<T> *a = m_head; a; a = a->next )
        cout<<a->v<<" ";
    cout<<"."<<endl;
}

template <class T, class C>
void CList<T,C>::ReverseList()
{
    
        CNode<T>* aux = m_head;
        for (; aux->next; aux = aux->next);
        CNode<T>* newHead = aux;

    
        while (aux!= m_head) {
            CNode<T>* a = m_head;
            for (; a != aux; a = a->next)
                 aux->next = a;
                aux = aux->next;
            
        }
    
        m_head->next = nullptr;
        m_head = newHead;
}
////////////////////////////////////////////////////////////////////////////////

int main()
{
    CList<int, CGreater<int> > l;
    l.Insert(7);
    l.Insert(2);
    l.Insert(11);
    l.Insert(8);
    l.Insert(5);
    l.Insert(18);
    l.Insert(23);
    l.Insert(17);
    l.Insert(26);
    l.Print();
    l.ReverseList();
    l.Print();
}

