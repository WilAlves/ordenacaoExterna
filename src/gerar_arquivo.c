#include "../lib/gerar_arquivo.h"


int32_t gerar_numero_aleatorio()
{

	int32_t numero = rand();

	return numero;
}

int32_t escrever_arquivo(char *nome_arquivo, long tamanho_total)
{
	FILE *arquivo = fopen(nome_arquivo, "wb");
	long tamanho_arquivo = 0;
	if (!arquivo)
	{
		printf("Erro ao abrir arquivo!");
		return 1;
	}
	while (tamanho_arquivo < tamanho_total)
	{
		int numero = gerar_numero_aleatorio();
		/*escrever em blocos de bytes no arquivo*/
		fwrite(&numero, sizeof(int32_t), 1, arquivo);
		tamanho_arquivo = tamanho_arquivo + sizeof(int32_t);
	}
	fclose(arquivo);
	return 0;
}
