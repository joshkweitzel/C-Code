#include <stdio.h>

int address_find() {
    int x = 5;
    int y = 5;

    int *p = &x;
    printf("Address of x is: %p\n", p);

    p = &y;
    printf("Address of y is: %p\n", p);

    return 0;
}
_Bool array_compare(int arr1[], int arr2[], int n){
	if (n <= 0){
		return 1;
	} else if (arr1[n - 1] == arr2[n - 1]){
        printf("a");
		return array_compare(arr1, arr2, n - 1);
	} else {
		return 0;
	}
}

int user_input(void){
    int input = 0;
    printf("Enter a fucking number: ");
    scanf("%d", &input);
    return input;
}
/*
int main(){
    int testarr[] = {1, 2, 4, 5};
    

}*/