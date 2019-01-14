/*
 * BB: The portable demo
 *
 * (C) 1997 by AA-group (e-mail: aa@horac.ta.jcu.cz)
 *
 * 3rd August 1997
 * version: 1.2 [final3]
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public Licences as by published
 * by the Free Software Foundation; either version 2; or (at your option)
 * any later version
 *
 * This program is distributed in the hope that it will entertaining,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILTY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Publis License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <string.h>
#include <malloc.h>
#include <math.h>
#include "bb.h"
#include "tex.h"

static unsigned char *helpbuffer;
static int aaval = -1, colorval;
static int sstarttime;

static void do3d()
{
    int t = pow((TIME - sstarttime) / 30000 / 200.0, 1.3) * 200;
    if (t < 0)
    t = 0;
    alfa = beta = gama = t;
    beta += 90;
    alfa %= 360;
    beta %= 360;
    gama %= 360;
    disp3d();
}

static void mydraw1(void)
{
    int x, y;
    unsigned char *pos = context->imagebuffer;
    unsigned char *pos1 = helpbuffer;
    int mul2 = 255 * (255 - colorval);
    if (aaval >= 0) {
        for (y = 0; y < aa_imgheight(context); y += 1) {
            for (x = 0; x < aa_imgwidth(context); x += 1) {
                *pos = (*pos1 * colorval + ((*pos1) != 0) * mul2) >> 8;
                pos++;
                pos1++;
            }
        }
    }
    else
    clrscr();
}

void torus(void)
{
    aaval = -1;
    set_zbuff();
    helpbuffer = malloc(aa_imgwidth(context) * aa_imgheight(context));
    alfa = 0;
    beta = 90;
    gama = 0;
    centerx = 0;
    centery = 0;
    centerz = 0;
    zoom = 1.5;
    torusconstructor();
    disp3d();
    memcpy(helpbuffer, context->imagebuffer, aa_imgwidth(context) * aa_imgheight(context));
    params->dither = AA_NONE;

    drawptr = do3d;
    timestuff(0, NULL, draw, 60 * 1000000);
}
