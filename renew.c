/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

// Rearrange cells into new dimensions.
static int rearrange(struct cgol *instance, size_t ysize, size_t xsize) {
    // Store new value in second bit.
    for (int i = 0; (i < ysize) && (i < instance->ysize); i++) {
        for (int j = 0; (j < xsize) && (j < instance->xsize); j++) {
            instance->grid[i*xsize+j] &= instance->grid[i*instance->xsize+j] << 1;
        }
    }
    // Update cells.
    for (int i = 0; i < ysize*xsize; i++) {
        instance->grid[i] >>= 1;
    }
    return SUCCESS;
}

// Zero out new area after size increase.
static int zero(struct cgol *instance, size_t ysize, size_t xsize) {
    for (int i = instance->ysize*instance->xsize; i < ysize*xsize; i++) {
        instance->grid[i] = 0;
    }
    return SUCCESS;
}

// Resize an instance.
struct cgol *cgol_renew(struct cgol *instance, size_t ysize, size_t xsize) {

    if (ysize*xsize > instance->ysize*instance->xsize) {

        // If new size is bigger, realloc before rearrange.
        instance->grid = realloc(instance->grid, ysize*xsize);
        zero(instance, ysize, xsize);
        rearrange(instance, ysize, xsize);

    } else if (ysize*xsize > instance->ysize*instance->xsize) {

        // If new size is smaller, rearrange before realloc.
        rearrange(instance, ysize, xsize);
        instance->grid = realloc(instance->grid, ysize*xsize);

    } else {

        // If size remains the same, only rearrange.
        rearrange(instance, ysize, xsize);
    }

    // Update sizes.
    instance->ysize = ysize;
    instance->xsize = xsize;

    return instance;
}
