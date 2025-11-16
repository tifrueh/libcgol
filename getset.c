/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

int cgol_isalive(struct cgol *instance, size_t y, size_t x) {
    if (y < 0 || y >= instance->ysize || x < 0 || x >= instance->xsize) {
        cgol_errno = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    }
    return instance->grid[y*instance->xsize+x];
}

enum cgol_err cgol_awaken(struct cgol *instance, size_t y, size_t x) {
    if (y < 0 || y >= instance->ysize || x < 0 || x >= instance->xsize) {
        cgol_errno = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    }
    instance->grid[y*instance->xsize+x] = 1;
    return SUCCESS;
}

enum cgol_err cgol_kill(struct cgol *instance, size_t y, size_t x) {
    if (y < 0 || y >= instance->ysize || x < 0 || x >= instance->xsize) {
        cgol_errno = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    }
    instance->grid[y*instance->xsize+x] = 0;
    return SUCCESS;
}
