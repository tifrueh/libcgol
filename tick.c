/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

static enum cgol_err tick_cell(struct cgol* instance, size_t y, size_t x) {

    // Count the number of adjacent and alive blocks.
    unsigned char adj_alive = 0;
    for (int i = y-1; i >= 0 && i < y+1 && i < instance->ysize; i++) {
        for (int j = x-1; j >= 0 && j < y+1 && j < instance->xsize; j++) {
            if (i == y && j == x) continue;
            adj_alive += RGRID_AT(instance, i, j);
        }
    }

    // Update second bit of cell accordingly.
    char isalive = RGRID_AT(instance, y, x);
    switch (isalive) {
    case 0:
        if (adj_alive == 3)     GRID_AT(instance, y, x) = 0x2;
    case 1:
        if (adj_alive < 2)      GRID_AT(instance, y, x) = 0x1;
        else if (adj_alive < 4) GRID_AT(instance, y, x) = 0x3;
        else                    GRID_AT(instance, y, x) = 0x1;
    }

    return SUCCESS;
}

enum cgol_err cgol_tick(struct cgol *instance) {

    // Tick all cells.
    for (int i = 0; i < instance->ysize; i++) {
        for (int j = 0; j < instance->xsize; j++) {
            cgol_errno = tick_cell(instance, i, j);
            if (cgol_errno != SUCCESS) return cgol_errno;
        }
    }

    // Update all cells.
    for (int i = 0; i < instance->ysize*instance->xsize; i++) {
        instance->grid[i] >>= 1;
    }

    // Increase time variable.
    instance->t++;

    return SUCCESS;
};
