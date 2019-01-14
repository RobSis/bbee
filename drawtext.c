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

#include <math.h>
#include <string.h>
#include "bb.h"

#define ETIME 650000
#define RATE 60
static char *mesg;
static char *lastmesg;
static char pos, lastpos;
#define MAXPOS (ETIME1)
#define STATE (TIME-starttime)
#define N 10000
#define ETIME1 2500000


void dvojprujezd(int starttime, char *text2, char *text1)
{
    int pos = (getwidth(2) * strlen(text1) + 1);
    centerprint(-pos / 2 + (aa_imgwidth(context) + pos * 1.2) * STATE / (endtime - starttime), 2 * aa_imgheight(context) / 3, 2, 255, text1, 0);
    pos = (getwidth(2) * strlen(text2) + 1);
    centerprint(aa_imgwidth(context) + pos / 2 - (aa_imgwidth(context) + pos * 1.2) * STATE / (endtime - starttime), aa_imgheight(context) / 3, 2, 255, text2, 0);
}

void message(char *text, int starttime)
{
    if (STATE > 0 && STATE < MAXPOS) {
    double pp = STATE * M_PI / MAXPOS * 2;
    double width = (1 + cos(pp)) * 5 + 2;
    int pos = aa_imgheight(context) - aa_imgheight(context) * STATE / MAXPOS;
    if (width <= 0)
        return;
    centerprint(aa_imgwidth(context) / 2, pos, width, sin(pp / 2) * 255, text, 0);
    }
}

static float xpos, xpos1, f, t;

#define TTIME1 80
#define TTIME 100
#define G 0.02
#define AMP 40

void ctrllepic(int i)
{
    for (; i; i--) {
    t++;
    f += G,
        f *= 0.96;
    if (t < TTIME) {
        if (t < TTIME1)
        f -= xpos / (double) AMP;
        else
        f -= xpos / (double) AMP / 2;
        xpos += f;
    }
    else {
        xpos1 += f;
        xpos += G;
    }
    if (xpos < 0)
        xpos = 0, f = -f;
    }
}

void drawlepic(char *mesg)
{
    print(0, xpos1 * aa_imgheight(context), aa_imgwidth(context) / (double) strlen(mesg), aa_imgheight(context) * xpos, font, 255, mesg);
}

void initlepic()
{
    t = 0;
    f = 0;
    xpos = 0;
    xpos1 = 0;
}
