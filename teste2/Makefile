all: supermercado.exe

supermercado.exe: dinheiro.o produto.o gerenciadorprodutos.o supermercado.o
	g++ supermercado.o dinheiro.o produto.o gerenciadorprodutos.o -o supermercado.exe

dinheiro.o: dinheiro.h dinheiro.cpp
	g++ -c dinheiro.cpp

produto.o: produto.h produto.cpp
	g++ -c produto.cpp

gerenciadorprodutos.o: gerenciadorprodutos.h gerenciadorprodutos.cpp
	g++ -c gerenciadorprodutos.cpp

supermercado.o: supermercado.cpp 
	g++ -c supermercado.cpp

limpa:
	rm -f *.exe *.o
