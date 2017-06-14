#include <stdio.h>
#include <stdlib.h>
#include "mod.h"

static PPMImage *ler_ppm(char *code, int *max, int *coluna, int *linha) {

    FILE *arquivo;
		PPMImage *imagem;
    char nome_arq[50];
    printf("entre com o nome do arquivo\n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arq);
        exit(1);
    }

		imagem = (PPMImage *)malloc(sizeof(PPMImage));
    if (!imagem) {
         fprintf(stderr, "Erro ao alocar memória\n");
         exit(1);
    }

    fscanf(arquivo, "%s", code);
    fscanf(arquivo, "%d %d", &imagem->x,&imagem->y);
    // fscanf(arquivo, "%d", &imagem->y);
    fscanf(arquivo, "%d", max);


		imagem->data = (PPMPixel*)malloc(imagem->x * imagem->y * sizeof(PPMPixel));

		if (fread(imagem->data, 3 * imagem->x, imagem->y, arquivo) != imagem->y) {
         fprintf(stderr, "Erro em carregar a imagem '%s'\n", nome_arq);
         exit(1);
    }

  	fclose(arquivo);
		return imagem;

}

