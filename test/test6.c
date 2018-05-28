/**
 * move(A,C);
 * 
 * hanoi_m(A,B,C,n)
 * 1.hanoi_m(A,C,B,n-1) 
 * 2.move(A,C) 
 * 3.hanoi_m(B,A,C,n-1)
 * 
 */
#include <stdio.h>

void move(char X, char Y)
{
    printf("move disk from %c to %c\n", X, Y);
}

void hanoi_m(char X, char Y, char Z, int num)
{
    if (num == 1)   move(X,Z);
    else
    {
        hanoi_m(X, Z, Y, num-1);
        move(X,Z);    
        hanoi_m(Y, X, Z, num-1);
    }
}


int Fibonacci(int n)
{
    if (n == 1 || n == 2)  return 1;
    return Fibonacci(n-1)+Fibonacci(n-2);
}

int main(int argc, char const *argv[])
{
    int layer;
    printf("Input the layer of hanoi tower:");
    scanf("%d", &layer);
    printf("Run %d layers of hanoi tower:\n", layer);
    hanoi_m('A','B','C', 3);
    printf("\n\n");

    printf("Input the layer of fibonacci:");
    scanf("%d", &layer);
    printf("Run %d layers of fibonacci:\n", layer);
    printf("Answer = %d\n", Fibonacci(layer));
    getchar();getchar();
    return 0;
}
