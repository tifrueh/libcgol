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
    return RGRID_AT(instance, y, x);
}

enum cgol_err cgol_awaken(struct cgol *instance, size_t y, size_t x) {
    if (y < 0 || y >= instance->ysize || x < 0 || x >= instance->xsize) {
        cgol_errno = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    }
    GRID_AT(instance, y, x) = 0x1;
    return SUCCESS;
}

enum cgol_err cgol_kill(struct cgol *instance, size_t y, size_t x) {
    if (y < 0 || y >= instance->ysize || x < 0 || x >= instance->xsize) {
        cgol_errno = OUT_OF_BOUNDS;
        return OUT_OF_BOUNDS;
    }
    GRID_AT(instance, y, x) = 0x0;
    return SUCCESS;
}
