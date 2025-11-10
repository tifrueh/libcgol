/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

void cgol_free(struct cgol *instance) {
    free(instance->grid);
    free(instance);
}
