#include <cs50.h> // typedef char *string; (define type "string", which is the address of a character)
#include <stdio.h>

int main(void)
{
    string s = "HI!";      // this line of code equals to --> char *s = "HI!";
    // A string is really the address of its first character
    printf("%p\n", s);     // s is a pointer
    printf("%p\n", &s[0]); // s[0] is a char
    printf("%p\n", &s[1]); // s[1] is a char
    printf("%p\n", &s[2]); // s[2] is a char
    printf("%p\n", &s[3]); // s[3] is a char
}
