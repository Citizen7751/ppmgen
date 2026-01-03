# PPM Maker

A very simple [.ppm](https://netpbm.sourceforge.net/doc/ppm.html) file generator I hacked together. It can only generate files, so cannot be used to view them. Linux has builtin support the viewing these files, but Windows doesn't, so I rely on GIMP and GNU Emacs. I made this to be just able to proceduraly generate pictures.

---

*Dependences:*
    - a working C compiler (anything starting from C89)
  
  
*Build with GCC on Windows:* ```gcc -o ppmmaker.exe ppmmaker.c -Wall -Wextra```


---

*License:* MIT License
