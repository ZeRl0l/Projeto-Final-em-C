typedef struct pgm {
	int altura;
	int largura;
	int maximo;
	int **data;

}pgm;

pgm* lerPGM(const char *nome_arquivo, pgm* pPgm){
	
	FILE *fp;
	char ler[256];
	int i, j;
	int lo, hi;
	
	printf("Qual o nome do arquivo a ser lido: ");
	scanf("%s", nome_arquivo);
	
	fp = fopen(nome_arquivo,"r");
	
	if(fp == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	
	printf("Lendo o arquivo %s...\n\n", nome_arquivo);
	
	fscanf(fp,"%s",ler);
	
	if(strcmp(ler, "P2") == 0){
		
		printf("TIPO VALIDO!\n\n");
		fscanf(fp,"%s", ler);
	}
	
	split(fp);
	fscanf(fp, "%d", &pPgm -> altura);
	split(fp);
	fscanf(fp, "%d", &pPgm -> largura);
	slipt(fp);
	fscanf(fp, "%d", &pPgm -> maximo);
	fgetc(fp);
	
	pPgm -> data = alocar_memoria(pPgm -> altura, pPgm -> largura);
	
	if(pPgm -> maximo > 255){
		for(i = 0; i < pPgm -> altura; ++i) {
			for(j = 0; j < pPgm -> largura; ++j){
				hi = fgetc(fp);
				lo = fgetc (fp);
				pPgm -> data[i][j] = (hi << 8) + lo;
			}	
		}
	}
	else {
		for(i = 0; i < pPgm -> altura; ++i){
			for(j = 0; i < pPgm -> largura; ++j){
				lo = fgetc(fp);
				pPgm -> data[i][j] = lo;
			}
		}
		
		fclose(fp);
		return pPgm;
}

void escreverPGM(const char *novo_arquivo, const pgm* pPgm){
	FILE *nfp;
	int i, j;
	int hi, lo;
	
	printf("--------ESCREVER NOVO ARQUIVO--------\n\n");
	
	printf("O arquivo deve ser escrito no formato ./pasta/nomedoarquivo.ascii.pgm\n\n");
	
	printf("Digite o nome do novo arquivo: ");
	scanf("%s", novo_arquivo);
	
	nfp = fopen(novo_arquivo, "w");
	
	if(nfp == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		exit(1);	
	}
	
	fprintf(nfp,"P2");
	fprintf(nfp,"%d %d", pPgm -> largura, pPgm -> altura);
	fprintf(nfp, "%d", pPgm -> maximo);
	
	/*if(pPgm -> maximo > 255){
	for(i = 0; i < pPgm -> altura; ++i) {
		for(j = 0; j < pPgm -> largura; ++j){
			hi = fgetc(fp);
			lo = fgetc (fp);
			pPgm -> data[i][j] = (hi << 8) + lo;
			}	
		}
	}
	else {
		for(i = 0; i < pPgm -> altura; ++i){
			for(j = 0; i < pPgm -> largura; ++j){
				lo = fgetc(fp);
				pPgm -> data[i][j] = lo;
		}
	}*/
	fclose(nfp);
	desalocar_memoria(pPgm -> data, pPgm -> altura);

}

void split(FILE *fp0){
	
	int ch;
	char linhas[100];
	
	while((ch = fgetc(fp0)) != EOF && isspace(ch));
	
	if(ch == '#'){
		fgets(linhas, sizeof(linhas), fp0);
		split(fp0);
	} else {
		fseek(fp, -1, SEEK_CUR);
	}

}

void **alocar_memoria(struct pmg* pgm){
	
	int **val;
	int i;
	
	val = (int **)malloc(sizeof(int *)* largura);
	if (val == NULL){
		printf("Nao foi possivel alocar memoria.");
		return NULL;
	}
	
	for(i = 0; i < altura; i++){
		val[i] = (int *)malloc(sizeof(int) * altura);
			printf("Nao foi possivel alocar memoria");
			return NULL;
	}
	
	return val;

}

void desalocar_memoria(int **data, int altura){

	int i;
	
	for (i = 0; i < altura; ++i){
		free(data[i]);
	
	}
	
	free (data);
}
