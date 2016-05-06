#include "../lib/ordenar_arquivo.h"

int32_t main(int32_t argc, char *argv[])
{
	/*
	 * Argumentos passados por parametros
	 * argv[0] -> executavel
	 * argv[1] -> nome_arquivo
	 * argv[2] -> tamanho_arquivo
	 *
	 */
	if (argc != 5)
	{
		printf("\nVc deve usar: %s <arquivo_entrada> <arquivo_saida> <qtde_memoria> <num_K>", argv[0]);
		return 1;
	}
	else
	{
		const int32_t K = atoi(argv[4]);
		int32_t memoria = atoi(argv[3]) * MB;
		FILE *file = fopen(argv[1], "rb");
		clock_t inicio, fim;
		inicio = clock();
		KFile *files = generate_runs(file, memoria, K);
		unsigned long input_file_length = get_file_length(file);
		int32_t output_file_index = interpolate(files, input_file_length, memoria, K);
		fim = clock();
		double tempo_gasto = (double) (fim - inicio) / CLOCKS_PER_SEC;
		int32_t x;
		for (x = 0; x < 2 * K; x++)
		{
			fclose(files[x].file);
			if (x == output_file_index)
			{
				continue;
			}
			remove(files[x].name);
		}
		rename(files[output_file_index].name, argv[2]);
		printf("\nARQUIVO: %s\n", argv[1]);
		printf("\nMEMORIA: %d", memoria);
		printf("\nK: %d", K);
		printf("\nTEMPO GASTO: %lf\n", tempo_gasto * 1000);
		printf("\nARQUIVO SAIDA: %s\n", argv[2]);
		fclose(file);
	}
	return 0;
}
