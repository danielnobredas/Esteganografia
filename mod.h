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
    char r, g, b;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;
/*STRUCTS BMP*/
#define MAX 500
#define RGB_COMPONENT_COLOR 255

typedef unsigned long DWORD;
typedef unsigned long UINT;
typedef unsigned long BYTE;
typedef unsigned long LONG;
typedef unsigned long WORD;
typedef unsigned long BITMAPFILEHEADER;

typedef struct tagBITMAPFILEHEADER{
	uint16_t bfType;
	uint32_t bfsize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBitts;
}tagBITMAPFILEHEADER;

typedef struct tagRGBQUAD{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
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

/*STRUCT FILE*/
typedef struct{
	char nomArq[80];
	float tamanhoArq;
}Arquivo;

static PPMImage *ler_ppm(FILE *arquivo,char code, int *max, int *coluna, int *linha);

unsigned char *lerBitMap(BITMAPINFOHEADER *bitmapInfoHeader,FILE *filePtr);

void writePPM(const char *filename, PPMImage *img);

int getBit (unsigned char byte, int pos);

void setBit (unsigned char* byte, int pos, int valor);

char* converteBin (unsigned char byte);

#endif
