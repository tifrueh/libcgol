/* Copyright (C) 2025 Timo Früh
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stddef.h>

/* Reference
 * =========
 * See https://en.wikipedia.org/wiki/Conway's_Game_of_Life.
 */

/* Types and Structures
 * ====================
 */

// Define a type for cells.
typedef char cell;

// Define the main data structure.
struct cgol {
    long t;
    size_t xsize;
    size_t ysize;
    cell **grid;
};

// Define a enum for error numbers.
enum cgol_err {
    SUCCESS = 0,
    OUT_OF_MEMORY,
    OUT_OF_BOUNDS,
};

/* Globals
 * =======
 */

// Declare a global error variable.
extern enum cgol_err cgol_errno;

// Declare a global error string.
extern char *cgol_errstr;

/* Library Functions
 * =================
 */

// Get an error string.
char *cgol_geterror(void);

// Initialise a new cgol structure.
struct cgol *cgol_new(size_t ysize, size_t xsize);

// Resize an instance.
struct cgol *cgol_renew(struct cgol *instance, size_t ysize, size_t xsize);

// Free an instance.
void cgol_free(struct cgol *instance);

// Perform one tick in a cgol instance.
enum cgol_err cgol_tick(struct cgol *instance);

// Shift the view of an instance downwards by a certain amount.
enum cgol_err cgol_yshift(struct cgol *instance, size_t shamt);

// Shift the view of an instance to the right by a certain amount.
enum cgol_err cgol_xshift(struct cgol *instance, size_t shamt);

// Set a cell of an instance.
enum cgol_err cgol_awaken(struct cgol *instance, size_t y, size_t x);
enum cgol_err cgol_kill(struct cgol *instance, size_t y, size_t x);

// Place one instance into another.
enum cgol_err cgol_place(struct cgol *src, struct cgol *dst, size_t y, size_t x);
