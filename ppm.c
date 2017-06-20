#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"

static PPMImage *ler_ppm(FILE *arquivo,char code,int *max, int *coluna, int *linha) {

    
		PPMImage *imagem;
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

		if (fread(imagem->data, 3 * imagem->y,imagem->x arquivo) != imagem->y) {
         fprintf(stderr, "Erro em carregar a imagem '%s'\n", nome_arq);
         exit(1);
    }

  	fclose(arquivo);
		return imagem;

}

