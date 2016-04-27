# ordenacaoExterna

Implementação de um algoritmo de ordenção externa por intercalação (Merge-Sort) multivias para ordenar um arquivo de dados fornecido como entrada.


# Compilar os arquivos

Vc pode compilar os arquivos de duas formas

digitando apenas:

make

ou compilar manualmente

gcc -c src/gerar_arquivo.c src/gerar_arquivo_main.c

gcc src/gerar_arquivo.o src/gerar_arquivo_main.o -o gerador

#executar: gerar arquivo

./gerador nome_arquivo tamanho_arquivo
