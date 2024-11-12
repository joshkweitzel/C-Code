//SYSC 2006 - Lab 2 Template

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"

/* Replace these lines with your information */ 
  const char* author_main = "Joshua Weitzel"; 
  const char* student_number_main = "101301965"; 

int main(void){
  // Tests exercise 1 - Complete for a comprehensive test harness
  int expected_week_non_vac = 7;
  int expected_week_vac = 10;

  if (alarm_clock(0, false) == 10 || alarm_clock(6, false) == 10){
    printf("Weekend, non Vacation: TEST PASS. \n");
  } else {
    printf("Weekend, Non vacation: TEST FAIL. \n");
  }
  if (alarm_clock(0, true) == -1 || alarm_clock(6, true) == -1){
    printf("Weekend, Vacation: TEST PASS. \n");
  } else {
    printf("Weekend, Vacation: TEST FAIL. \n");
  }

  for(int day = 1; day <=5; day++){
    int alarm_time = alarm_clock(day, false);
    if (alarm_time == expected_week_non_vac) {
      printf("Day %d, Non vacation: TEST PASS.\n", day);
    } else {
      printf("Day %d, Non vacation: TEST FAIL.\n", day);
    }
    int alarm_weekend = alarm_clock(day, true);
    if (alarm_weekend == expected_week_vac){
      printf("Day %d, Vacation: TEST PASS. \n", day);
    } else {
      printf("Day %d, Vacation: TEST FAIL. \n", day);
    }
  }

  // Type your test cases for exercise 2. Make sure to include border line cases
  // Example test case
  count_replace(15);
  printf("\n");
  printf("Output should match: 1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz. \n");

  // Type your test cases for exercise 3. Make sure to include border line cases
if (is_prime(7) == true){
  printf("7 is prime, TEST PASS. \n");
} else {
  printf("7 is prime, TEST FAIL. \n");
}
if (is_prime(8) == false){
  printf("8 is not prime, TEST PASS. \n");
} else {
  printf("8 is not prime, TEST FAIL. \n");
}
if (is_prime(0) == true || is_prime(1) == true){
  printf("1 and 0 are not prime, TEST FAIL. \n");
} else {
  printf("1 and 0 are not prime, TEST PASS. \n");
}

  // Type your test cases for exercise 4. Make sure to include border line cases
  if (sum_even(10) == 30){
    printf("sum of even integers 1 -> 10 = 30, TEST PASS. \n");
  } else {
    printf("sum of even integers 1 -> 10 = 30, TEST FAIL. \n");
  }
  if (sum_even(1) == 0){
    printf("1 is not even, sum is 0, TEST PASS. \n");
  } else {
    printf("1 is not even, sum is 0, TEST FAIL. \n");
  }
  

  printf("Test harness finished\n");
  return EXIT_SUCCESS;
}


