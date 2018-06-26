#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <stdlib.h>

using namespace std;

int main(){


  fstream entrada;
  entrada.open("teste.txt");
  if(!entrada.is_open()){
    cout << "toma no cu" << endl;
  }

  entrada.close();

  ofstream saida("saida.dat", ios::binary);

}
