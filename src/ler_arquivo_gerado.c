#include "../lib/gerar_arquivo.h"

int32_t ler_arquivo_binario(char *nome_arquivo)
{
	printf("\nFILENAME: %s\n", nome_arquivo);

	FILE *arquivo = fopen(nome_arquivo, "rb");

	if (!arquivo)
	{
		printf("Erro ao abrir o arquivo!");

		return 1;
	}

	int32_t numero;

	while (fread(&numero, sizeof(int), 1, arquivo) == 1)
	{
		printf("%d\n", numero);
	}

	fclose(arquivo);

	return 0;
}

int32_t main(int32_t argc, char *argv[])
{
	ler_arquivo_binario(argv[1]);

	return 0;
}
