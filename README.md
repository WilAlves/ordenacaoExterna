# ordenacaoExterna
Implementação de um algoritmo de ordenção externa por intercalação (Merge-Sort) multivias para ordenar um arquivo de dados fornecido como entrada.


# Compilar os arquivos
Vc pode compilar os arquivos de duas formas

digitando apenas:

make

ou compilar manualmente

gcc -c ./src/gerar_arquivo.c ./src/gerar_arquivo_main.c

gcc ./src/gerar_arquivo.o ./src/gerar_arquivo_main.o -o gerador

gcc -c ./src/ordenar_arquivo.c ./src/ordenar_arquivo_main.c

gcc ./src/ordenar_arquivo.o ./src/ordenar_arquivo_main.o -o ordenar

#executar: gerar arquivo
Vc pode executar de duas formas também

make gerar

ou executar manualmente

./gerador nome_arquivo tamanho_arquivo

#executar: ordenar arquivo
Vc pode executar de duas formas também

make ordenar

ou executar manualmente

./gerador entrada_arquivo saida_arquivo memoria K
