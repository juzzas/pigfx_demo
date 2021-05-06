/*
  Copyright 2021, Justin Skists <justin.skists@juzza.co.uk>

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
  (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <math.h>
#include <z80.h>

#include "blip1.h"
#include "background.h"



int main(void)
{
        int i;
        float p, x, y;
        int bx, by;
        
        printf("\x1b[2J");
        //printf("\x1b[#10;10;20;20r");
        printf("\x1b[=20h"); /* 320x240 VGA */
        printf("\x1b[=0f");  /* 8x8 font */
        

        printf("\x1b[#1;32;32;16A");
        for (i = 0; i < background_rle_bin_len; i++)
            printf("%02x;", background_rle_bin[i]);

        printf("\x1b[#2;32;16;16a");
        for (i = 0; i < blip1_bin_len; i++)
            printf("%02x;", blip1_bin[i]);

        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("Why have a ZX Spectrum Next when you can have sprites on a RC2014 PI Terminal?\n");

        
        x = 150*cos(0);
        y = 100;

        printf("\x1b[58;5;16m");  /* ink 16 is transparent, in this sprite */
        printf("\x1b[=2m");       /* set transparent drawing mode */

        //print background pic bitmap #1
        for (bx = 0; bx < 10; bx++)
            for (by = 0; by < 8; by++)
                printf("\x1b[#1;%d;%dd", bx * 32, by * 32);
        
        
        // creeate sprite #1 from bitmap #2
        printf("\x1b[#1;2;%d;%ds", x, y);

        
        do
        {
            
            for (p = 0.0; p < 360.0; p += 2.0)
            {            
                x = 100*cos(p * (M_PI/180.0)) + 120;
                y = 75*sin(p * (M_PI/180.0))  + 100;
                
                printf("\x1b[#1;%d;%dm", (int)x, (int)y);
                z80_delay_ms(20);
            }
        }
        while(1);

        return 0;
}
