#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

int main(){


	void desalocar_memoria(int *data, int altura);
	void **alocar_memoria(struct pgm* pgm);
	void split(FILE *fp0);
	pgm* lerPGM(const char *nome_arquivo, pgm* pPgm);
	void escreverPGM(const char *novo_arquivo, const pgm* pPgm);

	return 0;
}
