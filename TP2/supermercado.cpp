#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <stdlib.h>
//#include "dinheiro.h"
//#include "produto.h"
#include "gerenciadorprodutos.h"

using namespace std;

fstream file;
Produto produtos;

void ordena();
int compare(const void *a, const void *b);
void displayMenu();
//void cadastrar();
void listaP();
void printProduto(int codigo);
void enter();

int main(int argc, char **argv){

  //file.open("data.dat", ios::binary);
  ofstream teste("data.dat", ios::app | ios::binary);

  //checando se o arquivo data.dat foi aberto corretamente
  if(!teste.is_open()){
    cerr << "Erro ao abrir arquivo .dat" << endl;
    return -1;
  }

  teste.close();
  //file.close();

  system("clear"); //limpa o terminal para uma melhor visao

  if(argc != 2){
    cerr << "Erro ao executar programa, faltou um parametro: ./supermercado.exe <tamanhoMAX>" << endl;
    return 0;
  }

  int k = atoi(argv[1]);

  GerenciadorProdutos p(k);

  ordena(); //pega o arquivo e o ordena a partir dos codigos

  //displayMenu(); //imprime na tela o display de menu

  while(true){

    displayMenu(); //imprime na tela o display de menu
    //inicio do loop infinito para imprimir o display na tela e esperar
    //açao do usuario...
    int opcao;
    cout << "Digite a opcao: ";
    cin >> opcao;

    if(opcao == 1){
      //armazenar um produt
      if(p.getNumProdutosCadastrados()>=p.getTamanho()){
        cout << "Quantidade maxima de produtos excedida!" << endl;
        enter();
        system("clear");
        continue;
      }
      else {
        p.armazenaProduto();
        string enter1;
        cout << endl << "Pressione [Enter] para continuar";
        enter1 = cin.get();
        system("clear");
      }
    }

    else if(opcao == 2){
      //listar os produtos salvos no data.dat
      ordena();
      cout << endl;
      cout << "Qnt produtos cadastrados: " << p.getNumProdutosCadastrados() << endl;
      cout << "Qnt maxima de produtos: "<< p.getTamanho() << endl;
      listaP();
      enter();
      system("clear");
    }

    else if(opcao == 3){
      //deletar um produto q tenha o mermo codigo que o recebido como parametro
      int cod;
      cout << "Digite o codigo do produto que deseja ser removido: ";
      cin >> cod;
      p.removeProduto(cod);
      enter();
      system("clear");
    }

    else if(opcao == 4){
      //deletar todos os produtos de data.dat
      p.removeTodosProdutos();
      cout << endl << "Todos Produtos removidos!" << endl;
      enter();
      system("clear");
    }

    else if(opcao == 5) {
      //imprimir na tela um produto a partir de sua pesquisa por codigo
      int num;
      cout << "Digite o codigo do produto a ser consultado: ";
      cin >> num;
      printProduto(num);
      system("clear");
    }
    else if(opcao == 6){
      cout << "Obrigado!" << endl << endl;
      break;
    }

    //imprime display e recomeça o loop para operar denovo as opçoes
    //displayMenu();

  }

  return 0;
}

void enter(){
  //funcao apenas para o programa dar clear no terminal dps de o usuario
  //apertar a tecla enter
  //usei duas strings pois a primeira recebe o enter na entrada da opcao
  //e a segunda de fato q eh a do "pressione [enter]"
  string enter1, enter2;
  cout << endl << "Pressione [Enter] para continuar";
  enter1 = cin.get();
  enter2 = cin.get();
}

void ordena(){
  Produto *pOrdem; //array para armzenar infomarcoes dos produtos
  file.open("data.dat", ios::in); //abre arquivo
  file.seekg(0, ios::end);
  int n = file.tellg()/sizeof(Produto); //define a quantidade de produtos
  file.seekg(0, ios::beg); //reseta ponteiro para o inicio

  pOrdem = new Produto [n]; //aloca dinamicamente a array
  //salva na array os produtos que ja estavam no arquivo data.dat
  file.read(reinterpret_cast<char*>(pOrdem), sizeof(Produto)*n);

  file.close();

  //ordena esse array de produtos, a partir do codigo de cada um
  qsort(pOrdem, n, sizeof(Produto), compare);

  ofstream ofs;
  //limpa o arquivo .dat (abrindo com o msm nome e em branco)
  ofs.open("data.dat", ofstream::out | ofstream::trunc);
  //copia os dados da array pOrdem para o arquivo .dat
  ofs.write(reinterpret_cast<char*>(pOrdem), sizeof(Produto)*n);
  ofs.close();
  delete []pOrdem;
}

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
  cout << endl << "Produtos cadastrados: " << endl;
  file.seekg(0, ios::end);
  int tam = file.tellg();
  file.seekg(0, ios::beg);
  Produto *aux = new Produto [tam/sizeof(Produto)];
  file.read(reinterpret_cast<char*>(aux), sizeof(Produto)*(tam/sizeof(Produto)));
  for(int i=0; i<tam/sizeof(Produto); i++){
    if(aux[i].getCodigo()==codigo){
      aux[i].printP();
      enter();
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

void displayMenu(){
  //imprieme o display de usuario na tela
  cout << endl;
  cout << "===================================" << endl;
  cout << "|                                 |" << endl;
  cout << "| Menu Principal:                 |" << endl;
  cout << "| 1- Cadastrar produto            |" << endl;
  cout << "| 2- Listar produtos              |" << endl;
  cout << "| 3- Remover produto              |" << endl;
  cout << "| 4- Remover todos produtos       |" << endl;
  cout << "| 5- Consultar produto com codigo |" << endl;
  cout << "| 6- Sair                         |" << endl;
  cout << "|                                 |" << endl;
  cout << "===================================" << endl;
}
