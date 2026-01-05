/* ----- necessary elements ----- */
#define F_MAXLEN 128
const char fname[] = "zigzag";

const unsigned int w = 2048;
const unsigned int h = 2048;
/* ------------------------------ */



void bg_btow(FILE *f,
             const unsigned int x_beg,
             const unsigned int x_end,
             const unsigned int y_beg,
             const unsigned int y_end)
{
    unsigned int x;
    unsigned int y;

    for (y = y_beg; y < y_end; y++) {
        for (x = x_beg; x < x_end; x++) {
            ppmgen_add_pixel_grey(f, (x+y) % 256);
        }
    }
}

void bg_btow_inv(FILE *f,
                 const unsigned int x_beg,
                 const unsigned int x_end,
                 const unsigned int y_beg,
                 const unsigned int y_end)
{
    unsigned int x;
    unsigned int y;

    for (y = y_end; y > y_beg; y--) {
        for (x = x_end; x > x_beg; x--) {
            ppmgen_add_pixel_grey(f, (y-x) % 256);
        }
    }
}


/* ----- necessary function ----- */
void ppmgen_make_picture(FILE *f)
{
    ppmgen_add_header(f);

    bg_btow    (f, 0, w, 0,       h/4);
    bg_btow_inv(f, 0, w, h/4,     h/2);
    bg_btow    (f, 0, w, h/2,     h*(3/4.0));
    bg_btow_inv(f, 0, w, h*(3/4), h);
}
