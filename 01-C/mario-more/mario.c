#include <cs50.h>
#include <stdio.h>

int get_valid_int(void);
void print_pyramid(int height);
void print_row(int n, int height);

int main(void)
{
    int height = get_valid_int();
    print_pyramid(height);
}

// Print a pyramid with height of height
void print_pyramid(int height)
{
    for (int i = 1; i < height + 1; i++)
    {
        print_row(i, height);
    }
}

// Print the nth row of a pyramid
void print_row(int n, int height)
{
    for (int i = 0; i < height - n; i++)
    {
        printf(" ");
    }

    for (int j = 0; j < n; j++)
    {
        printf("#");
    }

    printf("  ");

    for (int k = 0; k < n; k++)
    {
        printf("#");
    }
    printf("\n");
}

// Get an integer between 1 & 8(inclusive)
int get_valid_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while ((n < 1) || (n > 8));

    return n;
}
