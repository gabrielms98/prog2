//aprendendo a usar backtracking
//permutando uma sequencia

#include <iostream>

using namespace std;

void permuta(int *arr, int inf, int sup);
void troca(int &a, int &b);

int main(){

  int n;
  cin >> n;

  int *arr = new int [n];

  for(int i=0; i<n; i++){
    cin >> arr[i];
  }

  int tam = sizeof(arr)/sizeof(int);

  permuta(arr, 0, n-1);

  return 0;
}
void troca(int vetor[], int i, int j){
  int aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}

void permuta(int *arr, int inf, int sup){
  if(inf == sup){
    for(int i=0; i<=sup; i++){
      cout << arr[i];
    }
    cout << endl;
  } else{
    for(int j=inf; j<=sup; j++){
      troca(arr, inf, j);
      permuta(arr, inf+1, sup);
      troca(arr, inf, j); //backtracking
    }
  }
}
