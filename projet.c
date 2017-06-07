#include <stdio.h>
#include <stdlib.h>
#include "mod.h"
#define MAX 500

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

 struct pixel{
	int r, g, b;
}Pixel;

typedef struct tagBITMAPINFO
{
	BITMAPFILEHEADER bmiHeader;
	RGBQUAD bmiColors;
}BITMAPINFO;

// typedef{
// 	int **imagem;
// }Png;

 struct ppm{
	char code;
	int max;
	int largura;
	int altura;
 	struct pixel **imagem;
}*Ppm;


void ler_ppm(struct ppm *Ppm){

		int i, j;
		FILE *arquivo;

		char nome_arq[50];
    printf("entre com o nome do arquivo\n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arq);
        exit(1);
    }


		fscanf(arquivo, "%s", &Ppm->code);
		fscanf(arquivo, "%d", &Ppm->largura);
		fscanf(arquivo, "%d", &Ppm->altura);
		fscanf(arquivo, "%d", &Ppm->max);

		for (i = 0; i < Ppm->altura; i++) {
			 for (j = 0; j < Ppm->largura; j++) {
					 fscanf(arquivo, "%d", &Ppm->imagem[i][j].r);
					 fscanf(arquivo, "%d", &Ppm->imagem[i][j].g);
					 fscanf(arquivo, "%d", &Ppm->imagem[i][j].b);
			 }

		fclose(arquivo);
	 }



}


int main(int argc, char const *argv[])
{
	ler_ppm(Ppm);
	return 0;
}
