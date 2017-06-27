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


PPMImage *codificarMsg(FILE *arquivo, PPMImage *image){


  char *message = convertFileToText(arquivo);
  char *message_bits;

  int i;
  //Get the bit amount in the message
  int string_bits_count = strlen(message) * sizeof(char) * 8;
  printf("String bits count: %d\n", string_bits_count);
  int counter = 0;

  //Alloc the array that will hold the message's bits
  message_bits = malloc(string_bits_count);

  if (image) {

    int image_size = 3 * image->y * image->x;
    printf("Image size: %d\n", image_size);

    //Check if image will hold the entire message plus the escape character
    if ((strlen(message) + sizeof(char)) * sizeof(char) > image_size * sizeof(char)) {
      fprintf(stderr, "Message too long for the selected image");
      exit(1);
    } else {
      //Set the message bits in the array, note that the array holds the
      //inverted message
      while (counter < string_bits_count) {
        *(message_bits + counter) = ((*message) % 2);
        //printf("Counter: %d\n", counter);
        *message = *message >> 1;
        //printf("Message bit: %c\n", *(message_bits + counter));
        counter++;
      }

      int bit_index = 0;

      for (i = 0; i < string_bits_count; i++) {
        if (*(message_bits + bit_index) != (image->data[i].r % 2)) {
          //printf("Original data: %d\n", image->data[i].red);
          image->data[i].r = (image->data[i].r & 0xFE) | *(message_bits + bit_index);
          //printf("New data: %d\n", image->data[i].red);
        }
        bit_index++;

        if (*(message_bits + bit_index) != (image->data[i].g % 2)) {
          image->data[i].g = (image->data[i].g & 0xFE) | *(message_bits + bit_index);
        }
        bit_index++;

        if (*(message_bits + bit_index) != (image->data[i].b % 2)) {
          image->data[i].b = (image->data[i].b & 0xFE) | *(message_bits + bit_index);
        }
        bit_index++;
      }
    }
  }
      return image;
  }
