all: compilar_objeto compilar_binario

compilar_objeto:
	gcc -c ./src/gerar_arquivo_main.c ./src/gerar_arquivo.c
	gcc -c ./src/ordenar_arquivo_main.c ./src/ordenar_arquivo.c

compilar_binario:
	gcc gerar_arquivo_main.o gerar_arquivo.o -o gerador -lm
	gcc ordenar_arquivo_main.o ordenar_arquivo.o -o ordenar -lm

gerar:
	./gerador 1MB.bin 1
	./gerador 10MB.bin 10
	./gerador 100MB.bin 100
	./gerador 1GB.bin 1000
	./gerador 3GB.bin 3000
	./gerador 6GB.bin 6000

ordenar:
# Tamanhos diferentes, mesma memoria e mesmo K
	./ordenar 1MB.bin out1MB.bin 1 10
	./ordenar 10MB.bin out10MB.bin 1 10
	./ordenar 100MB.bin out100MB.bin 1 10
	./ordenar 1GB.bin out1GB.bin 1 10
	./ordenar 3GB.bin out3GB.bin 1 10
	./ordenar 6GB.bin out6GB.bin 1 10
# Tamanhos diferentes, diferentes memoria e mesmo K
	./ordenar 1MB.bin out1MB.bin 1 10
	./ordenar 10MB.bin out10MB.bin 1 10
	./ordenar 100MB.bin out100MB.bin 10 10
	./ordenar 1GB.bin out1GB.bin 100 10
	./ordenar 3GB.bin out3GB.bin 300 10
	./ordenar 6GB.bin out6GB.bin 600 10
# Mesmo tamanho, mesma memoria e diferentes K
	./ordenar 1MB.bin out1MB.bin 1 10
	./ordenar 10MB.bin out10MB.bin 1 15
	./ordenar 100MB.bin out100MB.bin 1 20
	./ordenar 1GB.bin out1GB.bin 1 25
	./ordenar 3GB.bin out3GB.bin 1 30
	./ordenar 6GB.bin out6GB.bin 1 35

excluir:
	rm -f *.o *.out kfile*.bin
