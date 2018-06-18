#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
#include "mask.h"


int main (){
    
    int largura;
    int altura;
    int maximo;
  	int **data;
  	int janela;
  	int val = (janela/2)*2;
  	
    int op, op1;
    char nomearquivo[50];
    char novoarquivo[50];
	
	printf("Informe o nome do arquivo a ser lido: ");
	scanf("%s", nomearquivo);

	printf("Qual filtro voce deseja usar?\n");
	
	printf("(1) - Convolucao (2) - Filtro da media\n");
	scanf("%d", &op);

	if(op == 1){
		printf("Qual mascara voce deseja usar: ");
		
		printf("(1) - Laplace (2) - Sobel\n");
		scanf("%d", &op1);
		janela = 3;
		
		if(op1 != 1 && op1 != 2){
			printf("Opcao invalida.\n");
			return main();
		}
		
	}else if(op == 2){
		printf("Informe o tamanho da janela: ");
		scanf("%d", &janela);
		
	}else{
		printf("Opcao invalida.\n");
		return main();
	}	
	
	if(janela <= 1 || janela%2 == 0){
		printf("A janela deve ser um numero maior que 1 e deve ser um numero impar.\n\n");
		return main();
	}
	
	fp = fopen(nomearquivo, "r");
	
	if(fp == NULL){
		printf("Nao foi possivel abrir o arquivo %s.\n", nomearquivo);
		exit(1);
	}
	
	printf("Informe o nome do novo arquivo: ");
	scanf("%s", novoarquivo);
	
	armazenaimg(&largura,&altura,&maximo);
	

	data = alocamemo(largura+val, altura+val);
	
	lerimg(data,largura+1,altura+1);
	
	if(op = 1){
		data = filtros(data,largura, altura, op1);
	}else if(op == 2){
		data = filtromedia(data, largura, altura, janela);
	}
	
	escreverimg(data,largura,altura,maximo,novoarquivo);
	
	fclose(fp);
	
	desalocamemo(data,largura);
	
	return 0;
}
