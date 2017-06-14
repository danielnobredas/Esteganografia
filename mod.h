#ifndef MOD_H
#define MOD_H
#define RGB_COMPONENT_COLOR 255
typedef struct {
    char r, g, b;
} PPMPixel;

typedef struct {
     int x, y;
     PPMPixel *data;
} PPMImage;

static PPMImage *ler_ppm(char *code, int *max, int *coluna, int *linha);

void writePPM(const char *filename, PPMImage *img);

#endif