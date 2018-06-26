#include <iostream>
#include <fstream>

using namespace std;

int main(){

  ofstream fout("teste.txt");
  ifstream fin("entrada.txt");

  fin.seekg(0, ios::end);
  int tam = fin.tellg();
  //fin.seekg(tam-1, ios::beg);

  for(int i=tam-1; i>=0; i--){
    fin.seekg(i, ios::beg);
    char c = fin.get();
    fout << c;
    //fin.seekg(i, ios::beg);
  }

  fin.close();
  fout.close();


  return 0;

}
