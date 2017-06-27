#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"


PPMImage *ler_ppm(FILE *arquivo, int *max, int *coluna, int *linha) {

  PPMImage *imagem;
  char code[3];
  imagem = (PPMImage *)malloc(sizeof(PPMImage));
  if (!imagem) {
    fprintf(stderr, "Erro ao alocar memória\n");
    exit(1);
  }

  fscanf(arquivo, "%s", code);
  fscanf(arquivo, "%d %d", &imagem->x,&imagem->y);
  fscanf(arquivo, "%d", max);
  rewind(arquivo);
  imagem->data = (PPMPixel*)malloc(imagem->x * imagem->y * sizeof(PPMPixel));

  if (fread(imagem->data, 3 * imagem->x, imagem->y, arquivo) != imagem->y) {
    fprintf(stderr, "Erro em carregar a imagem\n");
    exit(1);
  }
  fclose(arquivo);
  return imagem;

}
