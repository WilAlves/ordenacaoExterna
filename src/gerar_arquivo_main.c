#include "../lib/gerar_arquivo.h"

int32_t main(int32_t argc, char *argv[])
{
	/*
	 * Argumentos passados por parametros
	 * argv[0] -> executavel
	 * argv[1] -> nome_arquivo
	 * argv[2] -> tamanho_arquivo
	 *
	 */
	if (argc != 3)
	{
		printf("\nVc deve usar: %s <nome_arquivo> <tamanho_arquivo>\n", argv[0]);
		return 1;
	}
	else
	{
		printf("\nCriando o arquivo: %s\n", argv[1]);
		clock_t inicio, fim;
		inicio = clock();
		FILE *arquivo = fopen(argv[1], "rb");
		if (arquivo != NULL)
		{
			printf("\nO arquivo já existe! Ignorando a criação ...\n");
			fclose(arquivo);
			return 0;
		}
		escrever_arquivo(argv[1], atol(argv[2]) * MB);
		fim = clock();
		double tempo_gasto = (double) (fim- inicio) / CLOCKS_PER_SEC;

		printf("\nARQUIVO: %s\n", argv[1]);
		printf("\nTEMPO GASTO: %lf\n", tempo_gasto);

	}
	return 0;
}
