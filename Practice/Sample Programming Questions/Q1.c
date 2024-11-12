#include <stdio.h>
#include <stdbool.h>

/* value_num_times_1 returns true if "value" occurs at least
"num_times" times in the first "n" elements of array "arr", and false
otherwise. The solution must use array indices for full marks. */
_Bool value_num_times_1 (int arr[], int n, int value, int num_times) {
    int num_times_actual = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == value){
            num_times_actual++;
        }
    }
    if(num_times_actual >= num_times){
        return true;
    } else {
        return false;
    }
}

/* value_num_times_1 returns true if "value" occurs at least
"num_times" times in the first "n" elements of the array pointed to by
"parr", and false otherwise. The solution must use a walking pointer
for full marks. */
_Bool value_num_times_2 (int *parr, int n, int value, int num_times) {
    int num_times_actual = 0;
    for(int *p = parr; p < parr + n; ++p){
        if(*p == value){
            num_times_actual++;
        }
    }
    if(num_times_actual >= num_times){
        return true;
    } else {
        return false;
    }
}


/*
int main(void){
    int my_arr[] = {1, 1, 1, 2};
    printf("%d", value_num_times_2(my_arr, 4, 1, 3));
}
*/
