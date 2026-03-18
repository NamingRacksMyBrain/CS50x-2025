#include <stdio.h>

const int SIZE = 5;

int main(void)
{
    // Declare an array
    int numbers[SIZE];
    numbers[0] = 1;

    // Populate an array
    for (int i = 1; i < SIZE; i++)
    {
        numbers[i] = numbers[i - 1] * 2;
    }

    // Print out the numbers
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i\n", numbers[i]);
    }
}
