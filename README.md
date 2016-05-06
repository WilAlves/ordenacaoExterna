
# ordenacaoExterna
Implementação de um algoritmo de ordenção externa por intercalação (Merge-Sort) multivias para ordenar um arquivo de dados fornecido como entrada.


# Compilar os arquivos
O codigo roda em qualquer plataforma:

-> Linux
	* GCC
	* Todos os passos podem ser feito pelo terminal

-> Windows
	* Qualquer IDE
	* Qualquer editor modo texto
	* GCC

Vc pode compilar os arquivos de duas formas

digitando apenas:

make

ou compilar manualmente

gcc -c ./src/gerar_arquivo.c ./src/gerar_arquivo_main.c

gcc ./src/gerar_arquivo.o ./src/gerar_arquivo_main.o -o gerador

gcc -c ./src/ordenar_arquivo.c ./src/ordenar_arquivo_main.c

gcc ./src/ordenar_arquivo.o ./src/ordenar_arquivo_main.o -o ordenar

gcc -c ./src/ler_arquivo_gerado.c

gcc ./src/ler_arquivo_gerado.o -o ler

#executar: gerar arquivo

make gerar

ou

./gerador nome_arquivo tamanho_arquivo

#executar: ordenar arquivo

make order

ou

./ordenar entrada_arquivo saida_arquivo memoria K

#transformar arquivos binarios gerados em txt

make ler_ordenado ou make ler_desordenado

ou

./ler 1GB.bin > 1GB.txt
./ler out1GB.bin > out1GB.txt
