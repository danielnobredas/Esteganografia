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
  // fscanf(arquivo, "%d", &imagem->y);
  fscanf(arquivo, "%d", max);


  imagem->data = (PPMPixel*)malloc(imagem->x * imagem->y * sizeof(PPMPixel));

  if (fread(imagem->data, 3 * imagem->x, imagem->y, arquivo) != imagem->y) {
    fprintf(stderr, "Erro em carregar a imagem\n");
    exit(1);
  }

  fclose(arquivo);
  return imagem;

}

char *convertFileToText(FILE *arquivo) {
  long size;
  char *texto;

  fseek(arquivo, 0L, SEEK_END);
  size = ftell(arquivo);
  rewind(arquivo);

  texto = calloc(1, size + 1);
  if (!texto) {
    fclose(arquivo);
    fprintf(stderr, "Erro ao alocar memória");
    exit(1);
  }

  if (fread(texto, size, 1, arquivo) != 1) {
    fclose(arquivo);
    free(texto);
    fprintf(stderr, "Não é possivel ler esse arquivo.");
    exit(1);
  }
  fclose(arquivo);
  return texto;
}


PPMImage *codificarMsg(FILE *arquivo, PPMImage *imagem){


  char *msg = convertFileToText(arquivo);
  char *msgBits;

  int i;

  int countString = strlen(msg) * sizeof(char) * 8;
  int counter = 0;

  msgBits = malloc(countString);

  if (imagem) {

    int imgSize = 3 * imagem->y * imagem->x;

    if ((strlen(msg) + sizeof(char)) * sizeof(char) > imgSize * sizeof(char)) {
      fprintf(stderr, "Mensagem muito grande.");
      exit(1);
    } else {
      while (counter < countString) {
        *(msgBits + counter) = ((*msg) % 2);
        *msg = *msg >> 1;
        counter++;
      }

      int index = 0;

      for (i = 0; i < countString; i++) {
        if (*(msgBits + index) != (imagem->data[i].r % 2)) {
          imagem->data[i].r = (imagem->data[i].r & 0xFE) | *(msgBits + index);
        }
        index++;

        if (*(msgBits + index) != (imagem->data[i].g % 2)) {
          imagem->data[i].g = (imagem->data[i].g & 0xFE) | *(msgBits + index);
        }
        index++;

        if (*(msgBits + index) != (imagem->data[i].b % 2)) {
          imagem->data[i].b = (imagem->data[i].b & 0xFE) | *(msgBits + index);
        }
        index++;
      }
    }
  }
  return imagem;
}

void decodificarMsg(PPMImage *imagem){

  int i, j, k;
  char *msg;
  // FILE *saida = fopen("saida.txt","a");

  int imgSize= 3* imagem->x * imagem->y;

  msg=malloc(imgSize);

  if(imagem){
    for (i = 0, j =0; (i < imgSize) && (j < 8); i++, j++) {
      // printf("%u\n",imagem->data[i].g);
      setBit(&msg[k],j,getBit(imagem->data[i].r, 7));
      setBit(&msg[k],j,getBit(imagem->data[i].g, 7));
      setBit(&msg[k],j,getBit(imagem->data[i].b, 7));
      if (j== 7) {
        printf("%u\n", *msg);
        j = 0;
        k++;
      }
    }
    printf("%s\n",converteBin(*msg));
  }
}


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
