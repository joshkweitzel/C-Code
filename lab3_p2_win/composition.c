/* SYSC 2006 Lab 3, Part 2.
 *
 * Incomplete implementations of the functions that will be coded during the lab. 
 */

#include <stdlib.h>
#include <math.h>

#include "composition.h"

/* Returns n! for n >= 0. (0! is defined to be 1.)
   Note that the return type is int, and n! grows rapidly as n increases,
   so this function should only be used for fairly small values of n; 
   i.e., if signed ints are implemented as 32-bit values, n must be <= 12.
*/
int factorial(int n)
{
    if (n == 0){
        return 1;
    } else {
        for (int i = n - 1; i > 0; i--){
            n *= i;
        }
        return n;
    }
}

/* Returns the number of different ordered subsets of k objects picked
from a set of n objects, for n > 0, k > 0, n >= k.
 */
int ordered_subsets(int n, int k)
{
    return factorial(n) / (factorial(n - k));
}

/* Returns the binomial coefficient (n k); that is, the number of 
   combinations of k objects that can be chosen from a set of n objects, 
   for n > 0, k > 0, n >= k.
 */
int binomial(int n, int k)
{
    return ordered_subsets(n, k) / (factorial(k));
}