all: compilar_objeto compilar_binario excluir

compilar_objeto:
	gcc -c ./src/gerar_arquivo_main.c ./src/gerar_arquivo.c

compilar_binario:
	gcc ./src/gerar_arquivo_main.o ./src/gerar_arquivo.o -o gerador

gerar:
	./gerador arquivo6MB.bin 6

excluir:
	rm -f *.o

ordenar:
