#include "splashkit.h"
#include <stdio.h>

void swap_1(int x, int y) //local swap using a temporary variable 
{
    int temp = x;
    x = y;
    y = temp;

    printf("In swap peocedure: X = %d, Y = %d\n",x,y);
}

void swap_2(int *x, int *y) //global Swap using pointers
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swap_3(int &x, int &y) //global swap  using references
{
    int temp = x;
    x = y;
    y = temp;
}

int main()
{
    int x = 5;
    int y = 10;

    swap_1(x,y);
    printf("\nswap 1: X = %d, Y = %d\n",x,y);

    swap_2(&x,&y);  //references of x and y are passed since it wouldn't work other wise
    printf("\nswap 2: X = %d, Y = %d\n",x,y);

    swap_3(x,y);
    printf("\nswap 3: X = %d, Y = %d",x,y);
}


