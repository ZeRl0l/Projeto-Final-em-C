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

int convolucao (int **data, int laplace[3][3]){
	
	int i, j;
	
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

int** testando(int **data, int largura, int altura, int op1){
	int matriz[3][3];
	
	int i;
	int j;
	
	if(op1 == 1){
    	for(i = 0; i < 3; i++){
			for(j = 0; j <3; j++){
				matriz[i][j] = laplace[i][j];
			}
		}	
 	}else if(op1 == 2){
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				matriz[i][j] = sobel[i][j];
			}
		}
	}
}
