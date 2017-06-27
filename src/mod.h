#ifndef MOD_H
#define MOD_H
#define RGB_COMPONENT_COLOR 255



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>


/*STRUCTS PPM*/
typedef struct {
    unsigned char r, g, b;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;
/*STRUCTS BMP*/
#define MAX 500
#define RGB_COMPONENT_COLOR 255

typedef struct tagBITMAPFILEHEADER{
	uint16_t bfType;
	uint32_t bfsize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBitts;
}BITMAPFILEHEADER;

typedef struct tagRGBQUAD{
	uint32_t rgbBlue;
	uint32_t rgbGreen;
	uint32_t rgbRed;
	uint32_t rgbReserved;
}RGBQUAD;

typedef struct tagBITMAPINFOHEADER{
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
}BITMAPINFOHEADER;

typedef struct tagBITMAPINFO
{
	BITMAPFILEHEADER bmiHeader;
	RGBQUAD bmiColors;
}BITMAPINFO;

#pragma pack(push, 1)
typedef struct {
  BITMAPFILEHEADER fileHeader;
  BITMAPINFOHEADER infoHeader;
  RGBQUAD *imageData;
} BMPFile;
#pragma pack(pop)


/*STRUCT FILE*/
typedef struct{
	char nomArq[80];
	float tamanhoArq;
}Arquivo;

PPMImage *ler_ppm(FILE *arquivo, int *max, int *coluna, int *linha);

BMPFile lerBitMap(FILE *filePtr);

void salvarPPM(const char *filename, PPMImage *img);

int getBit (unsigned char byte, int pos);

void setBit (unsigned char* byte, int pos, int valor);

char* converteBin (unsigned char byte);

PPMImage *codificarMsg(FILE *arquivo, PPMImage *image);

char *convertFileToText(FILE *arquivo);

BMPFile *codificarMsgBMP(FILE *arquivo, BMPFile *imagem);

void decodificarMsg(PPMImage *imagem);

#endif
