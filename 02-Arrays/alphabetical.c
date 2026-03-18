#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) // Quick review: ARGument Count & ARGument Vector
{
    // Get user's input('word')
    if (argc != 2)
    {
        printf("Please input a word\n");
        return 1; // Error 1: user doesn't input 'word'
    }
    string text = argv[1];
    int len = strlen(text);

    // Check if 'word' consists of only alphabets
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            printf("Please input a valid word\n");
            return 2; // Error 2: 'word' consists of something else(numbers, @#!...)
        }
    }

    // Iterate through each element in the string
        // Check if it is alphabetical
    for (int i = 1; i < len; i++)
    {
        if (text[i] < text[i - 1])
        {
            printf("no\n");
            return 0;
        }
    }

    // Print out yes
    printf("yes\n");
}
