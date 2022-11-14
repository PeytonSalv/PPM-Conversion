# PPM-Conversion
This program will convert PPM (portable pixmap image files) into black and white. PPMs are easily manipulated because they use ASCII files to store images.

**********************************************************************************************************************************************************                                                                            HOW TO RUN

1. Use a C compiler, I am using Cygwin and Visual Studio Code.
2. Make sure all files are in the same location when trying to compile program, it will access 'image.h'
3. To compile program use ( gcc -o image image.c)
4. Below are lines you could type into terminal.


./a.out copy-ppm hq_color.ppm hq_color_copy.ppm
./a.out copy-pgm hq_gray.ppm hq_gray_copy.pgm
./a.out grayscale hq_color.ppm hq_gray.pgm
./a.out shrink hq_gray.pgm lq_gray.pgm
