/* Copyright (C) 2025 Timo Früh
 *
 * See full copyright notice in ../cgol.h
 */

#include "test.h"

#define TEST_YSIZE 256
#define TEST_XSIZE 128

int main(void) {

    struct cgol *test = cgol_new(TEST_YSIZE, TEST_XSIZE);
    TEST_PASS;

    // Test for correct initial time.
    if (test->t == 0) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: incorrect initial time\n  expected: %d\n  received: %ld\n",
            __FILE__, __LINE__,
            0, test->t
        );
    }

    // Test for correct sizes.
    if (test->ysize == TEST_YSIZE && test->xsize == TEST_XSIZE) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: incorrect initial size\n  expected: y=%d, x=%d\n  received: y=%ld, x=%ld\n",
            __FILE__, __LINE__,
            TEST_YSIZE, TEST_XSIZE, test->ysize, test->xsize
        );
    }

    // Try writing into last element of grid.
    test->grid[TEST_YSIZE*TEST_XSIZE-1] = 0x1;
    TEST_PASS;

    // Free test structure.
    cgol_free(test);

    TEST_FINISH;
}
