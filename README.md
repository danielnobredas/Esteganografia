# Esteganografia

Aplicação feita com C, para as disciplinas de Introdução a Técnicas de Programção e Pratícas de Técnicas de Programação  


### Instalação

```sh
$ git clone https://github.com/danielnobredas/Esteganografia
$ cd Esteganografia
$ make
```
### Usando a aplicação

```sh
./steg -e -i <input-file> -f <format> <image>
```
-e indica que o programa deve rodar em modo de codificador (encoder)
- i <input-file> indica o arquivo de entrada (input) a ser codificado na imagem
-f <format> indica o formato da imagem a ser usada como hospedeira para a mensagem. Os
valores possíveis para <format> são: bmp ou ppm
<image> imagem a ser usada como hospedeira para a mensagem
