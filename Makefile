all: compilar_objeto compilar_binario

compilar_objeto:
	gcc -c ./src/gerar_arquivo_main.c ./src/gerar_arquivo.c
	gcc -c ./src/ordenar_arquivo_main.c ./src/ordenar_arquivo.c

compilar_binario:
	gcc gerar_arquivo_main.o gerar_arquivo.o -o gerador -lm
	gcc ordenar_arquivo_main.o ordenar_arquivo.o -o ordenar -lm

gerar:
	./gerador 1GB.bin 1000
	./gerador 6GB.bin 6000

ordenar:
	./ordenar 1GB.bin out1GB.bin 100 10
	./ordenar 6GB.bin out6GB.bin 600 10

excluir:
	rm -f *.o *.out kfile*.bin
