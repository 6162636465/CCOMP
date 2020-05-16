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
int **arr;
bool ppp=true;
void Matriz()
 {
  arr = new int*[4];
  for(int i=0;i<4;i++)
     arr[i] = new int[4];

  //recorrido usando punteros y aritmetica de puntero
  int cont=0,epalda=0;
  srand(time(NULL));
  int lista[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for(int **i=arr;i<arr+4;i++,a++){
        int num;
        for(int *j=*i;j<*i+4;j++,b++){
            num = 10 + rand() % (21 - 1);
            lista[cont]=num;
            int conta=0;
            for(int k=0;k<16;k++)
                {
                    if(lista[k]==num)
                        {
                            conta++;
                        }
                }
                if(conta>1)
                    {
                        *j=epalda;
                        epalda++;
                    }
                else{
                        cont++;
                        *j=num;
                }
     }
  }
}
void imprimirMatriz()
{
for(int i=0;i<4;i++)
  {
     for(int j=0;j<4;j++){
            //ordenar la matriz
        if(arr[i][j]>=10){
           cout << arr[i][j]<<"  ";
        }
        else if(arr[i][j]<10){
        cout << arr[i][j]<<"   ";
        }
     }
     cout<<endl;
  }
}
void inputt()
{
    int **tempp,x,y;
    char f;
    for(int w=0;w<4;w++)
    {
        for(int p=0;p<4;p++)
            {
                if(arr[w][p]==0)
                {
                    cout<<w<<","<<p<<endl;
                    x=w;
                    y=p;
                }
            }
    }

    cout<<"mueva el 0 y ponga q para salir del juego"<<endl;
		cin>>f;
		if (f==Letra_w)
		{
		    swap(**arr,**(arr+1));
		}
		if(f==Letra_a)
		{
		    swap(*arr,*(arr-1));
		}
		if(f==Letra_s)
		{
		    swap(**arr,**(arr+4));
		}
		if(f==Letra_d)
		{
		    swap(*arr,*(arr-1));
		}
		else if(f==Letra_q)
        {
            ppp=false;
        }
    system("cls");
}
int main()
{
    Matriz();
while (ppp==true){
    imprimirMatriz();
    inputt();
}
cout<<"fin del juego"<<endl;
}
