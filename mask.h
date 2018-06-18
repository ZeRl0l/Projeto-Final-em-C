int laplace[3][3] = {{1, 1, 1},
                     {1, -8, 1},
					 {1, -1, 1}};
					 
int sobel[3][3] = {{-1, 0, 1},
				   {-2, 0, 2},
				   {-1, 0, 1}};

					 
int** aloca_memo(int largura, int altura){
	
	int **val;
	int i;
	
	val = (int **)malloc(sizeof(int *) * largura);
	
	for(i = 0; i < largura; i ++){
		val[i] = (int *)malloc(sizeof(int *) * altura);
	}
	return val;
}

int convolucao (int i, int j ,int laplace[][3],int**data){
	
	int p = 0, q = 0, temp;
	int element = 0;
	i = i - 1;
	j = j - 1;
	temp = i;
	while(p < 3){
		while(q < 3){
		    element += data[i++][j] * laplace[q++][p];
		}
		p++;
		q = 0;
		i = temp;
		j++;
	}
	
	element = (element > 255?255 : element);
	element=( element < 0? 0 : element);
	return element;
}

int** filtros(int **data2, int linha , int coluna, int op1){
	int matriz[3][3];
	
	
	
	if(op1 == 1){
    	for(int i = 0; i < 3; i++){
			for(int j = 0; j <3; j++){
				matriz[i][j] = laplace[i][j];
			}
		}	
 	}else if(op1 == 2){
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				matriz[i][j] = sobel[i][j];
			}
		}
	}

	int **val = aloca_memo(coluna+2,linha+2);
		
		for (int i=0;i<linha;i++){
			for(int j=0;j<coluna;j++){
				val[i][j]=0;
			}
		}
		for (int i=1;i<linha+1;i++){
			for(int j=1;j<coluna+1;j++){
				val[i][j]= data2[i-1][j-1];
			}
		}
	
		for (int i=1;i<linha-1;i++){
			for(int j=1;j<coluna-1;j++){
				val[i][j]= convolucao(i,j,matriz,data2);
			}
		}
		for (int i=1;i<linha+1;i++){
			for(int j=1;j<coluna+1;j++){
				data2[i-1][j-1]= val[i][j];
			}
		}
	return val;
}
