/*
 * Copyright (c) 2019-2021 Paul Hindt
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#if defined(BM_WINDOWS)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#endif

#include "sprite.h"
#include "font.h"
#include "resource.h"
#include "main.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>

#define FONT_BASE 32
#define FONT_NULL 127
#define FONT_PX 7
#define FONT_COLS 16
#define FONT_ROWS 6

void font_print(engine_t *eng, i32 x, i32 y, f32 scale, const char *str, ...)
{
	va_list args;
	char text[TEMP_STRING_MAX];
	i32 c = 0;
	i32 fx, tu, tv;

	if (str == NULL)
		return;
	if (*str == '\0')
		return;

	va_start(args, str);
	vsprintf(text, str, args);
	va_end(args);

	game_resource_t *rsrc = eng_get_resource(eng, "font_7px");
	sprite_t *font_sprite = (sprite_t *)(rsrc->data);
	while (text[c] != '\0') {
		if (text[c] >= FONT_BASE && text[c] < FONT_NULL) {
			fx = text[c] - FONT_BASE;
			tu = (f32)(fx % FONT_COLS) * FONT_PX;
			tv = (f32)(fx / FONT_COLS) * FONT_PX;
			SDL_Rect src = {tu, tv, FONT_PX, FONT_PX};
			SDL_Rect dst = {x, y, FONT_PX * scale, FONT_PX * scale};
			SDL_RenderCopy((SDL_Renderer *)eng->renderer,
				       font_sprite->texture, &src, &dst);
			x += FONT_PX * scale;
		}
		c++;
	}
}

#ifdef _CRT_SECURE_NO_WARNINGS
#undef _CRT_SECURE_NO_WARNINGS
#endif
