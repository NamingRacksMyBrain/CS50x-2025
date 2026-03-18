#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
} candidate;

int main(void)
{
    const int num = 3;
    candidate candidates[num];

    for (int i = 0; i < num; i++)
    {
        candidates[i].name = get_string("Name: ");
        candidates[i].votes = get_int("Votes: ");
    }

    int highest_vote = 0;
    string highest_person = "";
    for (int i = 0; i < num; i++)
    {
        if (candidates[i].votes > highest_vote)
        {
            highest_vote = candidates[i].votes;
            highest_person = candidates[i].name;
        }
    }
    printf("%s\n", highest_person);
}
