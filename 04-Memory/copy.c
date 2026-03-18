#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // malloc()
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");

    char *t = malloc(strlen(s) + 1); // t is the pointer of a 4-byte memory(the address of the 1st byte)
    if (t == NULL) // Run out of memory!
    {
        return 1;
    }

    strcpy(t, s); // Destination comes first, then source (t <-- s)

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // Print string twice
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
}
