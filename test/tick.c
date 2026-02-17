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

    // Test stable populations by the edge.
    cgol_free(test);
    test = cgol_new(TEST_YSIZE, TEST_XSIZE);
    cgol_awaken(test, 0, 0);
    cgol_awaken(test, 0, 1);
    cgol_awaken(test, 1, 0);
    cgol_awaken(test, 1, 1);
    cgol_awaken(test, 0, TEST_XSIZE-2);
    cgol_awaken(test, 0, TEST_XSIZE-1);
    cgol_awaken(test, 1, TEST_XSIZE-2);
    cgol_awaken(test, 1, TEST_XSIZE-1);
    cgol_awaken(test, TEST_YSIZE-2, TEST_XSIZE-2);
    cgol_awaken(test, TEST_YSIZE-2, TEST_XSIZE-1);
    cgol_awaken(test, TEST_YSIZE-1, TEST_XSIZE-2);
    cgol_awaken(test, TEST_YSIZE-1, TEST_XSIZE-1);
    cgol_awaken(test, TEST_YSIZE-2, 0);
    cgol_awaken(test, TEST_YSIZE-2, 1);
    cgol_awaken(test, TEST_YSIZE-1, 0);
    cgol_awaken(test, TEST_YSIZE-1, 1);
    cgol_tick(test);
    if (cgol_isalive(test, 0, 0)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: weird things going on at the top left edge\n",
            __FILE__, __LINE__
        );
    }
    if (cgol_isalive(test, 0, 15)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: weird things going on at the top right edge\n",
            __FILE__, __LINE__
        );
    }
    if (cgol_isalive(test, 15, 15)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: weird things going on at the bottom right edge\n",
            __FILE__, __LINE__
        );
    }
    if (cgol_isalive(test, 15, 0)) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: weird things going on at the bottom left edge\n",
            __FILE__, __LINE__
        );
    }

    // Free test structure.
    cgol_free(test);

    TEST_FINISH;
}
