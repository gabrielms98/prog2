#include <iostream>
#include "produto.h"

using namespace std;

#ifndef GERENCIADORPRODUTOS_H
#define GERENCIADORPRODUTOS_H

class GerenciadorProdutos{
private:
  Produto *produtos;
  static int contador;
  static int tamanho;

public:

  GerenciadorProdutos();
  GerenciadorProdutos(int maxProdutos);
  ~GerenciadorProdutos();

  void armazenaProduto();
  void removeProduto(int codigo);
  void removeTodosProdutos();
  //void setProdutoNull(int codigo);

  Produto getProduto(int codigo);
  Produto getIesimoProduto(int i);

  int getNumProdutosCadastrados() const;
  int getTamanho() const;
  void printAllProdutos() const;

  friend ostream& operator<<(ostream& os, const Produto& p);

};

#endif
