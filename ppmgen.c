#include <stdio.h>
#include <string.h>

/* -------------------- The API for PPMGen -------------------- */

void ppmgen_add_header(FILE *f);

void ppmgen_add_pixel_colors(FILE *f,
                             const unsigned char r,
                             const unsigned char g,
                             const unsigned char b);

void ppmgen_add_pixel_grey(FILE *f,
                           const unsigned char s);
void ppmgen_skip_pixel(FILE *f);


/* -------------------- Files for pictures -------------------- */


/* #include "./ppmcodes/zigzag.c" */
/* #include "./ppmcodes/noise.c" */
#include "./ppmcodes/bwnoise.c"


/* ---------------------- Implementations --------------------- */

void ppmgen_add_header(FILE *f)
{
    fprintf(f, "P6\n%d %d\n255\n", w, h);
}

void ppmgen_add_pixel_colors(FILE *f,
                             const unsigned char r,
                             const unsigned char g,
                             const unsigned char b)
{
    fputc(r, f);
    fputc(g, f);
    fputc(b, f);
}

void ppmgen_add_pixel_grey(FILE *f,
                           const unsigned char s)
{
    fputc(s, f);
    fputc(s, f);
    fputc(s, f);
}

void ppmgen_skip_pixel(FILE *f)
{
    fgetc(f);
    fgetc(f);
    fgetc(f);
}


/* ------------------------------------------------------------ */


int main(void)
{
    const unsigned int flen = sizeof(fname)/sizeof(fname[0]);
    char file[F_MAXLEN] = {0};
    char confirm[4] = {0};
    FILE *f = NULL;

    if (flen > F_MAXLEN) {
        fprintf(stderr,
                "File name \"%s\" is longer than %d characters! (%d)\n",
                fname,
                F_MAXLEN - 4,   /* -4 for ".ppm" */
                flen);
        return 1;
    }

    sprintf(file, "%s.ppm", fname);

    f = fopen(file, "rb");

    if (f != NULL) {
        printf("File \"%s\" already exists! Type \"yes\" to overwrite.\n>",
               file);
        fgets(confirm, 4, stdin);
        confirm[3] = '\0';

        if (strcmp(confirm, "yes")) {
            puts("Aborted.");
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    f = fopen(file, "wb");

    if (f == NULL) {
        printf("Failed to open %s! Exiting...\n", file);
        return 1;
    }

    ppmgen_make_picture(f);

    fclose(f);
    printf("Generated %s\n", file);
    return 0;
}
