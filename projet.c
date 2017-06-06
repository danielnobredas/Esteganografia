#include <stdio.h>
#include "mod.h"

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

typedef{
	int **imagem;
}Png;

typedef{
	int **imagem;
}Ppm;

int main(int argc, char const *argv[])
{
	
	return 0;
}