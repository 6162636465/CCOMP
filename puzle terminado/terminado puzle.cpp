#include <iostream>
#include <stdlib.h>
#include <time.h>
#define Letra_a 97
#define Letra_w 119
#define Letra_s 115
#define Letra_d 100
#define Letra_q 113
using namespace std;

int a=1,b=a;
bool ppp=true;
int mat[4][4]={{10,11,2,3},{4,5,6,7},{8,9,15,12},{13,14,0,1}};
void inputt()
{
    char f;
    cout<<"mueva el 0 y ponga q para salir del juego"<<endl;
		cin>>f;
		int *i;
    bool encontrado=false;
    for(i=mat[0]; i<mat[0]+16 && encontrado==false; i++)
    {
        if(*i==0)
        {
            encontrado=true;
        }
    }
    i--;

    if(f==Letra_w)
    {
        if(i > mat[0]+3)
        {
            swap(*i,*(i-4));
        }
    }
    else if(f==Letra_s)
    {
        if(i < mat[3])
        {
            swap(*i,*(i+4));
        }
    }
    else if(f==Letra_a)
    {
        if(i != mat[0] && i != mat[1] && i != mat[2] && i != mat[3])
        {
            swap(*i,*(i-1));
        }
    }
    else if(f==Letra_d)
    {
        if(i != mat[0]+3 && i != mat[1]+3 && i != mat[2]+3 && i != mat[3]+3)
        {
            swap(*i,*(i+1));
        }
    }
    else if(f==Letra_q)
    {
        ppp=false;
    }
    system("cls");
}
void imprimirMatriz()
{
    int *i;
    for(i=mat[0]; i<mat[0]+16; i++)
    {
        if(*i>9)
            {
                cout<<"|"<<*i<<"|";
            }
        else{
        cout<<"|"<<*i<<" |";
        }
        if(*i==mat[0][3] || *i==mat[1][3] ||*i==mat[2][3] )
        {
            cout<<endl;
        }
    }
    cout<<endl;
}
void Matriz()
 {
    //recorrido usando punteros y aritmetica de puntero
    int cont=0,epalda=0;
    srand(time(NULL));
    imprimirMatriz();
    inputt();
    //comparacion=Comparacion();
    system("cls");
}
int main()
{
while (ppp==true){
    Matriz();
    imprimirMatriz();
    inputt();
}
cout<<"fin del juego"<<endl;
}
