#include <stdio.h>
#include <string.h>

void add_header(FILE *f);


/* ----- Files for pictures ----- */

#include "./ppmcodes/zigzag.c"
/* #include "./ppmcodes/noise.c" */
/* #include "./ppmcodes/bwnoise.c" */

/* ------------------------------ */

void add_header(FILE *f)
{
    fprintf(f, "P6\n%d %d\n255\n", w, h);
}


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
                F_MAXLEN,
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

    make_picture(f);

    fclose(f);
    printf("Generated %s\n", file);
    return 0;
}
