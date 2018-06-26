#include <iostream>
#include <fstream>
#include "gerenciadorprodutos.h"
#include "produto.h"

using namespace std;

//variaveis globais para q as funçoes utilizem
fstream fileg;
Produto produto;

int GerenciadorProdutos::contador = 0;
int GerenciadorProdutos::tamanho = 0;

GerenciadorProdutos::GerenciadorProdutos(){
  produtos = new Produto [1];
  //contador++;
  tamanho = 1; //qnd um produto é criado adiciona em 1 o contador de produtos
}

GerenciadorProdutos::GerenciadorProdutos(int maxProdutos){
  //maxProdutos = quantidade maxima de produtos q podem ter no arquivo data.dat
  produtos = new Produto [maxProdutos];
  tamanho = maxProdutos;
}

GerenciadorProdutos::~GerenciadorProdutos(){
  delete []produtos;
  contador--;
}

void GerenciadorProdutos::armazenaProduto(){
  //se o numero de produto ja estiver no limite, funcao retorna e nao faz nada
  if(contador>=getTamanho() && contador!=0){
    cerr << "Limite de produtos atingido!" << endl;
    return;
  }
  else {
    //abre data.dat (com ios::app para concatenar) chama funcao para cadastrar produto
    //escreve tais dados no final do arquivo
    fileg.open("data.dat", ios::out | ios::app);
    produto.cadastrarP();
    // (char*)&produto, sizeof(Produto)
    fileg.write((char*)&produto, sizeof(Produto));
    fileg.close();
    cout << "Produto foi armazenado com sucesso!" << endl;
    getchar();
    contador++;
  }
}

void GerenciadorProdutos::removeProduto(int codigo){
  //procura pela lista de produtos em data.dat o produto q tem o mesmo codigo q o de entrada
  //se encontrado esse produto é deletado
  fileg.open("data.dat", ios::in | ios::out);
  fstream f2;
  f2.open("temp.dat", ios::out);
  // fileg.read(reinterpret_cast<char*>(produto), sizeof(Produto)) =>  invalid cast from type 'Produto' to type 'char*'
  while(fileg.read((char*)&produto, sizeof(Produto))){
    if(produto.getCodigo() != codigo){
      f2.write((char*)&produto, sizeof(Produto));
    }
  }
  f2.close();
  fileg.close();
  remove("data.dat");
  rename("temp.dat", "data.dat");
  cout << "Produto removido..." << endl;
  contador--;
}

void GerenciadorProdutos::removeTodosProdutos(){
  //abre o arquivo data.dat em branco(trunc), logo apaga tudo q tem nele
  ofstream ofs;
  ofs.open("data.dat", ofstream::out | ofstream::trunc);
  ofs.close();
}

Produto GerenciadorProdutos::getProduto(int codigo){
  //le o arquivo file
  fileg.open("data.dat", ios::in);
  fileg.seekg(0, ios::end);
  int tam = fileg.tellg();
  fileg.seekg(0, ios::beg);
  Produto *aux = new Produto [tam/sizeof(Produto)];
  fileg.read(reinterpret_cast<char*>(aux), sizeof(Produto)*(tam/sizeof(Produto)));
  for(int i=0; i<tam/sizeof(Produto); i++){
    if(aux[i].getCodigo() == codigo){
      fileg.close();
      cout << "Produto:" << endl;
      cout << "-----------------------------------" << endl;
      return aux[i];
    }
  }
}

Produto GerenciadorProdutos::getIesimoProduto(int i){
  fileg.open("data.dat", ios::in);
  cout << endl << "Todos Produtos..." << endl;
  fileg.seekg(0, ios::end);
  int tam = fileg.tellg();
  fileg.seekg(0, ios::beg);
  Produto *aux = new Produto [tam/sizeof(Produto)];
  fileg.read(reinterpret_cast<char*>(aux), sizeof(Produto)*(tam/sizeof(Produto)));
  fileg.close();
  return aux[i];
}

int GerenciadorProdutos::getNumProdutosCadastrados() const{
  fileg.open("data.dat", ios::in);
  fileg.seekg(0, ios::end);
  int aux = fileg.tellg()/sizeof(Produto);
  contador = aux;
  fileg.close();
  return contador;
}

int GerenciadorProdutos::getTamanho() const{
  return tamanho;
}

ostream& operator<<(ostream& os, const GerenciadorProdutos& g){
  os << "Quantidade de Produtos: " << g.getNumProdutosCadastrados() << endl;
  os << "Tamanho maximo: " << g.getTamanho() << endl;

  g.printAllProdutos();

  return os;
}

void GerenciadorProdutos::printAllProdutos() const{
  for(int i=0; i<contador; i++){
    produtos[i].printP();
  }
}
