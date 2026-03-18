#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (n < 1);

    printf("%i\n", collatz(n));
}

int collatz(int n)
{
    // Base case
    if (n == 1)
        return 0;
    // Even numbers
    else if (n % 2 == 0)
        return collatz(n / 2) + 1;
    // Odd numbers
    else
        return collatz(3 * n + 1) + 1;
}
