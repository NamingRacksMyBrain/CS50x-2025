/* A program that calculates the approximate grade level needed to comprehend some text.
Print as output “Grade X” where “X” is the grade level computed.
If the grade level is >= 16, your program should output “Grade 16+”;
If the grade level is < 1, your program should output “Before Grade 1”.*/

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Declare functions
int cal_letters(string text);
int cal_words(string text);
int cal_sentences(string text);
int cal_index(string text);

int main(void)
{
    // Prompt the user for text
    string text = get_string("Text: ");

    // Calculate the index
    int index = cal_index(text);

    // Print the grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Calculate Coleman-Liau index
int cal_index(string text)
{
    int letters = cal_letters(text);
    int words = cal_words(text);
    int sentences = cal_sentences(text);

    /*
    Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
    L is the average number of letters per 100 words in the text;
    S is the average number of sentences per 100 words in the text.
    */
    double L = 100 * (double) letters / (double) words;
    double S = 100 * (double) sentences / (double) words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}

// Get the number of letters in the text
int cal_letters(string text)
{
    int len = strlen(text);
    int letters = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Get the number of words in the text
int cal_words(string text)
{
    int len = strlen(text);
    int space = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            space++;
        }
    }
    return space + 1;
}

// Get the number of sentences in the text
int cal_sentences(string text)
{
    int len = strlen(text);
    int sentences = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentences++;
        }
    }
    return sentences;
}
