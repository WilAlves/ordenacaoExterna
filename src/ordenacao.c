#include "../lib/ordenacao.h"


int32_t gerar_numero_aleatorio(qtde)
{
	srand ( (unsigned)time(NULL) );

	int32_t numero = rand() % qtde;//( rand() % qtdeNumeros )

	return numero;
}
