#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"

const char *ext_arquivo(const char *nome_arq){
    const char *ponto = strrchr(nome_arq, '.');
    if(!ponto || ponto == nome_arq) return "";
    return ponto + 1;
}

int main(int argc, char const *argv[])
{
  char nome_arq[80];
  scanf("%s",nome_arq);
  FILE *arquivo=fopen(nome_arq,"r");
	char code[3]; //o código para saber se a imagem é ascii ou binária
	int max; //o valor máximo de tonalidade de cada pixel
	int larg, alt; // largura e altura da imagem em pixe
	PPMImage *imagem;
	imagem = ler_ppm(arquivo, code, &max, &larg, &alt);
	writePPM("imd2.ppm",imagem);

  //RECEBER E TESTAR EXTENÇÃO DO ARQUIVO
    printf("%s\n", ext_arquivo(nome_arq));
    printf("%s\n", ext_arquivo("teste.blah.ppm"));
    printf("%s\n", ext_arquivo("teste."));
    printf("%s\n", ext_arquivo("teste"));
    printf("%s\n", ext_arquivo("..."));
	return 0;
}
