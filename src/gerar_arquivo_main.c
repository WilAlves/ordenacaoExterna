#include "../lib/gerar_arquivo.h"

#define GB 1000 * 1000 * 1000
#define MB 1000 * 1000

int32_t main(int32_t argc, char *argv[])
{
	/*
	 * Argumentos passados por paramentos
	 * argv[0] -> executavel
	 * argv[1] -> nome_arquivo
	 * argv[2] -> tamanho_arquivo
	 *
	 */
	if (argc > 2)
	{
		printf("\nCriando o arquivo: %s\n", argv[1]);
		FILE *arquivo = fopen(argv[1], "rb");
		if (arquivo != NULL)
		{
			printf("\nO arquivo já existe! Ignorando a criação ...\n");
			fclose(arquivo);
			return 0;
		}
		escrever_arquivo(argv[1], atol(argv[2]) * MB);
	}
	else
	{
		printf("\nVc deve usar: %s <nome_arquivo> <tamanho_arquivo>\n", argv[0]);
		return 1;
	}
	return 0;
}
