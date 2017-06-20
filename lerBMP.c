#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"

unsigned char *lerBitMap(BITMAPINFOHEADER *bitmapInfoHeader,FILE *filePtr){

    BITMAPFILEHEADER bitmapFileHeader;
    unsigned char *imagem;
    unsigned char auxRGB; //variavel auxiliar

    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);    
    fread(bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,filePtr);

    fseek(filePtr, bitmapFileHeader, bfOffBitts, SEEK_SET); //Procura o inicio dos dados bitmap

    imagem = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

        if (!imagem) {
         fprintf(stderr, "Erro ao alocar memória\n");
         exit(1);
    }

    fread(imagem,bitmapInfoHeader->biSizeImage,filePtr);

    if (imagem==NULL) {
     	fprintf(stderr, "Erro ao alocar memória\n");
        exit(1);
    }

   for(int i=0; i<bitmapInfoHeader->biSizeImage;i+=3){ //navega pelos pixels
   	auxRGB = imagem[i];
   	imagem[i] = imagem[i+2];
   	imagem[i+2] = auxRGB;
   }

   unsigned char significativo;   
    significativo=imagem[i];
    printf("%s\n",imagem[i]);

   return imagem;
}