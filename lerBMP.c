#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"

BMPFile lerBitMap(FILE *arquivo){

  BITMAPINFOHEADER bitmapInfoHeader;
  BITMAPFILEHEADER bitmapFileHeader;
  unsigned char *imageData;
  // unsigned char auxRGB; //variavel auxiliar
  BMPFile imagem;

  fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,arquivo);

  if (bitmapFileHeader.bfType !=0x4D42){
    fclose(arquivo);
    fprintf(stderr, "Imagem Invalida \n");
    exit(1);
  }

  fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,arquivo);

  // if (bitmapInfoHeader.biSize !=40){
  //   fclose(arquivo);
  //   fprintf(stderr, "Não é possivel carregar a imagem\n");
  //   exit(1);
  // }

  // if ((bitmapInfoHeader.biPlanes != 1) || (bitmapInfoHeader.biBitCount != 24)) {
  //   fclose(arquivo);
  //   fprintf(stderr, "Imagem Invalida");
  //   exit(1);
  // }


  if (bitmapInfoHeader.biCompression != 0) {
    fclose(arquivo);
    fprintf(stderr, "Compressão não suportada");
    exit(1);
  }


  fseek(arquivo, bitmapFileHeader.bfOffBitts, SEEK_SET); //Procura o inicio dos dados bitmap

  imageData = (unsigned char*)malloc(bitmapInfoHeader.biSizeImage);

  if (!imageData) {
    fprintf(stderr, "Erro ao alocar memória\n");
    exit(1);
  }

  fread(imageData,bitmapInfoHeader.biSizeImage,1,arquivo);

  if (imageData==NULL) {
    fprintf(stderr, "Erro ao alocar memória\n");
    exit(1);
  }

  imagem.fileHeader = bitmapFileHeader;
  imagem.infoHeader = bitmapInfoHeader;
  imagem.imageData = imageData;
  // for(int i = 0; i<bitmapInfoHeader->biSizeImage;i+=3){ //navega pelos pixels
  //   auxRGB = imagem[i];
  //   imagem[i] = imagem[i+2];
  //   imagem[i+2] = auxRGB;
  // }

  return imagem;
}
