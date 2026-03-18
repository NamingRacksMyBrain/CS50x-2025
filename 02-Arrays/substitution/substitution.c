#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool repeat(char key_upper[]);
void key_to_char(char key_cp[], char key_upper[]);

int main(int argc, string argv[])
{
    char key_upper[26];
    char key_cp[26];
    // Get key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Validate key
    else
    {
        // Copy key
        for (int i = 0; i < 26; i++)
        {
            key_cp[i] = argv[1][i];
        }
        key_to_char(key_cp, key_upper);
        // Check key length
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            // Check for non-alphabetic characters
            for (int i = 0; i < 26; i++)
            {
                if (!isalpha(argv[1][i]))
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
            }
            // Check for repeated characters(case-insensitive)
            if (repeat(key_upper))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    // Get plaintext
    string plaintext = get_string("plaintext: ");

    // Encipher
    // Print ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Preserve case
        if (isupper(plaintext[i]))
        {
            printf("%c", toupper(key_upper[plaintext[i] - 'A']));
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", tolower(key_upper[plaintext[i] - 'a']));
        }
        // Leave non-alphabetic chararcters as-is
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}

// Check if the key contains repeated characters
bool repeat(char key_upper[])
{
    int char_count[26];
    // Initialize to all 0
    for (int i = 0; i < 26; i++)
    {
        char_count[i] = 0;
    }
    // Record counts
    for (int i = 0; i < 26; i++)
    {
        char_count[(int) key_upper[i] - 'A']++;
    }
    // Check if each number in numbers[] appear only once
    for (int i = 0; i < 26; i++)
    {
        if (char_count[i] != 1)
        {
            return true;
        }
    }
    return false;
}

// Translate the key into all UPPER case
void key_to_char(char key_cp[], char key_upper[])
{
    for (int i = 0; i < 26; i++)
    {
        if (isupper(key_cp[i]))
        {
            key_upper[i] = key_cp[i];
        }
        else
        {
            key_upper[i] = key_cp[i] - 'a' + 'A';
        }
    }
}
