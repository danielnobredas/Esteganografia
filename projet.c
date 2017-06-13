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

 typedef struct {
	int r, g, b;
} pixel;

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
 	pixel **imagem;
}Ppm;


// void ler_ppm(struct ppm *Ppm){
//
// 		int i, j;
// 		FILE *arquivo;
//
// 		char nome_arq[50];
//     printf("entre com o nome do arquivo\n");
//     scanf("%s", nome_arq);
//
//     if ((arquivo = fopen(nome_arq, "r")) == NULL) {
//         printf("Erro ao abrir o arquivo %s\n", nome_arq);
//         exit(1);
//     }
//
//
// 		fscanf(arquivo, "%s", Ppm->code);
// 		fscanf(arquivo, "%d", Ppm.largura);
// 		fscanf(arquivo, "%d", Ppm.altura);
// 		fscanf(arquivo, "%d", Ppm.max);
//
// 	// 	for (i = 0; i < Ppm.altura; i++) {
// 	// 		 for (j = 0; j < Ppm.largura; j++) {
// 	// 				 fscanf(arquivo, "%d", &Ppm.imagem[i][j].r);
// 	// 				 fscanf(arquivo, "%d", &Ppm.imagem[i][j].g);
// 	// 				 fscanf(arquivo, "%d", &Ppm.imagem[i][j].b);
// 	// 		 }
// 	//  }
//
// 		fclose(arquivo);
//
// }


void ler_ppm(pixel imagem[MAX][MAX], char *code, int *max, int *coluna, int *linha) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("entre com o nome do arquivo\n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arq);
        exit(1);
    }

    fscanf(arquivo, "%s", code);
    fscanf(arquivo, "%d", coluna);
    fscanf(arquivo, "%d", linha);
    fscanf(arquivo, "%d", max);

    for (i = 0; i < *linha; i++) {
        for (j = 0; j < *coluna; j++) {
            fscanf(arquivo, "%d", &imagem[i][j].r);
            fscanf(arquivo, "%d", &imagem[i][j].g);
            fscanf(arquivo, "%d", &imagem[i][j].b);
        }
    }

    fclose(arquivo);
}


int main(int argc, char const *argv[])
{
	pixel imagem[MAX][MAX]; //cria uma matriz de pixeis para armazenar a imagem
	char code[3]; //o código para saber se a imagem é ascii ou binária
	int max; //o valor máximo de tonalidade de cada pixel
	int larg, alt; // largura e altura da imagem em pixeis
	ler_ppm(imagem, code, &max, &larg, &alt);
	for (int i = 0; i < alt; i++) {
		for(int j = 0.; j < larg; j++){
			printf("O pixel é: %d %d %d\n", imagem[i][j].r, imagem[i][j].g, imagem[i][j].b);
		}
	};
	return 0;
}
