#include <iostream>
#include <stdlib.h>
#include <time.h>
#define Letra_a 97
#define Letra_w 119
#define Letra_s 115
#define Letra_d 100
#define Letra_q 113
using namespace std;
char matriz[4][5]={{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '}};
int conta1=0,conta2=0;
bool ppop=true;
int entradaA,entradaB;
bool Gane(char mat[][5], char signo)
{
    for(char *i=mat[0]; i<mat[0]+20; i++)
    {
        if(*i==signo)
        {
            if(*(i+4)==signo && *(i+8)==signo && *(i+12)==signo)//  (\)
            {
                return true;
            }
            else if(*(i+6)==signo && *(i+12)==signo && *(i+18)==signo)// (/)
            {
                return true;
            }
            else if(*(i+1)==signo && *(i+2)==signo && *(i+3)==signo)// (--)
            {
                return true;
            }
            else if(*(i+5)==signo && *(i+10)==signo && *(i+15)==signo)// (|)
            {
                return true;
            }
        }
    }
    return false;
}
bool juego()
{
    char signo='1';
    for(char *i=matriz[0]; i<matriz[0]+20; i++)
    {
        if(*i==signo)
        {
            if(*(i+4)==signo && *(i+8)==signo && *(i+12)==signo)//  (\)
            {
                return true;
            }
            else if(*(i+6)==signo && *(i+12)==signo && *(i+18)==signo)// (/)
            {
                return true;
            }
            else if(*(i+1)==signo && *(i+2)==signo && *(i+3)==signo)// (--)
            {
                return true;
            }
            else if(*(i+5)==signo && *(i+10)==signo && *(i+15)==signo)// (|)
            {
                return true;
            }
        }
    }
    return false;
}
void imprimir(char mat[][5])
{
    char *i;
    for(i=matriz[0]; i<matriz[0]+20; i++)
    {
        cout<<"| "<<*i<<" |";
        if(i==matriz[0]+4 || i==matriz[1]+4 ||i==matriz[2]+4)
        {
            cout<<endl;
        }
    }
}
void Colocar(char mat[][5], int columna, char signo, int &refTurno)
{
    int *i= new int;
    for(*i=0; matriz[*i][columna-1]==' ' && *i<4; (*i)++)
    {}
    (*i)--;
    if(matriz[*i][columna-1]==' ')
    {
        refTurno++;
    }
    matriz[*i][columna-1]=signo;
    delete i;
}
void movimiento()
{
    int columna;
    int turno=0;
    bool gane=juego();
    char signo;
    while(!gane)
    {
        if(turno%2==0)
        {
            cout<<"\"X\""<<endl;
            signo='1';
        }
        else
        {
            cout<<"\"O\""<<endl;
            signo='2';
        }
        imprimir(matriz);
        cout<<"\ncolumna: ";
        cin>>columna;
        cout<<endl;
        if(columna>0 && columna<6)
        {
            Colocar(matriz,columna,signo,turno);
        }
        else
        {
            cout<<"solo hay 5 columnas"<<endl;
        }
        system("cls");
        gane=Gane(matriz,'X');

    }
    cout<<"GANaste "<<signo<<endl;
}
void Cuatro_Linea()
{
    int columna;
    int turno=0;
    bool gane=juego();
    char signo;
    while(!gane)
    {
        if(turno%2==0)
        {
            cout<<"\"1\""<<endl;
            signo='1';
        }
        else
        {
            cout<<"\"2\""<<endl;
            signo='2';
        }
        imprimir(matriz);
        cout<<"\neponga una columna: ";
        cin>>columna;
        cout<<endl;
        if(columna>0 && columna<6)
        {
            Colocar(matriz,columna,signo,turno);
        }
        else
        {
            cout<<"solo hay 5 columnas"<<endl;
        }
        system("cls");
        gane=Gane(matriz,'X');

    }
    cout<<"ganaste"<<signo<<endl;
}
int main() {
        Cuatro_Linea();
        movimiento();

}
