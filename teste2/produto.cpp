#include <iostream>
#include <iomanip>
#include "produto.h"

using namespace std;

Produto::Produto(){
  //definindo como nulo um produto inicializado
  codigo = -1;
  setNomeBlank();
  margemLucro = 0;
  nome[0] = '\0';
  // precoCusto.setReais(0);
  // precoCusto.setCentavos(0);
  // impostoMunicipal.setReais(0);
  // impostoMunicipal.setCentavos(0);
  // precoVenda.setReais(0);
  // precoVenda.setCentavos(0);
}

Produto::Produto(int codigo, char *nome, Dinheiro precoCusto, double margemLucro, Dinheiro impostoMunicipal){
  setCodigo(codigo);
  setNome(nome);
  setPrecoCusto(precoCusto.getReais(), precoCusto.getCentavos());
  setLucro(margemLucro);
  setImposto(impostoMunicipal.getReais(), impostoMunicipal.getCentavos());
}

Produto::~Produto(){
  setNomeBlank();
}

Dinheiro Produto::getPrecoCusto(){
  return precoCusto;
}

Dinheiro Produto::getPrecoVenda(){
  precoVenda = precoCusto + (precoCusto*(margemLucro)*0.01) + impostoMunicipal;
  return precoVenda;
}

int Produto::getCodigo(){
  return codigo;
}

const char * Produto::getNome(){
  return nome;
}

void Produto::setCodigo(int codigo){
  this->codigo = codigo;
}

void Produto::setNome(char *nome){
  strcpy(this->nome, nome);
}

void Produto::setNomeBlank(){
  strcpy(this->nome, "\0");
}

void Produto::setLucro(int lucro){
  margemLucro = lucro;
}

void Produto::setPrecoCusto(int r, int c){
  precoCusto.setReais(r);
  precoCusto.setCentavos(c);
  precoVenda = precoCusto + (precoCusto*(margemLucro)*0.01) + impostoMunicipal;
}

void Produto::setImposto(int r, int c){
  impostoMunicipal.setReais(r);
  impostoMunicipal.setCentavos(c);
  precoVenda = precoCusto + (precoCusto*(margemLucro)*0.01) + impostoMunicipal;
}

void Produto::setPrecoVenda(){
  precoVenda = precoCusto + (precoCusto*(margemLucro)*0.01) + impostoMunicipal;
}

Produto & Produto::operator=(Produto p){
  //salva as informacoes de um produto e as atribui a outro
  this->codigo = p.codigo;
  this->margemLucro = p.margemLucro;
  this->precoCusto = p.precoCusto;
  this->impostoMunicipal = p.impostoMunicipal;
  this->precoVenda = p.precoVenda;
  strcpy(this->nome, p.nome);
  return *this;
}

void Produto::cadastrarP(){
  //funcao completa para cadastrar um produtos
  //pede os dados
  int real, centavo, a, b;
  cout << "Digite as informacoes do produto: " << endl;
  cout << "Codigo: ";
  cin >> codigo;
  cout << endl;
  cout << "Nome: ";
  cin >> nome;
  cout << endl;
  cout << "Preco de custo(REAL CENTAVO): ";
  cin >> real >> centavo;
  cout << endl;
  precoCusto.setReais(real);
  precoCusto.setCentavos(centavo);
  cout << "Margem de Lucro(%): ";
  cin >> margemLucro;
  cout << endl;
  cout << "Imposto Municipal (REAL CENTAVO): ";
  cin >> a >> b;
  cout << endl;
  impostoMunicipal.setReais(a);
  impostoMunicipal.setCentavos(b);
  setPrecoVenda();
}

void Produto::printP(){
  //imprime as informacoes do produto
  cout << "\nCodigo produto: " << codigo << endl;
  cout << "Nome produto: " << nome << endl;
  cout << "Preco de custo: " << precoCusto << endl;
  cout << "Preco de venda: " << precoVenda << endl;
  cout << "Imposto municipal: " << impostoMunicipal << endl;
}

ostream& operator<<(ostream& os, const Produto& p){
  os << "\nCodigo produto: " << p.codigo << endl;
  os << "Nome produto: " << p.nome << endl;
  os << "Preco de custo: " << p.precoCusto << endl;
  os << "Preco de venda: " << p.precoVenda << endl;
  os << "Imposto municipal: " << p.impostoMunicipal << endl;
  os << "-----------------------------------" << endl;

  return os;
}
