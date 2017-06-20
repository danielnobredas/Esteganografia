#ifndef MOD_H
#define MOD_H
#define RGB_COMPONENT_COLOR 255

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

/*STRUCT FILE*/
typedef struct{
	char nomArq[80];
	float tamanhoArq;
}Arquivo;

static PPMImage *ler_ppm(FILE *arquivo,char code, int *max, int *coluna, int *linha);

unsigned char *lerBitMap(BITMAPINFOHEADER *bitmapInfoHeader,FILE *filePtr);

void writePPM(const char *filename, PPMImage *img);

#endif