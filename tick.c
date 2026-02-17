/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

static enum cgol_err tick_cell(struct cgol* instance, size_t y, size_t x) {

    // Count the number of adjacent and alive blocks.
    unsigned char adj_alive = 0;
    for (size_t i = y-1; i <= y+1; i++) {
        for (size_t j = x-1; j <= x+1; j++) {
            if (
                  (i == y && j == x)
                || i > instance->ysize
                || j > instance->xsize
            ) continue;
            adj_alive += RGRID_AT(instance, i, j);
        }
    }

    // Update second bit of cell accordingly.
    switch (adj_alive) {
    case 2:
        GRID_AT(instance, y, x) = RGRID_AT(instance, y, x) | (RGRID_AT(instance, x, y) << 1);
        break;
    case 3:
        GRID_AT(instance, y, x) = RGRID_AT(instance, y, x) | (0x1U << 1);
        break;
    default:
        GRID_AT(instance, y, x) = RGRID_AT(instance, y, x) & ~(0x1U << 1);
        break;
    }

    return SUCCESS;
}

enum cgol_err cgol_tick(struct cgol *instance) {

    // Tick all cells.
    for (size_t i = 0; i < instance->ysize; i++) {
        for (size_t j = 0; j < instance->xsize; j++) {
            cgol_errno = tick_cell(instance, i, j);
            if (cgol_errno != SUCCESS) return cgol_errno;
        }
    }

    // Update all cells.
    for (size_t i = 0; i < instance->ysize*instance->xsize; i++) {
        instance->grid[i] >>= 1;
    }

    // Increase time variable.
    instance->t++;

    return SUCCESS;
}
