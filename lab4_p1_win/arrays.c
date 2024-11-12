/* SYSC 2006 Lab 4. 

 * Incomplete implementations of the functions that will be coded during the lab.
 */

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "arrays.h"

/* Exercise 1. */

/* Return the average magnitude of the signal represented by
 * the n doubles in x[]. 
 * This function assumes that parameter n is >= 1.
 */
double avg_magnitude(double x[], int n)
{
    double sum = 0;
    for (int i = 0; i <= n - 1; i++ ){
        if (x[i] < 0){
            sum += x[i] * -1;
        } else {
            sum += x[i];
        }
    }
    return sum / n;
}

/* Exercise 2. */

/* Return the average power of the signal represented by
 * the n doubles in x[].
 * This function assumes that parameter n is >= 1.
 */
double avg_power(double x[], int n)
{
    double sum = 0;
    for (int i = 0; i <= n - 1; i++){
        sum += x[i] * x[i];
    }
    return sum / n;
}

/* Exercise 3. */

/* Return the largest of the n doubles in arr[]. 
 * This function assumes that parameter n is >= 1.
 */
double maxi(double arr[], int n)
{
    double largest = arr[0];
    for (int i = 0; i <= n - 1; i++){
        if (arr[i] > largest){
            largest = arr[i];
        }
    }
    return largest;
}

/* Exercise 4. */

/* Return the smallest of the n doubles in arr[]. 
 * This function assumes that parameter n is >= 1.
 */
double mini(double arr[], int n)
{
   double smallest = arr[0];
    for (int i = 0; i <= n - 1; i++){
        if (arr[i] < smallest){
            smallest = arr[i];
        }
    }
    return smallest;
}

/* Exercise 5. */

/* Normalize the n doubles in x[]. 
 * This function assumes that parameter n is >= 2, and that at least
 * two of the values in x[] are different.
 */
void normalize(double x[], int n)
{
    double min = mini(x, n);
    double max = maxi(x, n);

    for (int i = 0; i <= n - 1; i++){
        x[i] = (x[i] - min) / (max - min);
    }
}
