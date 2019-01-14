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
#include <stdlib.h>
#include <ctype.h>
#include <aalib.h>
#include "bb.h"

int finish_stuff, starttime, endtime;
int dual = 0;
static int quitnow = 0;
int scene;
aa_context *context;
aa_renderparams *params;
int TIME;
tl_timer *scenetimer;
struct font *font;

double getwidth(double size)
{
    double height = aa_imgheight(context) / size;
    double width = height * (double) aa_imgwidth(context) * 0.75 / aa_imgheight(context) * aa_mmheight(context) / aa_mmwidth(context);
    return (width);
}

void centerprint(int x, int y, double size, int color, char *text, int mode)
{
    if (!dual || !mode) {
        double height = aa_imgheight(context) / size;
        double width = height * (double) aa_imgwidth(context) * 0.75 / aa_imgheight(context) * aa_mmheight(context) / aa_mmwidth(context);
        print(x - (width * strlen(text)) / 2, y - height / 2, width, height, font, color, text);
    } else {
        if (mode & 1) {
            double height = aa_imgheight(context) / size;
            double width = height * (double) aa_imgwidth(context) * 0.75 / aa_imgheight(context) * aa_mmheight(context) / aa_mmwidth(context);
            print(x / 2 - (width * strlen(text)) / 2, y - height / 2, width, height, font, color, text);
        }
        if (mode & 2) {
            double height = aa_imgheight(context) / size;
            double width = height * (double) aa_imgwidth(context) * 0.75 / aa_imgheight(context) * aa_mmheight(context) / aa_mmwidth(context);
            print(aa_imgwidth(context) / 2 + x / 2 - (width * strlen(text)) / 2, y - height / 2, width, height, font, color, text);
        }
    }
}

static void (*control1) (int);
static int called = 0;

static void mycontrol(void *data, int i)
{
    called = 1;
    if (control1 != NULL)
        control1(i);
}
static void mycontrol2(void *data, int i)
{
    ((void (*) (int))data)(i);
}

int bbupdate()
{
    int ch;
    tl_update_time();
    TIME = tl_lookup_timer(scenetimer);
    tl_process_group (syncgroup, NULL);
    ch = aa_getkey(context, 0);
    switch (ch)
    {
        case AA_ESC:
        case 'q':
            finish_stuff = quitnow = 1;
    }
    return (ch);
}

void timestuff(int rate, void (*control) (int), void (*draw) (void), int maxtime)
{
    int waitmode = 0, t;
    tl_timer *timer;
    bbupdate();
    /*starttime = TIME; */
    endtime = starttime + maxtime;
    timer = tl_create_timer();
    if (control == NULL)
    {
        rate = -40;
    }
    if (rate < 0) {
        waitmode = 1, rate = -rate;
        control1 = control;
        tl_set_multihandler(timer, mycontrol, NULL);
    }
    else
        tl_set_multihandler(timer, mycontrol2, control);
    tl_set_interval(timer, 1000000 / rate);
    tl_add_timer(syncgroup, timer);
    tl_reset_timer(timer);
    tl_slowdown_timer (timer, starttime - TIME);
    if (control != NULL)
        control(1);
    while (!quitnow && TIME < endtime)
    {
        called = 0;
        bbupdate();
        t = tl_process_group(syncgroup, NULL);
        if (TIME > endtime)
            break;
        if (!called && waitmode)
            tl_sleep(t);
        else {
            if (draw != NULL)
                draw();
        }
    }
    starttime = endtime;
    tl_free_timer(timer);
}

int bbinit(int argc, char **argv)
{
    aa_defparams.supported|= AA_NORMAL_MASK | AA_BOLD_MASK | AA_DIM_MASK;
    aa_parseoptions(NULL, NULL, &argc, argv);
    if (argc < 2 || (strcmp(argv[1], "-torus") != 0 && strcmp(argv[1], "-plasma") != 0 && strcmp(argv[1], "-fractal") != 0))
    {
        printf("Usage: bbee -torus|-plasma|-fractal [aaoptions]\n\n");
        printf("Options:\n"
               "  -torus         run torus effect\n"
               "  -plasma        run plasma effect\n"
               "  -fractal       run fractal effect\n\n"
               "AAlib options:\n%s\n", aa_help);
        exit(1);
    }
    context = aa_autoinit(&aa_defparams);
    if (!context)
    {
        printf("Failed to initialize aalib\n");
        exit(2);
    }
    if (!aa_autoinitkbd(context, 0))
    {
        aa_close(context);
        printf("Failed to initialize keyboard\n");
        exit(3);
    }
    if (strcmp(argv[1], "-fractal") == 0) {
        scene = 0;
    } else if (strcmp(argv[1], "-plasma") == 0) {
        scene = 1;
    } else if (strcmp(argv[1], "-torus") == 0) {
        scene = 2;
    }
    aa_hidecursor(context);
    return 1;
}

int bb(void)
{
    aa_gotoxy(context, 0, 0);
    introscreen();
    params = aa_getrenderparams();
    aa_render(context, params, 0, 0, 1, 1);
    font = uncompressfont( /*context->params.font */ &aa_font16);
    scenetimer = tl_create_timer();
    srand(time(NULL));
    do
    {
        bbupdate();
        aa_resize (context);
        switch (scene)
        {
            case 0: fractal();
                    break;
            case 1: plasma();
                    break;
            case 2: torus();
                    break;
        }
        if (quitnow)
        goto quit;
    } while (scene);
  quit:;
    aa_close(context);
    return (0);
}
