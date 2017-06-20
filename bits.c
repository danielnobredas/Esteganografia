#include <stdio.h>
#include <stdlib.h>


int getBit (unsigned char byte, int pos) {
	int valor;
	unsigned char mascara;
	mascara = 0x1 << pos;
	valor = byte & mascara;
	return valor >> pos;
}

void setBit (unsigned char* byte, int pos, int valor) {
	unsigned char mascara;
	unsigned char novoByte;
	mascara = 0x1 << pos;
	(*byte) &= (~mascara);
	mascara = (unsigned char) valor << pos;
	(*byte) |= mascara;
}

char* converteBin (unsigned char byte) {
	char* binario = (char*) malloc(9*sizeof(char));
	for (int i = 7; i >= 0; --i)
	{
		binario[7-i] = (getBit(byte, i)==0?'0':'1');
	}
	binario[8] = '\0';
	return binario;
}

int main(int argc, char const *argv[])
{
	unsigned char letra = 'B';
	printf("%c - %d - %s\n", letra, letra, converteBin(letra));
	
	unsigned char saida = 'A';
	printf("%c - %d - %s\n", saida, saida, converteBin(saida));
	
	for (int i = 0; i <= 7; ++i)
	{
		setBit(&saida,i,getBit(letra, i));
	}
	printf("%c - %d - %s\n", saida, saida, converteBin(saida));
	return 0;
}