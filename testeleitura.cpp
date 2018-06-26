#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(){

  ifstream entrada("entrada.txt");
  ofstream saida("entrada.txt", ios::app);

  while(true){
    char c = entrada.get();
    char a = putchar(toupper(c));
    //char a = c;
    saida << a;
    if(c == EOF) break;
  }
  cout << endl;


  return 0;
}
