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
#include <aalib.h>
#include "bb.h"

char *text;
void (*drawptr) ();

static void drawwait()
{
    aa_puts(context, (aa_scrwidth(context) - strlen(text)) / 2, aa_scrheight(context) / 2, AA_SPECIAL, text);
    aa_flush(context);
}

void draw(void)
{
    if (drawptr != NULL)
    drawptr();
    aa_render(context, params, 0, 0, aa_imgwidth(context), aa_imgheight(context));
    aa_puts(context, (aa_scrwidth(context) - strlen(text)) / 2, aa_scrheight(context) / 2, AA_SPECIAL, text);
    aa_flush(context);
}

void introscreen(void)
{
    text = "Please wait. Precalculating data";
    drawwait();
    text = "";
}
