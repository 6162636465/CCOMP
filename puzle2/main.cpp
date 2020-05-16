#include <iostream>
#include <stdlib.h>
#include <time.h>
#define Letra_a 97
#define Letra_w 119
#define Letra_s 115
#define Letra_d 100
#define Letra_q 113
using namespace std;
int conta1=0,conta2=0;
int a[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int b[4][4] ={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
bool ppop=true;
int reservadoA[16],reservadoB[16];
int entradaA,entradaB;
void encontrar(int x,int jugador)
{
    int contas1=0,contas2=0;
    int guardado1,guardado2;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++)
            {
            if(b[i][j]==x)
            {
                guardado1=i;
                guardado2=j;
            }
            }
    }
    for (int (*p)[4] = a;p<a+4;p++)
    {
    for(int *q=*p;q<*p+4;q++)
        {
            if(contas1==guardado1 and contas2==guardado2)
                {
                    if(jugador==1)
                        {
                            *q=1;
                        }
                    else if(jugador==2)
                        {
                            *q=2;
                        }
                }
            contas2=contas2+1;
            cout<<contas2<<",";
        }
        contas1=contas1+1;
    }

}
void movimiento()
{
    int f,w;
    int axa=1,exa=2;
        cout<<"jugador 1 ponga un numero"<<endl;
		cin>>f;
		cout<<"jugador 2 ponga un numero"<<endl;
		cin>>w;
		//agregar a la lista1
		reservadoA[conta1]=f;
		//agregar a la lista2
		reservadoB[conta2]=w;
		 if(w==322)
            {
                ppop=false;
            }
    system("cls");
    for(int s=0;s<16;s++)
        {
            cout<<reservadoA[s];
        }
    cout<<endl;
    for(int j=0;j<16;j++)
        {
            cout<<reservadoB[j];
        }
    cout<<endl;
    conta1=conta1+1;
    conta2=conta2+1;
    encontrar(f,axa);
    encontrar(w,exa);
}
int main() {
  while(ppop==true){
    cout<<"|1 |2 |3 |4 |"<< endl;
    cout<<"|5 |6 |7 |8 |"<< endl;
    cout<<"|9 |10|11|12|"<< endl;
    cout<<"|13|14|15|16|"<< endl;
    cout<<"jugador 1 ponga la variable que elijio"<<endl;
  for (int (*p)[4] = a;p<a+4;p++)
  {
    for(int *q=*p;q<*p+4;q++)
        {
            cout<<*q<<" ";
        }
    cout<<endl;
  }
  movimiento();
  }
}
