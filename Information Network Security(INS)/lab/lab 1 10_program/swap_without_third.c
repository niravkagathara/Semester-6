#include <stdio.h>
void swapa(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
    printf("After swapping: x = %d, y = %d\n", a, b);
}
void main()
{
    int x, y;
    printf("Enter two number: ");
    scanf("%d %d", &x, &y);
    printf("Before swapping: x = %d, y = %d\n", x, y);
    swapa(x, y);
}
