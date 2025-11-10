/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

struct cgol *cgol_new(size_t ysize, size_t xsize) {
    struct cgol *new = malloc(sizeof(struct cgol));
    new->t = 0;
    new->ysize = ysize;
    new->xsize = xsize;
    new->grid = calloc(ysize*xsize, sizeof(cell));
    return new;
}
