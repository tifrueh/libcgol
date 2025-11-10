/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in cgol.h
 */

#include "cgol.h"

enum cgol_err cgol_errno = SUCCESS;
char cgol_errstr[CGOL_ERRSTR_LEN] = "";

void cgol_enderr(void) {
    switch (cgol_errno) {
    case SUCCESS:
        exit(0);
    default:
        puts(cgol_errstr);
        exit(cgol_errno);
    }
};
