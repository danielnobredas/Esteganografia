#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "mod.h"
#define MAX 500
#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR 255

typedef unsigned long DWORD;
typedef unsigned long UINT;
typedef unsigned long BYTE;
typedef unsigned long LONG;
typedef unsigned long WORD;
typedef unsigned long BITMAPFILEHEADER;

typedef struct tagBITMAPFILEHEADER{
	UINT bfType;
	DWORD bfsize;
	UINT bfReserved1;
	UINT bfReserved2;
	DWORD bfOffBitts;
}tagBITMAPFILEHEADER;

typedef struct tagRGBQUAD{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}RGBQUAD;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}BITMAPINFOHEADER;

typedef struct {
	unsigned char r, g, b;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel *data;
} PPMImage;


typedef struct tagBITMAPINFO
{
	BITMAPFILEHEADER bmiHeader;
	RGBQUAD bmiColors;
}BITMAPINFO;


void copiaString(char destino[], char origem[], int quantidade)
{
    for(int i = 0;i < quantidade; ++i)
        destino[i] = origem[i];
}

static PPMImage *ler_ppm(FILE *arquivo, char *code, int *max, int *coluna, int *linha) {

	PPMImage *imagem;

	imagem = (PPMImage *)malloc(sizeof(PPMImage));
	if (!imagem) {
		fprintf(stderr, "Erro ao alocar memória\n");
		exit(1);
	}

	fscanf(arquivo, "%s", code);
	fscanf(arquivo, "%d", &imagem->x);
	fscanf(arquivo, "%d", &imagem->y);
	fscanf(arquivo, "%d", max);


	imagem->data = (PPMPixel*)malloc(imagem->x * imagem->y * sizeof(PPMPixel));

	if (fread(imagem->data, 3 * imagem->x, imagem->y, arquivo) != imagem->y) {
		fprintf(stderr, "Erro em carregar a imagem\n");
		exit(1);
	}

	fclose(arquivo);
	return imagem;

}

unsigned char *lerBitMap(FILE *arquivo, BITMAPINFOHEADER *tagBITMAPINFOHEADER){

	tagBITMAPFILEHEADER	bitmapFileHeader;
	unsigned char *imagem;
	unsigned char auxRGB;
	int i;

	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,arquivo);

	if (bitmapFileHeader.bfType !=0x4D42)
	exit(1);

	fread(tagBITMAPINFOHEADER, sizeof(BITMAPINFOHEADER),1,arquivo);

	fseek(arquivo, bitmapFileHeader.bfOffBitts, SEEK_SET);

	imagem = (unsigned char*)malloc(tagBITMAPINFOHEADER->biSizeImage);

	fread(imagem,tagBITMAPINFOHEADER->biWidth, tagBITMAPINFOHEADER->biHeight,arquivo);

	for (i = 0;i < tagBITMAPINFOHEADER->biSizeImage;i+=3){
		auxRGB = imagem[i];
		imagem[i] = imagem[i + 2];
		imagem[i + 2] = auxRGB;
	}

	return imagem;
}

void salvarPPM(const char *filename, PPMImage *img){
	FILE *arq;
	arq = fopen(filename, "wb");
	if (!arq) {
		fprintf(stderr, "Unable to open file '%s'\n", filename);
		exit(1);
	}

	fprintf(arq, "P6\n");
	fprintf(arq, "%d %d\n",img->x,img->y);
	fprintf(arq, "%d\n",RGB_COMPONENT_COLOR);
	fwrite(img->data, 3 * img->x, img->y, arq);
	fclose(arq);
}



int main(int argc, char** argv)
{

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
		char code[3];
		int max;
		int larg, alt;
		PPMImage *imagem;
		imagem = ler_ppm(arquivo, code, &max, &larg, &alt);
		salvarPPM("imd2.ppm",imagem);

	}

	return 0;
}
