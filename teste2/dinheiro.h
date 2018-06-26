#include <iostream>

using namespace std;

//se n tiver sido definida uma classe dinheiro.h, irá definir
#ifndef DINHEIRO_H
#define DINHEIRO_H

class Dinheiro{
private:
  int r, c; //real e centavo

public:
  Dinheiro(); //construtor padrao
  Dinheiro(int r, int c);

  int getReais() const;
  int getCentavos() const;

  void setReais(int valor);
  void setCentavos(int valor);

  Dinheiro operator=(const Dinheiro d);
  Dinheiro operator+(const Dinheiro d);
  Dinheiro operator-(const Dinheiro d);
  Dinheiro operator+=(const Dinheiro d);
  Dinheiro operator*(const double valor);
  double operator*(Dinheiro d);
  Dinheiro operator-=(const Dinheiro d);
  friend ostream& operator<<(ostream& os, const Dinheiro& d);
};

#endif
