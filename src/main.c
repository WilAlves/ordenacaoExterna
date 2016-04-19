#include "../lib/ordenacao.h"

int32_t main()
{
	int qtde, i;

	printf("Quantidade de numeros aleatorio: ");
	scanf("%d",&qtde);

	for (i = 9999; i <= qtde + 9999; i++)
	{
		int32_t numero = gerar_numero_aleatorio(i);
		printf ("%d\n", numero);
	}
}
