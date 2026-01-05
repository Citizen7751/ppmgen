# PPM Generator

A very simple [.ppm](https://netpbm.sourceforge.net/doc/ppm.html) file generator I hacked together. It can only generate files, so cannot be used to view them. Linux has builtin support the viewing these files, but Windows doesn't, so I rely on GIMP and GNU Emacs. I made this to be just able to proceduraly generate pictures.

The different codes for the pictures are in ```ppmcodes/```. The sources have to be included in ```ppmgen.c``` in order to be processed.

---

*Dependences:*

- a working C compiler (anything supporting at least C89)
  
  
*Build with GCC on Windows:* ```gcc -o ppmgen.exe ppmgen.c```


---

*License:* MIT License
