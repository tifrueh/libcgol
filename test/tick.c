/* Copyright (C) 2026 Timo Früh
 *
 * See full copyright notice in ../cgol.h
 */

#include "test.h"

#define TEST_YSIZE 32
#define TEST_XSIZE 16

int main(void) {

    struct cgol* test;

    // Test death by underpopulation.
    test = cgol_new(TEST_YSIZE, TEST_XSIZE);
    cgol_awaken(test, 10, 10);
    cgol_awaken(test, 12, 12);
    cgol_tick(test);
    if (!cgol_isalive(test, 10, 10)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: failed to kill cell by underpopulation\n",
            __FILE__, __LINE__
        );
    }
    if (!cgol_isalive(test, 12, 12)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: failed to kill cell by underpopulation\n",
            __FILE__, __LINE__
        );
    }

    // Test reproduction.
    cgol_free(test);
    test = cgol_new(TEST_YSIZE, TEST_XSIZE);
    cgol_awaken(test, 10, 10);
    cgol_awaken(test, 11, 10);
    cgol_awaken(test, 11, 11);
    cgol_tick(test);
    if (cgol_isalive(test, 10, 11)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: failed to awaken cell when necessary\n",
            __FILE__, __LINE__
        );
    }

    // Test death by overpopulation.
    cgol_free(test);
    test = cgol_new(TEST_YSIZE, TEST_XSIZE);
    cgol_awaken(test, 10, 10);
    cgol_awaken(test, 10, 11);
    cgol_awaken(test, 10, 12);
    cgol_awaken(test, 11, 11);
    cgol_awaken(test, 11, 12);
    cgol_tick(test);
    if (!cgol_isalive(test, 11, 11)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: failed to kill cell by overpopulation\n",
            __FILE__, __LINE__
        );
    }

    // Free test structure.
    cgol_free(test);

    TEST_FINISH;
}
