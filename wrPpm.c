#include <stdio.h>
#include <stdlib.h>
#include "mod.h"
#define RGB_COMPONENT_COLOR 255

void salvarPPM(const char *filename, PPMImage *img){
  FILE *arq;
  arq = fopen(filename, "wb");
  if (!arq) {
    printf("Não é possivel abrir o arquivo '%s'\n", filename);
    exit(1);
  }

  fprintf(arq, "P6\n");
  fprintf(arq, "%d %d\n",img->x,img->y);
  fprintf(arq, "%d\n",RGB_COMPONENT_COLOR);
  fwrite(img->data, 3 * img->x, img->y, arq);
  fclose(arq);
}
