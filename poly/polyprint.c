/**
 * Created by Curtis Barnhart on 2023-05-28
 */

#include "polyprint.h"

/**
 * str_size returns the size that a string returned by poly_str would be (not including the null terminator).
 *
 * @param p polynomial being represented
 * @param mode whether the polynomial is being represented using 'z' as the term or with the Euler formula 'e^(ix)'.
 * @return
 */
static int str_size(poly *p, poly_str_mode mode) {
    int term_size;  // length of 'z' or '(e^(ix))' depending on mode
    int degree = p->degree;
    int first_sign = GET_SIGN(p, degree) - 1;  // sign = 0 (negative) -> -1, sign = 1 (positive) -> 0

    switch (mode) {
        case NORMAL:
            term_size = 1;
        case EULER:
            term_size = 8;
    }

    switch (degree) {
        case 0:
            return 1 + first_sign;  // Just a '1' with a possible '-' in front
        case 1:
            return 2 + term_size + first_sign;  // First term needs no exponent
        default:
            for (int i = 0; i < ; ++i) {  // 2**9 < max int value

            }
    }
}

/**
 * poly_str_cp transforms a polynomial into a human readable string (eg z^3 + z^2 - z - 1) and copies the string into
 * the given buffer (with no null terminator).
 * Returns the length of the string.
 *
 * @param p polynomial to represent
 * @param buffer buffer to place the string into
 * @return number of characters in string (including null terminator)
 */
char *poly_str_cp(poly *p, char *buffer) {

}

/**
 * poly_str_euler_cp transforms a polynomial into a human readable string written in terms of Euler's formula
 * (eg (e^(ix))^3 + (e^(ix))^2 - e^(ix) - 1) and copies the string into the given buffer (with no null terminator).
 * Returns the length of the string.
 *
 * @param p
 * @param buffer
 * @return the length of the string
 */
char *poly_str_euler_cp(poly *p, char *buffer) {

}

/**
 * poly_str returns a null terminated string giving a human readable representation of a polynomial (in the same form as
 * poly_str_cp).
 *
 * @param p polynomial to represent
 * @return pointer to the string
 */
char *poly_str(poly *p) {

}

/**
 * poly_str_euler returns a null terminated string giving a human readable representation of a polynomial (in the same
 * form as poly_str_euler_cp)
 *
 * @param p polynomial to represent
 * @return pointer to the string
 */
char *poly_str_euler(poly *p) {

}