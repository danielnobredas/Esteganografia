#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // *POSIX* Para o getopt() original
#include <getopt.h>
#include "mod.h"

const char *ext_arquivo(const char *nome_arq){
  const char *ponto = strrchr(nome_arq, '.');
  if(!ponto || ponto == nome_arq) return "";
  return ponto + 1;

}

int main(int argc, char** argv) {

  FILE *arquivo;
  FILE *input;

  int mode;
  char format[10];
  char optc = 0;

  //Codigo para os paramentros baseado em http://mindbending.org/pt/argumentos-e-parametros-em-c;
  struct option OpcoesLongas[] = {
    {"encoder", no_argument, NULL, 'e'},
    {"decoder", no_argument, NULL, 'd'},
    {"input-file", required_argument, NULL, 'i'},
    {"output-file", required_argument, NULL, 'o'},
    {"format", required_argument, NULL, 'f'},
    {"stdout", no_argument, NULL, 's'},
    {0, 0, 0, 0}
  };


  if(argc == 1) { // Sem argumentos
    printf("Parametros faltando\n");
    exit(0);
  }

  while((optc = getopt_long(argc, argv, "edi:f:", OpcoesLongas, NULL)) != -1) {
    switch(optc) {
      case 'e' :
      mode = 1;
      printf("Rodando em modo 'Enconder'%s\n", format);
      break;
      case 'd' :
      mode = 2;
        printf("Rodando em modo 'Decoder'%s\n", format);
      break;
      case 'i' :
      if ((input = fopen(optarg, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", optarg);
        return 1;
      }
      break;
      case 'o' :
      if ((input = fopen(optarg, "w")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", optarg);
        return 1;
      }
      case 'f' :
      strcpy(format, optarg);
      break;
    }
  }

  if(optind < argc) {
    do {
      if ((arquivo = fopen(argv[optind], "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[optind]);
        return 1;
      }
    }
    while(++optind < argc);
  }


  if (mode == 1){
    if (strcmp(format, "ppm") == 0){
      int max;
      int larg, alt;
      PPMImage *imagem;
      imagem = ler_ppm(arquivo, &max, &larg, &alt);
      salvarPPM("imd2.ppm",codificarMsg(input, imagem));
    }

    if (strcmp(format, "bmp") == 0){
      // BMPFile imagem;
      // imagem = lerBitMap(arquivo);

    }
  }

  if (mode == 2){
    if (strcmp(format, "ppm") == 0){
      int max;
      int larg, alt;
      PPMImage *imagem;
      imagem = ler_ppm(arquivo, &max, &larg, &alt);
      decodificarMsg(imagem);
    }

    if (strcmp(format, "bmp") == 0){
    }

  }

  return 0;
}
