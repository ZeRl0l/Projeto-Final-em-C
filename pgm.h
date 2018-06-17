#define vetorzao 10000

FILE *fp;
FILE *nfp;
int janela;

int** alocamemo(int largura, int altura){
	
	int **val;
	int i;
	
	val = (int **)malloc(sizeof(int *) * largura);
	
	for(i = 0; i < largura; i ++){
		val[i] = (int *)malloc(sizeof(int *) * altura);
	}
	return val;
}

int** lerimg(int **data,int largura, int altura){
	
	int i,j;
	char x;
	char linha[1000];
	unsigned char val;
	
	for(i = janela/2; i < largura + janela/2 - 1; i++){
		for(j = janela/2; j < altura + janela/2 - 1; j++){
		
			x = fgetc(fp);
			if ( x == '#'){
				j--;
				fgets(linha, vetorzao, fp);
				continue;
			}
			fseek(fp, -1, SEEK_CUR);
			fscanf(fp, "%hhd ", &val);
			data[i][j] = val;
		}
	}		
	return data;
}

void armazenaimg(int *largura, int *altura, int *maximo){
	
	char linha[1000];
	char x;
	
	unsigned char k;
	
	fgets(linha,vetorzao,fp);
	*altura = -1;
	*largura = -1;
	*maximo = -1;
	
	while(*maximo <= 0){
		x = fgetc(fp);
	
		if(x == '#'){
			fgets(linha,vetorzao,fp);
			continue;
		}
		
		fseek(fp, -1, SEEK_CUR);
		
		fscanf(fp, "%c", &k);
		
		if(*altura == -1){
			fseek(fp,-1,SEEK_CUR);
			fscanf(fp, "%d", &(*altura));
		}else if (*largura == -1){
			fseek(fp,-1,SEEK_CUR);
			fscanf(fp, "%d", &(*largura));
		}else if(*maximo == -1){
			fseek(fp,-1,SEEK_CUR);
			fscanf(fp, "%d", &(*maximo));
		}
	}
}

void bordas(int **data, int largura, int altura){
	
	int i = 0;
	
	for(i = 0; i <= altura + 1; i++){
		data[0][i] = 255;
		data[largura + 1][i] = 255;
	}
	
	for(i = 0; i <= largura + 1; i++){
		data[i][0] = 255;
		data[i][altura +1] = 255;
	}
}

void desalocamemo(int **data, int largura){
	int i;
	
	for(i = 0; i < largura; ++i){
		free(data[i]);
	}
	free(data);
}

void escreverimg(int **data,int largura, int altura, int maximo, const char *newfile){
	
	int i,j;
	int count = 1;
	
	nfp = fopen(newfile, "w");
	
	if(nfp == NULL){
		printf("Nao foi possivel criar o arquivo.\n");
		exit(1);
	}
	
	fprintf(nfp,"P2\n");
	fprintf(nfp,"%d %d\n", altura, largura);
	fprintf(nfp,"%d\n", maximo);
	
	for(i = janela/2; i < altura+janela/2; i++){
			count = 1;
		for(j = janela/2; j < largura+janela/2; j++,count++){
			fprintf(nfp, "%.3d ", data[i][j]);
			if(count%10 == 0 && j > janela/2)
				fprintf(nfp, "\n");
		}
		fprintf(nfp,"\n");
	}
	fclose(nfp);
	printf("O arquivo foi criado com exito!\n");
}
