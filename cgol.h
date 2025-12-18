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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Reference
 * =========
 * See https://en.wikipedia.org/wiki/Conway's_Game_of_Life.
 */

/* Macros
 * ======
 */

// Define the version string.
#define CGOL_VERSION "@version@"

// Define a buffer size for the error string.
#define CGOL_ERRSTR_LEN 256

// Access the grid of an instance at coordinates y and x.
#define GRID_AT(instance, y, x) instance->grid[y*instance->xsize+x]

// Access the real grid at coordinates y and x.
#define RGRID_AT(instance, y, x) ((GRID_AT(instance, y, x)) & 0x1)

// Access the superposed grid at coordinates y and x.
#define SGRID_AT(instance, y, x) ((GRID_AT(instance, y, x)) & 0x2)

// Access the grid of an instance with a modified xsize.
#define MGRID_AT(instance, xsize, y, x) instance->grid[y*xsize+x]

// Access the real modified grid at coordinates y and x.
#define MRGRID_AT(instance, xsize, y, x) ((MGRID_AT(instance, xsize, y, x)) & 0x1)

// Access the modified superposed grid at coordinates y and x.
#define MSGRID_AT(instance, xsize, y, x) ((MGRID_AT(instance, xsize, y, x)) & 0x2)

/* Types and Structures
 * ====================
 */

// Define a type for cells.
typedef uint8_t cell;

// Define the main data structure.
struct cgol {
    unsigned long t;
    size_t ysize;
    size_t xsize;
    cell *grid;
};

// Define a enum for error numbers.
enum cgol_err {
    SUCCESS = 0,
    OUT_OF_MEMORY = 1,
    OUT_OF_BOUNDS = 2,
    NULL_PTR = 3,
};

/* Globals
 * =======
 */

// Declare a global error variable.
extern enum cgol_err cgol_errno;

/* Library Functions
 * =================
 */

// Print the current error and exit accordingly.
void cgol_enderr(void);

// Initialise a new cgol structure.
struct cgol *cgol_new(size_t ysize, size_t xsize);

// Resize an instance.
struct cgol *cgol_renew(struct cgol *instance, size_t ysize, size_t xsize);

// Free an instance.
void cgol_free(struct cgol *instance);

// Perform one tick in a cgol instance.
enum cgol_err cgol_tick(struct cgol *instance);

// Shift the view of an instance.
enum cgol_err cgol_yshift(struct cgol *instance, size_t shamt);
enum cgol_err cgol_xshift(struct cgol *instance, size_t shamt);

// Get/set a cell of an instance.
int cgol_isalive(struct cgol *instance, size_t y, size_t x);
enum cgol_err cgol_awaken(struct cgol *instance, size_t y, size_t x);
enum cgol_err cgol_kill(struct cgol *instance, size_t y, size_t x);

// Place part of one instance into another.
enum cgol_err cgol_place(struct cgol *src, size_t srcy, size_t srcx, struct cgol *dst, size_t dsty, size_t dstx);
