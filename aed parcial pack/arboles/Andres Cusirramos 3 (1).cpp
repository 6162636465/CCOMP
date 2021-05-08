#include<iostream>

using namespace std;


void Ordenar(int *arr, int tam ){

      int aux;
     
    int medio=tam/2;
    int *p =arr+medio;

       for(int *i=arr+(tam-1);i>arr;i--){
           for(int *j=arr;j<i;j++){
                  if(*p>*(j+1)){
                  aux = *j;
                  *j = *(j+1);
                  *(j+1)= aux;
               }
               p++;
           }
           p++;
       }
}
    
    
    

void print(int *arr, int tam){
    for(int *i=arr;i<arr+tam;i++){
        cout<<*i<<",";
    }
    cout<<endl;
}

int main(){
    int arbol[19]={ 90 ,82, 74, 71 ,66 ,62 ,58 ,51, 42 ,38 ,33, 30, 25, 22, 17, 12, 9, 6, 2};
    print(arbol,19);
    Ordenar(arbol, 19);
    print(arbol, 19);
}
