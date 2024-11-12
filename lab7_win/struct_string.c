#include "struct_string.h"
#include <stdlib.h>  // abs(x)
#include <stdio.h>   // printf

// Exercise 1
/* Print fraction pointed to by pf in the form a/b. */
void print_fraction(const fraction_t* pf)
{
   printf("%d/%d", pf->num, pf->den);
}

/* Return the greatest common divisor of integers a and b; 
   i.e., return the largest positive integer that evenly divides 
   both values.  Copy this function from Lab 6.  No changes are needed.
*/
int gcd(int a, int b)
{
   /* Euclid's algorithm, using iteration and calculation of remainders. */
   int q = abs(a);
   int p = abs(b);
   int r = (q % p);

   while(r != 0){
      q = p;
      p = r;
      r = (q % p);
   }
	return p;
}


/* Updates the fraction pointed to by pf to its reduced form.

   This means that:
   (1) if the numerator is equal to 0 the denominator is always 1.
   (2) if the numerator is not equal to 0 the denominator is always
	   positive, and the numerator and denominator have no common
	   divisors other than 1.

   In other words,
   (1) if the numerator is 0 the denominator is always changed to 1.
   (2) if the numerator and denominator are both negative, both values
	   are made positive, or if the numerator is positive and the 
	   denominator is negative, the numerator is made negative and the 
	   denominator is made positive.
   (3) the numerator and denominator are both divided by their greatest
	   common divisor. 
*/
void reduce(fraction_t* pf)
{
   int common_div = gcd(pf->num, pf->den);
   pf->num /= common_div;
   pf->den /= common_div;

   if(pf->num < 0 && pf->den < 0){
      pf->num = abs(pf->num);
      pf->den = abs(pf->den);
   } else if(pf->den < 0){
      pf->den *= -1;
      pf->num *= -1;
   }
}

/* Returns a pointer to a fraction (by reference) with numerator a and denominator b.
   Print an error message and terminate the calling program via exit()
   if the denominator is 0.
   The fraction returned by this function is always in reduced form.
*/
void make_fraction(int a, int b, fraction_t* pf)
{
   if(b == 0){
      exit(1);
   } else {
      pf->num = a;
      pf->den = b;
      reduce(pf);
   }
}

/* Returns by reference a pointer to the sum of fractions pointed to by pf1 and pf2.
   The fraction returned by this function is always in reduced form
 */
void add_fractions(const fraction_t* pf1, const fraction_t* pf2, fraction_t* psum)
{
   make_fraction((pf1->num * pf2->den) + (pf1->den * pf2->num), pf1->den * pf1->num, psum);
}

/* Returns by reference a pointer to the product of fractions pointed to by pf1 and pf2.
   The fraction returned by this function is always in reduced form
 */
void multiply_fractions(const fraction_t* pf1, const fraction_t* pf2, fraction_t* pprod)
{
   make_fraction(pf1->num * pf2->num, pf1->den * pf2->den, pprod);
}

// Exercise 2

/* Update the GPA of the student pointed to by studentp, assuming the student has numGrades.	Note that update_gpa must call calc_gpa for each student. */
void update_gpa(student_t *studentp, int numGrades) {
  studentp->gpa = calc_gpa(studentp->grades, numGrades);
}

/* Calculate the GPA associated with the numGrades pointed to by gradesp.
   The implementation must use a walking pointer. 
   If the total weight of all courses is 0, a GPA of 0 is returned. */
float calc_gpa(const grade_t *gradesp, int numGrades) {
   int tot_credit = 0;
   int tot_gp = 0;
   for(int g = 0; g < numGrades; g++){
      tot_credit += gradesp[g].weight;
      tot_gp += gradesp[g].gp * gradesp[g].weight;
   }
	return tot_gp/tot_credit;
}

// Exercise 3

/* Calculate how many time the target character appears in string my_str
For example:
count_char("Hello world ",'l') return 3
count_char("Hello world ",'a') return 0
Your implementation must use array-indexing. 
*/

int count_char(const char * my_str, char target){
   int num_times = 0;
   for(int c = 0; my_str[c] != '\0'; c++){
      if(my_str[c] == target){
         num_times += 1;
      }
   }
   return num_times;
}

// Exercise 4

/* Calculate how many time the target character appears in string my_str
For example:
count_char("Hello world ",'l') return 3
count_char("Hello world ",'a') return 0
Your implementation must use walking pointer.
*/


int count_char_wp(const char * my_str, char target){
int num_times = 0;
   for(const char *c = my_str; *c != '\0'; ++c){
      if(*c == target){
         num_times += 1;
      }
   }
   return num_times;
}