#include <stdlib.h>
#include <time.h>

/* ----- necessary elements ----- */
#define F_MAXLEN 128
const char fname[] = "noise";

const unsigned int w = 1024;
const unsigned int h = 1024;
/* ------------------------------ */



void draw_noise(FILE *f,
                const unsigned int x_beg,
                const unsigned int x_end,
                const unsigned int y_beg,
                const unsigned int y_end)
{
    unsigned int x;
    unsigned int y;

    for (y = y_beg; y < y_end; y++) {
        for (x = x_beg; x < x_end; x++) {

            fputc((rand() % 256), f);
            fputc((rand() % 256), f);
            fputc((rand() % 256), f);
        }
    }
}


/* ----- necessary function ----- */
void make_picture(FILE *f)
{
    srand(time(NULL));
    add_header(f);
    draw_noise(f, 0, w, 0, h);
}
