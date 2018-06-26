#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cstring>

using namespace std;

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
    os << setfill('0') << setw(2) << d.getCentavos();
  }
   else os << "R$" << d.getReais() << "," << d.getCentavos();
  return os;
}

Dinheiro Dinheiro::operator=( Dinheiro d){
  r = d.r;
  c = d.c;
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

//variaveis globais para q as funçoes utilizem
fstream file;
Produto produto;

Produto::Produto(){
  //definindo como nulo um produto inicializado
  codigo = 0;
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
  void setProdutoNull(int codigo);

  Produto getProduto(int codigo);
  Produto getIesimoProduto(int i);
  void printAllProdutos() const;

  int getNumProdutosCadastrados() const;
  int getTamanho() const;

  friend ostream& operator<<(ostream& os, const Produto& p);

};

int GerenciadorProdutos::contador = 0;
int GerenciadorProdutos::tamanho = 0;

GerenciadorProdutos::GerenciadorProdutos(){
  produtos = new Produto [1];
  contador++;
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
  if(contador>=getTamanho()){
    cerr << "Limite de produtos atingido!" << endl;
    return;
  }
  else {
    //abre data.dat (com ios::app para concatenar) chama funcao para cadastrar produto
    //escreve tais dados no final do arquivo
    file.open("data.dat", ios::out | ios::app);
    produto.cadastrarP();
    // (char*)&produto, sizeof(Produto)
    file.write((char*)&produto, sizeof(Produto));
    file.close();
    cout << "Produto foi armazenado com sucesso!" << endl;
    getchar();
    contador++;
  }
}

void GerenciadorProdutos::removeProduto(int codigo){
  //procura pela lista de produtos em data.dat o produto q tem o mesmo codigo q o de entrada
  //se encontrado esse produto é deletado
  file.open("data.dat", ios::in | ios::out);
  fstream f2;
  f2.open("temp.dat", ios::out);
  // file.read(reinterpret_cast<char*>(produto), sizeof(Produto)) =>  invalid cast from type 'Produto' to type 'char*'
  while(file.read((char*)&produto, sizeof(Produto))){
    if(produto.getCodigo() != codigo){
      f2.write((char*)&produto, sizeof(Produto));
    }
  }
  f2.close();
  file.close();
  remove("data.dat");
  rename("temp.dat", "data.dat");
  cout << "Produto removido..." << endl;
  contador--;
}

void GerenciadorProdutos::removeTodosProdutos(){
  ofstream ofs;
  ofs.open("data.dat", ofstream::out | ofstream::trunc);
  ofs.close();
}

Produto GerenciadorProdutos::getProduto(int codigo){
  file.open("data.dat", ios::in);
  file.seekg(0, ios::end);
  int tam = file.tellg();
  file.seekg(0, ios::beg);
  Produto *aux = new Produto [tam/sizeof(Produto)];
  file.read(reinterpret_cast<char*>(aux), sizeof(Produto)*(tam/sizeof(Produto)));
  for(int i=0; i<tam/sizeof(Produto); i++){
    if(aux[i].getCodigo() == codigo){
      file.close();
      cout << "Produto:" << endl;
      cout << "-----------------------------------" << endl;
      return aux[i];
    }
  }
}

Produto GerenciadorProdutos::getIesimoProduto(int i){
  file.open("data.dat", ios::in);
  cout << endl << "Todos Produtos..." << endl;
  file.seekg(0, ios::end);
  int tam = file.tellg();
  file.seekg(0, ios::beg);
  Produto *aux = new Produto [tam/sizeof(Produto)];
  file.read(reinterpret_cast<char*>(aux), sizeof(Produto)*(tam/sizeof(Produto)));
  file.close();
  return aux[i];
}

int GerenciadorProdutos::getNumProdutosCadastrados() const{
  file.open("data.dat", ios::in);
  file.seekg(0, ios::end);
  int aux = file.tellg()/sizeof(Produto);
  contador = aux;
  file.close();
  return contador;
}

int GerenciadorProdutos::getTamanho() const{
  return tamanho;
}

void GerenciadorProdutos::setProdutoNull(int codigo){
  for(int i = 0; i < getTamanho(); i++){
    if(produtos[i].getCodigo() == codigo){

    }
  }
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

Produto produtos;
GerenciadorProdutos p;

void listaP(){
  //TESTAR SE ARQUIVO TEM PELO MENOS 1 DADO
  //enquanto o arquivo ainda estiver sendo lido, chama
  //a funcao printP para imprimir as informacoes de cada produto
  file.open("data.dat", ios::in);
  cout << endl << "Produtos cadastrados: " << endl;
  file.seekg(0, ios::end);
  int tam = file.tellg();
  file.seekg(0, ios::beg);
  Produto *aux = new Produto [tam/sizeof(Produto)];
  file.read(reinterpret_cast<char*>(aux), sizeof(Produto)*(tam/sizeof(Produto)));
  for(int i=0; i<tam/sizeof(Produto); i++){
    cout << aux[i];
    cout << "-----------------------------------" << endl;
  }
  string enter;
  cout << "Pressione [Enter] para continuar";
  enter = cin.get();
  file.close();
  delete []aux;
}

void printProduto(int codigo){
  //NAO UTILIZAR COM DATA.DAT VAZIO
  //faz uma busca no arquivo data.dat (a partir do while) e procura por um
  //produto q tenha o codigo igual ao recebido como parametro...
  //imprime esse produto na tela se achar, se nao imprime msg de erro
  bool achou = false;
  file.open("data.dat", ios::in);
  while(file.read((char*)&produtos, sizeof(Produto))){
    if(produtos.getCodigo()==codigo){
      produtos.printP();
      achou = true;
    }
  }
  file.close();
  if(achou == false){
    cout << "Produto não encontrado..." << endl;
    getchar();
  }
}

int compare(const void *a, const void *b){
  //funcao compare usada pelo qsort
  //se o codigo de um produto for maior q outro retorna 1 ou -1
  //para a funcao qsort ordenar o array
  Produto v1 = *((Produto *)a);
  Produto v2 = *((Produto *)b);

  if(v1.getCodigo() > v2.getCodigo()) return 1;
  else return -1;
}

int main(){

  cout << "DINHEIRO TESTE" << endl;

  Dinheiro p;
  Dinheiro d[11];

  for(int i=0; i<11; i++){
    d[i].setReais(i);
    d[i].setCentavos(i*10);
  }

  cout << endl;

  cout << "p : " << p << endl;

  for(int j=0; j<11; j++){
    cout << "d" << j+1 << " : " << d[j] << endl;
  }

  d[0] = d[9];
  cout << "d1 = d10 : " << d[0] << endl;  //ok
  cout << "d2 + d3 = " << d[1] + d[2] << endl; //ok

  cout << d[2] << " + " << d[4] << endl;
  d[2]+=d[4]; //ok
  cout << "d3+=d5, d3 = " << d[2] << endl;

  cout << "d10 - d2" << endl; //ok
  cout << d[9] << " - " << d[1] << " = " << d[9]-d[1] << endl;
  cout << "d11 - d10 : " << d[10] << " - " << d[9] << " = "<< d[10]-d[9] << endl;

  cout << "d2 - d10" << " = " << d[1] - d[9] << endl;

  d[10]-=d[9];
  cout << "d11-=d10 : " << d[10] << endl;

  cout << "d3 * 2 = " << d[2]*2 << endl; //ok

  cout << endl << "==============================" << endl ;
  cout << "PRODUTOS TESTE" << endl;

  Produto prod;
  Produto cria;

  cout << "prod : " << prod << endl;

  /*char nome[49];
  cout << "Digite o nome: ";
  cin >> nome;
  cout << endl;
  prod.setNome(nome);
  cout << "prod, novo nome : " << prod.getNome() << endl;
  //cout << "prod, set nome : " << prod.setNome('prod') << endl;
  prod.setNomeBlank();
  cout << "prod, nome blank : " << prod.getNome() << endl;
  prod.setLucro(10);
  prod.setPrecoCusto(10, 99);
  prod.setImposto(1, 25);

  cout << prod << endl;

  cria.cadastrarP();

  cout << cria << endl;

  prod = cria;

  cout << prod << endl;
*/
  cout << endl << "==============================" << endl ;
  cout << "GERENCIADOR DE PRODUTOS" << endl;

  GerenciadorProdutos g(5);

  cout << g.getNumProdutosCadastrados() << " " << g.getTamanho() << endl;
  //cout << g << endl;

  // g.armazenaProduto();
  // g.armazenaProduto();
  // g.armazenaProduto();

  //Abrindo o arquivo e ordenando por codigo os produtos...
  Produto *pOrdem;
  file.open("data.dat", ios::binary);
  if(!file.is_open()){
    cerr << "Erro ao abrir arquivo .dat" << endl;
    return -1;
  }
  file.seekg(0, ios::end);
  int n = file.tellg()/sizeof(Produto);
  file.seekg(0, ios::beg);
  //file.read(reinterpret_cast<char*>(&n), sizeof(int));

  //fstream f2;
  //f2.open("temp.dat", ios::in | ios::out); //abre um arquivo temporario auxiliar
  pOrdem = new Produto [n];
  //salva na array os produtos que ja estavam no arquivo data.dat
  file.read(reinterpret_cast<char*>(pOrdem), sizeof(Produto)*n);
  for(int i=0; i<n; i++){
    cout << pOrdem[i];
  }

  file.close();


  //ordena esse array de produtos, a partir do codigo de cada um
  qsort(pOrdem, n, sizeof(Produto), compare);

  for(int i=0; i<n; i++){
    cout << pOrdem[i];
  }
  ofstream ofs;
  ofs.open("data.dat", ofstream::out | ofstream::trunc);
  //escreve no arquivo temporario a array ja ordenada
  ofs.write(reinterpret_cast<char*>(pOrdem), sizeof(Produto)*n);
  //remove("data.dat"); //deleta data.dat
  //rename("temp.dat", "data.dat"); //array temp troca de nome e vira principal
  ofs.close();

  listaP();
  /*
  //printProduto(5);
  //listaP();
  //g.removeTodosProdutos();
  //listaP();

  //cout << g.getIesimoProduto(1) << endl;
  //cout << g.getNumProdutosCadastrados() << endl;

  g.armazenaProduto();
  g.armazenaProduto();
  g.armazenaProduto();

  cout << g.getNumProdutosCadastrados() << endl;
  cout << g.getProduto(1) << endl;

  g.removeProduto(2);
  listaP();

  */








  return 0;
}
