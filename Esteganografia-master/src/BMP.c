#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"

/*Leitura do arquivo bmp*/
BMPFile lerBitMap(FILE *arquivo){

  BITMAPINFOHEADER bitmapInfoHeader;
  BITMAPFILEHEADER bitmapFileHeader;
  RGBQUAD *imageData;
  // unsigned char auxRGB; //variavel auxiliar
  BMPFile imagem;
//le e armazena o cabeçalho
  fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,arquivo);

  if (bitmapFileHeader.bfType !=0x4D42){
    fclose(arquivo);
    fprintf(stderr, "Imagem Invalida \n");
    exit(1);
  }
//Verifica se a imagem esta comprimida, caso esteja o programa fecha
  fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,arquivo);

  if (bitmapInfoHeader.biCompression != 0) {
    fclose(arquivo);
    fprintf(stderr, "Compressão não suportada");
    exit(1);
  }


  fseek(arquivo, bitmapFileHeader.bfOffBitts, SEEK_SET); //Procura o inicio dos dados bitmap

  imageData = (RGBQUAD*)malloc(bitmapInfoHeader.biSizeImage);

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
  //Navega pelos pixeis da imagem
  for(int i = 0; i<bitmapInfoHeader->biSizeImage;i+=3){
    auxRGB = imagem[i];
    imagem[i] = imagem[i+2];
    imagem[i+2] = auxRGB;
  }

  return imagem;
}
//Converte a string em binario e adiciona o valor aos bits dos pixeis da imagem
BMPFile *codificarMsgBMP(FILE *arquivo, BMPFile *imagem){

  char *msg;
  char *msgBits;

  int i;

  int countString = strlen(msg) * sizeof(char) * 8;
  int counter = 0;

  msgBits = malloc(countString);
  *msgBits=converteBin(*msg);

  if (imagem) {

    // unsigned char  imgSize = imagem.infoHeader;

    //caso o texto for maior que a imagem
    if ((strlen(msg) + sizeof(char)) * sizeof(char) > imagem->infoHeader.biSizeImage * sizeof(char)) {
      fprintf(stderr, "Mensagem muito grande.");
      exit(1);
    } else {
      while (counter < countString) {
        *(msgBits + counter) = ((*msg) % 2);
        *msg = *msg >> 1;
        counter++;
      }

      int index = 0;
//Adiciona os pixeis da mensagem ao RGB da imagem
      for (i = 0; i < countString; i++) {
        if (*(msgBits + index) != (imagem->imageData[i].rgbBlue % 2)) {
          imagem->imageData[i].rgbBlue = (imagem->imageData[i].rgbBlue & 0xFE) | *(msgBits + index);
        }
        index++;

        if (*(msgBits + index) != (imagem->imageData[i].rgbGreen % 2)) {
          imagem->imageData[i].rgbGreen = (imagem->imageData[i].rgbGreen & 0xFE) | *(msgBits + index);
        }
        index++;

        if (*(msgBits + index) != (imagem->imageData[i].rgbRed % 2)) {
          imagem->imageData[i].rgbRed = (imagem->imageData[i].rgbRed & 0xFE) | *(msgBits + index);
        }
        index++;

        if (*(msgBits + index) != (imagem->imageData[i].rgbReserved % 2)) {
          imagem->imageData[i].rgbReserved = (imagem->imageData[i].rgbReserved & 0xFE) | *(msgBits + index);
        }
        index++;

      }
    }
  }

return imagem;
}
