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

#ifndef BB_H
#define BB_H
#include <aalib.h>
#include "timers.h"
struct font {
    int width, height;
    char *data;
};

#define clrscr() memset(context->imagebuffer,0,aa_imgwidth(context)*aa_imgheight(context))
#define textclrscr()     memset(context->textbuffer,' ',aa_scrwidth(context)*aa_scrheight(context)), memset(context->attrbuffer,AA_NORMAL,aa_scrwidth(context)*aa_scrheight(context))

extern int finish_stuff, starttime, endtime;
extern aa_context *context;
extern int dual;
extern int TIME;
extern aa_renderparams *params;
extern tl_timer *scenetimer;
extern void (*drawptr) (void);
extern struct font *font;
extern int bbsound, soundcounter;

void dvojprujezd(int, char *, char *);
void timestuff(int rate, void (*control) (int), void (*draw) (void), int maxtime);
void centerprint(int x, int y, double size, int color, char *text,int mode);
double getwidth(double);

struct font *uncompressfont(const aa_font * font);
void fastscale(char *b1, char *b2, int x1, int x2, int y1, int y2, int width1, int width2, int color);
void print(int x, int y, float width, int height, struct font *f, int color, char *text);
void draw(void);
void plasma(void);
void torus(void);
void fractal(void);
void introscreen(void);
int bbupdate();
void initplasma(void);
void message(char *text, int starttime);
void ctrllepic(int i);
int bb(void);
int bbinit(int, char **);
void drawlepic(char *mesg);
void initlepic(void);
extern int textsize;
extern char *line[];
extern void format(int);

#endif
