/**
 * Created by Curtis Barnhart on 2023-05-29.
 */

#include <limits.h>
#include <math.h>

#include "my_math.h"

/**
 * ipow returns 'base' raised to the power of 'exp'.
 *
 * @param base base to raise to a power
 * @param exp power to raise base to
 * @return 'base' raised to the power of 'exp'
 */
long ipow(long base, unsigned char exp) {
    long accumulator = 1;
    do {
        if (exp & 1) {
            accumulator *= base;
        }
        base *= base;
    } while (exp >>= 1);

    return accumulator;
}

/**
 * ipow_safe returns 'base' raised to the power of 'exp' if performing such an operation does not cause an overflow.
 * If an overflow if caused, the integer pointed to by 'err' will be set to 1 to indicate the operation could not be
 * performed, and 0 will be returned by the function.
 *
 * @param base base to raise to a power
 * @param exp power to raise base to
 * @param err pointer to an error integer which will be set to 1 if the operation caused an overflow
 * @return
 */
long ipow_safe(long base, unsigned char exp, int *err) {
    if (log((double) LONG_MAX) / log((double) base) < exp) {
        *err = 1;
        return 0;
    }
    return ipow(base, exp);
}

