#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // *POSIX* Para o getopt() original
#include <getopt.h>
#include "mod.h"

int main(int argc, char** argv) {


  FILE *arquivo; //Declaração do arquivo de imagem
  FILE *input; //Declaração do arquivo de texto

  //Variaveis para parametros
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


  if(argc == 1) { // No caso de não ter argumentos
    printf("Parametros faltando\n");
    exit(0);
  }

//Leitura dos parametros
  while((optc = getopt_long(argc, argv, "edi:f:", OpcoesLongas, NULL)) != -1) {
    switch(optc) {
      case 'e' :
      mode = 1;
      break;
      case 'd' :
      mode = 2;
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
      //Formato do arquivo
      case 'f' :
      strcpy(format, optarg);
      break;
    }
  }
//Caso de erro ao abrir o arquivo
  if(optind < argc) {
    do {
      if ((arquivo = fopen(argv[optind], "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[optind]);
        return 1;
      }
    }
    while(++optind < argc);
  }

//tipo de arquivo para encriptar
  if (mode == 1){
    if (strcmp(format, "ppm") == 0){
      int max;
      int larg, alt;
      PPMImage *imagem;
      imagem = ler_ppm(arquivo, &max, &larg, &alt);
      codificarMsg(imagem);
      salvarPPM("imd2.ppm",arquivo,input);
    } else

    if (strcmp(format, "bmp") == 0){
      BMPFile imagem;
      imagem = lerBitMap(arquivo);

    }else{
      printf("O formato de arquivo: '%s' não é suportado\n",format);
      return 1;
    }
  }
//tipo de arquivo para decriptar
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
