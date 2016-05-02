all: compilar_objeto compilar_binario excluir

compilar_objeto:
	gcc -c ./src/gerar_arquivo_main.c ./src/gerar_arquivo.c
	gcc -c ./src/ordenar_arquivo_main.c ./src/ordenar_arquivo.c

compilar_binario:
	gcc ./src/gerar_arquivo_main.o ./src/gerar_arquivo.o -o gerador -lm
	gcc ./src/ordenar_arquivo_main.c ./src/ordenar_arquivo.c -o ordenar -lm

gerar:
	./gerador 1MB.bin 1
	./gerador 10MB.bin 10
	./gerador 100MB.bin 100
	./gerador 1GB.bin 1000
	./gerador 3GB.bin 3000
	./gerador 6GB.bin 6000


ordenar:
	#Tamanhos diferentes, mesma memoria e mesmo K
	./ordenar 1MB.bin out1MB 0.1 2
	./ordenar 10MB.bin out10MB 0.1 2
	./ordenar 100MB.bin out100MB 0.1 2
	./ordenar 1GB.bin out1GB 0.1 2
	./ordenar 3GB.bin out3GB 0.1 2
	./ordenar 6GB.bin out6GB 0.1 2
	#Tamanhos diferentes, diferentes memoria e mesmo K
	./ordenar 1MB.bin out1MB 0.1 2
	./ordenar 10MB.bin out10MB 1 2
	./ordenar 100MB.bin out100MB 10 2
	./ordenar 1GB.bin out1GB 100 2
	./ordenar 3GB.bin out3GB 300 2
	./ordenar 6GB.bin out6GB 600 2
	#Mesmo tamanho, mesma memoria e diferentes K
	./ordenar 1MB.bin out1MB 0.1 2
	./ordenar 10MB.bin out10MB 0.1 4
	./ordenar 100MB.bin out100MB 0.1 6
	./ordenar 1GB.bin out1GB 0.1 10
	./ordenar 3GB.bin out3GB 0.1 15
	./ordenar 6GB.bin out6GB 0.1 20

excluir:
	rm -f *.o *.out kfile*.bin
