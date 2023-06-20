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
static int str_size(poly *p) {
    int term_size = 2;  // length of 'z^*'
    int length;
    int degree = p->degree;
    int first_sign = 1 - GET_SIGN(p, degree);  // sign = 0 (negative) -> 1, sign = 1 (positive) -> 0


    switch (degree) {
        case 0:
            return 1 + first_sign;  // Just a '1' with a possible '-' in front
        case 1:
            // "-z + 1" or "z + 1" = 6/5
            return 3 + term_size + first_sign - (mode == NORMAL);  // First term needs no exponent
        default:
            length = 3 + term_size + first_sign - (mode == NORMAL);  // Value of last two terms
            degree -= 2;  // from now on degree will track how many terms are remaining to be accounted for

            int exp_len = 1;
            int num_fit = 9;
            degree -= 8;
            if (degree > 0) {
                length += 8 * (3 + term_size + exp_len);  // 8 terms of exp_len 1
            } else {
                length += (8 + degree) * (3 + term_size + exp_len);  // whatever the degree was terms of exp_len 1
                return length;
            }

            while (exp_len++ < 7) {  // 10**9 < max int value
                num_fit *= 10;  // amount of exponents that have length exp_len

                if ((degree -= num_fit) > 0) {
                    length += num_fit * (3 + term_size + exp_len);
                } else {
                    length += (num_fit + degree) * (3 + term_size + exp_len);
                    return length;
                }
            }
    }
    return -1;  // If the exponent had so many terms it doesn't fit (which isn't possible), return a -1
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
 * poly_str returns a null terminated string giving a human readable representation of a polynomial (in the same form as
 * poly_str_cp).
 *
 * @param p polynomial to represent
 * @return pointer to the string
 */
char *poly_str(poly *p) {

}
