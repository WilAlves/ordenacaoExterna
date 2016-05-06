all: compilar_objeto compilar_binario

compilar_objeto:
	gcc -c ./src/gerar_arquivo_main.c ./src/gerar_arquivo.c
	gcc -c ./src/ordenar_arquivo_main.c ./src/ordenar_arquivo.c
	gcc -c ./src/ler_arquivo_gerado.c

compilar_binario:
	gcc gerar_arquivo_main.o gerar_arquivo.o -o gerador -lm
	gcc ordenar_arquivo_main.o ordenar_arquivo.o -o ordenar -lm
	gcc ler_arquivo_gerado.o -o ler -lm

gerar:
	./gerador 1GB.bin 1000

order:
	./ordenar 1GB.bin out_1GB.bin 100 10

ler_ordenado:
	./ler out_1GB.bin > ordenado.txt

ler_desordenado:
	./ler 1GB.bin > desordenado.txt
