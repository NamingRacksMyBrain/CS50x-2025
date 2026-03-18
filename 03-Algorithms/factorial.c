#include <cs50.h>
#include <stdio.h>

int f(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (n < 0);
    printf("%i\n", f(n));
}

int f(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return f(n - 1) * n;
}
