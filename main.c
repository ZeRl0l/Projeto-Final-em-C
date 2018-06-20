#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
#include "mask.h"


int main (){
    
    int largura, altura, maximo;
    int i,j;
  	int **data;
  	int val;
    
    char op,op1;
    char nomearquivo[50];
    char novoarquivo[50];
	
	printf("Informe o nome do arquivo a ser lido: ");
	scanf("%s", nomearquivo);
	
	printf("Qual filtro voce deseja usar?\n");
	
	printf("(A) - Convolucao (B) - Mediana (C) - Media\n");
	setbuf(stdin,NULL);
	scanf("%c", &op);
	setbuf(stdin,NULL);

	if(op == 'A'){
		printf("(L) - Laplace (S) - Sobel\n");
		getchar();
		scanf("%c", &op1);
		jan = 3;
		
		if(op1 != 'L' && op1 != 'S'){
			printf("Opcao invalida.\n");
			return main();	
		}
		
		setbuf(stdin,NULL);
		
	}else if(op == 'B'){
		printf("Informe o tamanho da janela:\n");
		scanf("%d",&jan);
	
		
	}else if(op == 'C'){
		printf("Informe o tamanho da janela:\n");
		scanf("%d",&jan);
	}else{
		printf("Opcao invalida.\n");
		return main();
	}	
	
	if(jan <= 1 || jan%2 == 0){
		printf("A janela deve ser um numero maior que 1 e deve ser um numero impar.\n\n");
		setbuf(stdin,NULL);
		
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

	val = (jan/2)*2;
	data = alocamemo(largura+val, altura+val);
	
	lerimg(data,largura+1,altura+1);
	
	if(op == 'A'){
		data = masks(data, largura + 1, altura + 1, op1);
	
	}else if(op == 'B'){
		data = filtromediana(data,largura, altura, jan);
	}else if(op == 'C'){
		data = filtromedia(data,larugra,altura,jan);
	}
	
	escreverimg(data,largura,altura,maximo,novoarquivo);
	
	fclose(fp);
	
	desalocamemo(data,largura);
	
	return 0;
}
