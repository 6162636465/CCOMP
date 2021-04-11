#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;
#define MAX 1500
double A[MAX][MAX], x[MAX], y[MAX];
int mivector[10];
/*
void swap(int* mivecto,int i,int j)
{
	int tmp = *(mivecto + i);
	*(mivecto + i) = *(mivecto + j);
	*(mivecto + j) = tmp; 
	i++;
	j--;
}
*/
void llenarvector(int cantidad) {
	for (int i = 0; i < cantidad; i++)
	{

		cout<<"Entre el elemento elemento["<<i+1<<"]["<<i+1<<"] del vector"<<endl;
		cin >> mivector[i];
	}
	}
void llenarvectorrandon(int cantidad) {
	srand(time(nullptr));
for (size_t j = 0; j < cantidad; ++j)
	{
		mivector[j] = rand() % cantidad;
	}
}
void imprimirvector(int cantidad)
{
		for (int i = 0; i < cantidad; i++)
		{
			cout<<mivector[i]<<" ";
		}
}
void quicksort(int* mivecto, int primero, int ultimo)
{
	int i, j, central;
	int pivote;
	central = (primero + ultimo) / 2;
	i = primero ;
	pivote = *(mivecto + central);
	primero; *(mivecto + central);
	j = ultimo;
	do {
		while (*(mivecto + i) < pivote)  i++;
		while (*(mivecto + j) > pivote)  j--;
		if (i <= j)
		{
		//wap(mivecto,i,j);
			int tmp = *(mivecto + i);
			*(mivecto + i) = *(mivecto + j);
			*(mivecto + j) = tmp;
			i++;
			j--;
		}
	}
	while (i <= j);
	if (primero < j)
		quicksort(mivector, primero, j);/* mismo proceso proceso con sublista sublista izqda */
	if (i < ultimo)
		quicksort(mivector, i, ultimo); /* mismo proceso proceso con sublista sublista drcha */
}
int main() 
	{
	int cantidad = 0,condicion;
	cout << "desea auto llenar la lista ponga 1(SI) u 0(NO)";
	cin >> condicion;
	if (condicion == 1)
	{
		cout << "coloque la cantidad de elementos a llenar" << endl;
		cin >> cantidad;
		llenarvectorrandon(cantidad);
		cout << "El vector es :  " << endl;
		imprimirvector(cantidad);
		quicksort(mivector, 0, cantidad-1);
		cout << "El vector ordenado ordenado es : " << endl;
		imprimirvector(cantidad);
		system("pause");
	}
	else
	{
		cout << "coloque la cantidad de elementos a llenar" << endl;
		cin >> cantidad;
		llenarvector(cantidad);
		cout << "El vector es :  " << endl;
		imprimirvector(cantidad);
		quicksort(mivector, 0, cantidad-1);
		cout << "El vector ordenado ordenado es : " << endl;
		imprimirvector(cantidad);
		system("pause");

	}
	system("pause");
	}