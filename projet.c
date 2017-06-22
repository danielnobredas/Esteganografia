#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // *POSIX* Para o getopt() original
#include <getopt.h>
#include "mod.h"

void copiaString(char destino[], char origem[], int quantidade)
{
    for(int i = 0;i < quantidade; ++i)
        destino[i] = origem[i];
}

const char *ext_arquivo(const char *nome_arq){
    const char *ponto = strrchr(nome_arq, '.');
    if(!ponto || ponto == nome_arq) return "";
    return ponto + 1;

}

int main(int argc, char** argv) {

	FILE *arquivo;

	int mode;
	char format[10];
	char optc = 0;

	//Codigo para os paramentros baseado em http://mindbending.org/pt/argumentos-e-parametros-em-c;
	struct option OpcoesLongas[] = {
		{"encoder", no_argument, NULL, 'e'},
		{"decoder", no_argument, NULL, 'd'},
		{"input-file", required_argument, NULL, 'i'},
		{"output-file", required_argument, NULL, 'i'},
		{"format", required_argument, NULL, 'f'},
		{"stdout", no_argument, NULL, 's'},
		{0, 0, 0, 0}
	};


	if(argc == 1) { // Sem argumentos
		printf("Parametros faltando\n");
		exit(0);
	}

	while((optc = getopt_long(argc, argv, "ef:d:", OpcoesLongas, NULL)) != -1) {
		switch(optc) {
			case 'e' :
			mode = 1;
			break;
			case 'd' :
			mode = 2;
			break;
			// case 'i' :
			// 					printf("Oi\n");
			// 					break;
			case 'f' :
			copiaString(format, optarg, 10);
			printf("O formato da imagem é %s\n", format);
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
		int max;
		int larg, alt;
    char code[3];
		PPMImage *imagem;
		imagem = ler_ppm(arquivo, code, &max, &larg, &alt);
		salvarPPM("imd2.ppm",imagem);

	}

	return 0;
}
