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


typedef struct tagBITMAPINFO
{
	BITMAPFILEHEADER bmiHeader;
	RGBQUAD bmiColors;
}BITMAPINFO;

/*static PPMImage *ler_ppm(char *code, int *max, int *coluna, int *linha) {

    FILE *arquivo;
    PPMImage *imagem;
    char nome_arq[50];
    printf("entre com o nome do arquivo\n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arq);
        exit(1);
    }

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
    
    // if (fread(imagem->data, 3 * imagem->x, imagem->y, arquivo) != imagem->y) {
    //      fprintf(stderr, "Erro em carregar a imagem '%s'\n", nome_arq);
    //      exit(1);
    // }

    fclose(arquivo);
    return imagem;

}*/




int main(int argc, char const *argv[])
{
	char code[3]; //o código para saber se a imagem é ascii ou binária
	int max; //o valor máximo de tonalidade de cada pixel
	int larg, alt; // largura e altura da imagem em pixe

	PPMImage *imagem;
	imagem = ler_ppm(code, &max, &larg, &alt);
	writePPM("imd2.ppm",imagem);
	return 0;
}