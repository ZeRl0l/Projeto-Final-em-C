#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

void lerimg(struct image* img, FILE *fp);

int main(){

    printf("Qual o nome do arquivo a ser lido: ");
    scanf("%s", nome_arquivo);

    free(pPgm ->data);
    free(pPgm);
    fclose(fp);

    return 0;
}

void lerimg (struct image* img, FILE *fp){

    fp = fopen(nome_arquivo,"r");

    if(!fp){

        printf("Nao foi possivel ler o arquivo %s\n\n", nome_arquivo);

    }

    pPgm = malloc(sizeof(img));

    printf("Lendo o arquivo %s...", nome_arquivo);
    fscanf(fp,"%s", lerarq);

    if(strcmp(lerarq,"P2") == 0){

        printf("TIPO VALIDO!\n\n");
        fscanf(fp,"%s",lerarq);

        while(lerarq[0] == '#'){

            fgets(lerarq, 255, fp);
            fscanf(fp,"%s", lerarq);
        }

    }

    sscanf(fp, "%d", &pPgm->larg);
    fscanf(fp, "%d", &pPgm->alt);
    fscanf(fp, "%d", &pPgm->maximo);
    printf("Largura: %d, Altura: %d\n", pPgm->larg, pPgm->alt);

    pPgm -> data = (int*)malloc(sizeof(int) * pPgm->larg * pPgm->alt);

    for(ler = 0; ler < pPgm->larg * pPgm->alt; ler ++){
        fscanf(fp, "%d", &palavra);
        pPgm->data[ler] = palavra;
    }
    printf("Tamanho da imagem .PGM: %dx%d, Taxa de cinza: %d \n", pPgm -> larg, pPgm->alt, pPgm->maximo);
}
