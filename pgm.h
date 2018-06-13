typedef struct image {
    int larg;
    int alt;
    int maximo;
    int *data;
}img;

FILE* fp;
img* pPgm;
int ler = 0;
char nome_arquivo [265];
char lerarq [256];
int palavra;

void escreverigm (struct image* img);
