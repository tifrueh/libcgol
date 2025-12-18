/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in ../cgol.h
 */

#ifndef __CGOL_TEST_H_
#define __CGOL_TEST_H_

#include <stdio.h>
#include "cgol.h"

// Define useful ANSI color codes.
#define ANSI_GOOD "\033[32m"
#define ANSI_BAD  "\033[31m"
#define ANSI_RST  "\033[0m"

// Define general testing macros.
#define TEST_PASS do {\
    test_cnt++;\
    good_cnt++;\
    printf("%sTest %4d: PASS%s\n", ANSI_GOOD, test_cnt, ANSI_RST);\
} while (0)

#define TEST_FAIL do {\
    test_cnt++;\
    printf("%sTest %4d: FAIL%s\n", ANSI_BAD, test_cnt, ANSI_RST);\
} while (0)

#define TEST_FINISH do {\
    int isgood = (good_cnt == test_cnt);\
    char *col = (isgood) ? (ANSI_GOOD) : (ANSI_BAD);\
    int perc = (good_cnt * 100) / test_cnt;\
    printf("\nPASSED: %s%d%% [%d/%d]%s\n", col, perc, good_cnt, test_cnt, ANSI_RST);\
    return !isgood;\
} while (0)


// Define global test counters.
int test_cnt = 0;
int good_cnt = 0;

#endif
