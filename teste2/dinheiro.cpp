#include <iostream>
#include <iomanip>
#include "dinheiro.h"

using namespace std;

Dinheiro::Dinheiro(){
  //por padrao todo dinheiro é definido como R$00,00
  r = 0;
  c = 0;
}

Dinheiro::Dinheiro(int r,  int c){
  //define as variaveis private do objeto
  this->r = r;
  while(c > 99){
    c-=100;
    this->r++;
  }
  this->c = c;
}

int Dinheiro::getReais() const{
  return this->r;
}

int Dinheiro::getCentavos() const{
  return this->c;
}

void Dinheiro::setReais(int valor){
  r = valor;
}
void Dinheiro::setCentavos(int valor){
  //checa o tamanho dos centavos para guardar em cada variavel valores
  //aceitaveis (centavo > 99, aumenta o real)
  while(valor > 99){
    valor-=100;
    r++;
  }
  c = valor;
}

ostream& operator<<(ostream& os, const Dinheiro& d){
  //sobrecarga do operador << para dar cout em um Dinheiro
  //tela: R$00,00
  if(d.getCentavos()<10){
    os << "R$" << d.getReais() << ",";
    //usei setfill para que sempre tenha duas casas o real
    os << setfill('0') << setw(2) << d.getCentavos();
  }
   else os << "R$" << d.getReais() << "," << d.getCentavos();
  return os;
}

Dinheiro Dinheiro::operator=( Dinheiro d){
  if(this->r == d.r && this->c == d.c) return *this;
  r = d.r;
  c = d.c;
  return *this;
}

Dinheiro Dinheiro::operator+(const Dinheiro d){
  Dinheiro aux;
  aux.setReais(this->r + d.r);
  aux.setCentavos(this->c + d.c);
  return aux;
}

Dinheiro Dinheiro::operator-(const Dinheiro d){
  Dinheiro aux;
  if(this->r - d.r < 0){
    aux.r = 0;
    aux.c = 0;
  }
  else{
    int x = this->r, y = this->c;
    if(this->c - d.c < 0){
      y += 100;
      x -= 1;
      y -= d.c;
      x -= d.r;
    }
    else{
      x -= d.r;
      y -= d.c;
    }
    aux.setReais(x);
    aux.setCentavos(y);
  }
  return aux;
}

Dinheiro Dinheiro::operator-=(const Dinheiro d){

  if(this->r - d.r < 0){
    this->r = 0;
    this->c = 0;
  }
  else{
    if(this->c - d.c < 0){
      this->c += 100;
      this->r -= 1;
      this->c -= d.c;
      this->r -= d.r;
    }
    else{
      this->r -= d.r;
      this->c -= d.c;
    }
  }
  return *this;
}

Dinheiro Dinheiro::operator+=(const Dinheiro d){
  this->r = this->r + d.r;
  this->c = this->c + d.c;
  return *this;
}

Dinheiro Dinheiro::operator*(const double valor){
  //se a multiplicacao der um valor negativo o dinheiro é definido como 0
  if((r*valor)+(c*valor)/100 < 0){
    Dinheiro dinheiro(0,0);
    return dinheiro;
  }
  else{
    Dinheiro dinheiro(r*valor, c*valor);
    return dinheiro;
  }
}

/*double Dinheiro::operator*(Dinheiro d){
  //se a multiplicacao der um valor negativo o dinheiro é definido como 0
  if((r*valor)+(c*valor)/100 < 0){
    Dinheiro dinheiro(0,0);
    return dinheiro;
  }
  else{
    Dinheiro dinheiro(r*valor, c*valor);
    return dinheiro;
  }
}*/
