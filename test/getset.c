/* Copyright (C) 2026 Timo Früh
 *
 * See full copyright notice in ../cgol.h
 */

#include "test.h"

#define TEST_YSIZE 256
#define TEST_XSIZE 128

int main(void) {

    struct cgol *test = cgol_new(TEST_YSIZE, TEST_XSIZE);
    enum cgol_err err;

    // Test awaken.
    err = cgol_awaken(test, 3, 10);
    if (err == SUCCESS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: failed to awaken cell with errno %d\n",
            __FILE__, __LINE__, err
        );
    }

    // Test kill.
    err = cgol_kill(test, 3, 10);
    if (err == SUCCESS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: failed to kill cell with errno %d\n",
            __FILE__, __LINE__, err
        );
    }

    // Test isalive.
    int isalive = cgol_isalive(test, 3, 10);
    if (!isalive) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: read incorrect cell value\n  expected: %d\n  received %d\n",
            __FILE__, __LINE__, 0, isalive
        );
    }

    // Test bounds checks.
    err = cgol_awaken(test, TEST_YSIZE, 0);
    if (err == OUT_OF_BOUNDS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: didn't catch out-of-bounds y on awaken\n",
            __FILE__, __LINE__
        );
    }
    err = cgol_awaken(test, 0, TEST_XSIZE);
    if (err == OUT_OF_BOUNDS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: didn't catch out-of-bounds x on awaken\n",
            __FILE__, __LINE__
        );
    }
    err = cgol_kill(test, TEST_YSIZE, 0);
    if (err == OUT_OF_BOUNDS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: didn't catch out-of-bounds y on kill\n",
            __FILE__, __LINE__
        );
    }
    err = cgol_kill(test, 0, TEST_XSIZE);
    if (err == OUT_OF_BOUNDS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: didn't catch out-of-bounds x on kill\n",
            __FILE__, __LINE__
        );
    }
    isalive = cgol_isalive(test, TEST_YSIZE, 0);
    if (isalive == OUT_OF_BOUNDS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: didn't catch out-of-bounds y on isalive\n",
            __FILE__, __LINE__
        );
    }
    isalive = cgol_isalive(test, 0, TEST_XSIZE);
    if (isalive == OUT_OF_BOUNDS) {
        TEST_PASS;
    } else {
        TEST_FAIL;
        printf(
            "  %s:%d: didn't catch out-of-bounds x on isalive\n",
            __FILE__, __LINE__
        );
    }

    // Free test structure.
    cgol_free(test);

    TEST_FINISH;
}
