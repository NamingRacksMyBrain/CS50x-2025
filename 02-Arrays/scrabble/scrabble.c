#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int cal_score(string word);

// Scores assigned to each letter of the alphabet
int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // Prompt the user for 2 words
    string word1 = get_string("Player1: ");
    string word2 = get_string("Player2: ");

    // Calculate the score for each word
    int score1 = cal_score(word1);
    int score2 = cal_score(word2);

    // Compare scores and print the winner
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int cal_score(string word)
{
    // Initialize score
    int score = 0;
    
    // Calculate score for each character
    for (int i = 0; i < strlen(word); i++)
    {
        // If the character is UPPER
        if (isupper(word[i]))
        {
            score += scores[word[i] - 'A']; // 'A' is difinitely better than 65
        }

        // If the character is lower
        else if (islower(word[i]))
        {
            score += scores[word[i] - 'a']; // 'a' is definitely better than 97
        }
    }
    return score;
}
