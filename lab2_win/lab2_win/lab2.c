//SYSC 2006 - Lab 2 Solution template

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include the necessary header for _Bool
#include "lab2.h"

/* Replace these lines with your information */ 
  const char* author = "Joshua Weitzel"; 
  const char* student_number = "101301965"; 

// Type your solution to exercise 1 inside the body of the function. You need to update the return statement
int alarm_clock(int day,_Bool vacation){
  if (day == 0 || day == 6){
    if (vacation == true){
      return -1;
    } else {
      return 10;
    }
  } else if (1 <= day <= 5){
    if (vacation == true){
      return 10;
    } else {
      return 7;
    }
  }
}

// Type your solution to exercise 2 inside the body of the function.
void count_replace(int value){
  for (int i = 1; i <= value; i++){
    if (i % 3 == 0 && i % 5 == 0){
      printf("FizzBuzz ");
    } else if (i % 3 == 0) {
      printf("Fizz ");
    } else if (i % 5 == 0){
      printf("Buzz ");
    } else {
      int printnum = i;
      printf("%d ", printnum);
    }
  } 
}

// Type your solution to exercise 3 inside the body of the function. You need to update the return statement
_Bool is_prime(int value){
  if (value <= 1){
    return false;
  } else {
    for (int i = 2; i < value; i++){
      if (value % i == 0){
        return false;
      }
    }
  }
  return true;
}

// Type your solution to exercise 4 inside the body of the function. You need to update the return statement
int sum_even(int value){
  int even_count = 0;
  for (int i = 1; i <= value; i++){
    if (i % 2 == 0){
      even_count += i;
    }
  }
  return even_count;
}