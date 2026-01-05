#include <stdio.h>
#include <stdlib.h>
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

void ppmgen_terminate_if(const int cond,
                         const char *msg);

void ppmgen_make_picture(FILE *f); /* user-implemented */

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

void ppmgen_terminate_if(const int cond,
                         const char *msg)
{
    if (cond) {
        printf("PPMGen - FATAL: %s\n", msg);
        abort();
    }
}

/* ------------------------------------------------------------ */


int main(void)
{
    const unsigned int flen = sizeof(fname)/sizeof(fname[0]);
    char file[F_MAXLEN] = {0};
    char confirm[4] = {0};
    FILE *f = NULL;

    if (flen > F_MAXLEN - 4) {
        fprintf(stderr,
                "File name \"%s\" is longer than %d characters! (%d)\n",
                fname,
                F_MAXLEN - 4,   /* -4 for ".ppm" */
                flen);
        return EXIT_FAILURE;
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
            return EXIT_SUCCESS;
        }
    }

    fclose(f);
    f = fopen(file, "wb");

    if (f == NULL) {
        printf("Failed to open %s! Exiting...\n", file);
        return EXIT_FAILURE;
    }

    ppmgen_make_picture(f);

    fclose(f);
    printf("Generated %s\n", file);
    return EXIT_SUCCESS;
}
