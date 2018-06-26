#include <iostream>
#include <cstring>
#include "dinheiro.h"

using namespace std;

#ifndef PRODUTO_H
#define PRODUTO_H

class Produto{
private:
  int codigo;
  double margemLucro;
  Dinheiro precoCusto, impostoMunicipal, precoVenda;
  char nome[49];

public:
  Produto();
  Produto(int codigo, char *nome, Dinheiro precoCusto, double margemLucro, Dinheiro impostoMunicipal);
  ~Produto();

  Dinheiro getPrecoCusto();
  Dinheiro getPrecoVenda();

  int getCodigo();
  const char *getNome();

  void setCodigo(int codigo);
  void setNome(char *nome);
  void setNomeBlank();
  void setLucro(int lucro);
  void setPrecoCusto(int r, int c);
  void setImposto(int r, int c);
  void setPrecoVenda();

  void cadastrarP();
  void printP();

  Produto & operator=(Produto p);
  friend ostream& operator<<(ostream& os, const Produto& p);
};

#endif
