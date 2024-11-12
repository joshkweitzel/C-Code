#include <stdio.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
    double z;
} coord_t;

/* num_coord_less_value_1 returns the number of members of the
coord_t structure "coord" that are less than "value". */
int num_coord_less_value_1 (coord_t coord, double value) {
    //We can use an array of pointers teehee to iterate through the members
    double *members[] = {&coord.x, &coord.y, &coord.z};
    int num_less = 0;
    for(int i = 0; i < 3; i++){
        if(*members[i] < value){
            num_less++;
        }
    }
    return num_less;
}

int main(void){
    coord_t boyhouse;
    boyhouse.x = 21.5;
    boyhouse.y = 23.4;
    boyhouse.z = 10.1;
    printf("Test: %d", num_coord_less_value_1(boyhouse, 22));
}
