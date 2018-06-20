#define vetorzao 10000

FILE *fp;
FILE *nfp;
int jan;

int** alocamemo(int largura, int altura){
	
	int **val;
	int i;
	
	val = (int **)malloc(largura*sizeof(int*));
	
	for(i = 0; i < largura; i ++){
		val[i] = (int *)malloc(altura*sizeof(int*));
	}
	return val;
}

int** lerimg(int **data,int largura, int altura){
	
	int i,j;
	int x;
	char linha[1000];
	int val;
	
	for(i = jan/2; i < largura + jan/2 -1; i++){
		for(j = jan/2; j < altura + jan/2 -1; j++){
		
			x = fgetc(fp);
			if ( x == '#'){
				j--;
				fgets(linha, vetorzao, fp);
				continue;
			}
			fseek(fp, -1, SEEK_CUR);
			fscanf(fp, "%d ", &val);
			data[i][j] = val;
		}
	}		
	return data;
}

void armazenaimg(int *largura, int *altura, int *maximo){
	
	char linha[1000];
	char x;
	int k;
	
	fgets(linha,vetorzao,fp);
	*altura = -1;
	*largura = -1;
	*maximo = -1;
	
	while(*maximo <= 0){
		k = fgetc(fp);
	
		if(k == '#'){
			fgets(linha,vetorzao,fp);
			continue;
		}
		
		fseek(fp, -1, SEEK_CUR);
		
		fscanf(fp, "%c", &x);
		
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

void escreverimg(int **data,int largura, int altura, int maximo, char *newfile){
	
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
	
	for(i = jan/2; i < largura+jan/2; i++){
			count = 1;
		for(j = jan/2; j < altura+jan/2; j++,count++){
			fprintf(nfp, "%.3d ", data[i][j]);
			if(count%10 == 0 && j > jan/2){
			}	
		}
		fprintf(nfp,"\n");
	}
	fclose(nfp);
	printf("O arquivo foi criado com exito!\n");
}

int** filtromediana(int **ndata, int largura, int altura,int janela2){
	int *matriz;
    matriz = (int *) malloc(sizeof(int *) * janela2 * janela2);
    
    int soma;
    int m = 0;
    int count, val;
    int i, j, k, l, h;
    
    int **data;
     
    int aux = janela2/2;
    data = alocamemo(largura + 2*aux, altura + 2*aux);
    for(i = 0; i < largura + 2*aux; i++){
	    for(j = 0; j < altura + 2*aux; j++){
		    data[i][j] = 0;
	    }
    }
    for(i = aux; i < largura + aux; i++){
	    for(j = aux; j < altura + aux; j++){
		    data[i][j] = ndata[i][j];
	    }
    }
    soma = 0;
    for(k = aux; k < largura + aux; k++){
	    for(l = aux; l < altura + aux; l++){
		    for(i = k - aux; i < k + aux + 1; i++){
			    for(j = l - aux; j < l + aux + 1; j++){
				    matriz[m++]= data[i][j];

			    }
			}   
		    for(h = 0; h < janela2 *janela2;h++){         
				count = h;
				while(matriz[count-1] > matriz[count] && count > 0){
				    val = matriz[count];
				    matriz[count] = matriz[count -1];
				    matriz[count-1] = val;
				    count--;
		    	}
	  		}
			data[k][l] = matriz[janela2*janela2/2];
			m = 0;
			soma = 0;
		}
    }
    return data;
}
