// Verify if a credit card number is a valid AMEX/MASTERCARD/VISA one
#include <cs50.h>
#include <stdio.h>

bool amex(long n);
bool mastercard(long n);
bool visa(long n);
bool algorithm_check(long n);
int add_digits(int n);
long get_digit(long n, long digit_number);
long get_length(long n);

int main(void)
{
    long n = get_long("Number: ");
    if (algorithm_check(n))
    {
        if (amex(n))
        {
            printf("AMEX\n");
        }
        else if (mastercard(n))
        {
            printf("MASTERCARD\n");
        }
        else if (visa(n))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Formats
// AMEX:15        (34/37)
// MASTERCARD:16  (51/52/53/54/55)
// VISA:13/16     (4)

// Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add
// those products’ digits together. Add the sum to the sum of the digits that weren’t multiplied
// by 2. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent
// to 0), the number is valid!
bool algorithm_check(long n)
{
    int len = get_length(n);
    int sum = 0;
    // Add to sum the products' digits
    for (int i = 2; i < len + 1; i += 2)
    {
        int digit = get_digit(n, i);
        sum += add_digits(digit * 2);
    }

    // Add to sum the digits that weren't multiplied
    for (int j = 1; j < len + 1; j += 2)
    {
        int digit = get_digit(n, j);
        sum += digit;
    }

    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Get a specific digit of a number(digit_number from right to left are: 1, 2, 3...)
long get_digit(long n, long digit_number)
{
    for (long i = 0; i < digit_number - 1; i++)
    {
        n = (long) (n / 10);
    }

    return (long) (n % 10);
}

// Get the length of a number
long get_length(long n)
{
    long len = 1;
    while ((long) (n / 10) != 0)
    {
        len++;
        n = (long) (n / 10);
    }
    return len;
}

// Add the digit(s) of a number between 0 and 99
int add_digits(int n)
{
    int sum = n % 10 + (int) (n / 10);
    return sum;
}

// Identify whether the number is AMEX-formatted regarding length and start numbers
bool amex(long n)
{
    int len = get_length(n);
    if ((len == 15) && (get_digit(n, 15) == 3) &&
        ((get_digit(n, 14) == 4) || (get_digit(n, 14) == 7)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Identify whether the number is MASTERCARD-formatted regarding length and start numbers
bool mastercard(long n)
{
    int len = get_length(n);
    if ((len == 16) && (get_digit(n, 16) == 5) &&
        ((get_digit(n, 15) == 1) || (get_digit(n, 15) == 2) || (get_digit(n, 15) == 3) ||
         (get_digit(n, 15) == 4) || (get_digit(n, 15) == 5)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Identify whether the number is VISA-formatted regarding length and start numbers
bool visa(long n)
{
    int len = get_length(n);
    if (((len == 13) && (get_digit(n, 13) == 4)) || ((len == 16) && (get_digit(n, 16) == 4)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
