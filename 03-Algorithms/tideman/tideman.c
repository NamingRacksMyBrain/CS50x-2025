#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycle(int start, int end);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate to check if name matches a valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If name is a candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update ranks[]
            ranks[rank] = i;
            // Return true as the rank was successfully updated
            return true;
        }
    }
    // Otherwise return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // For the ith candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int l = i + 1; l < candidate_count; l++)
        {
            // Preferences[j][k] represent the number of voters who prefer candidate j over
            // candidate k
            preferences[ranks[i]][ranks[l]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Get pair count
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            // If candidate j is more preferred than k
            if (preferences[j][k] != preferences[k][j])
                pair_count++;
        }
    }
    // For each pair in pairs[]
    int n = 0;
    // Pairs[n] contains candidate j & k
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            // If j is more preferred than k
            if (preferences[j][k] > preferences[k][j])
            {
                // Declare winner and loser of each pair
                pairs[n].winner = j;
                pairs[n].loser = k;
                n++;
            }
            // If j is less preferred than k
            else if (preferences[j][k] < preferences[k][j])
            {
                // Declare winner and loser of each pair
                pairs[n].winner = k;
                pairs[n].loser = j;
                n++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Initialize pairs_copy[]
    pair pairs_copy[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        pairs_copy[i].winner = 0;
    }
    // Record each pair's victory strength correspondent to pairs[]
    int victory_strength[pair_count];
    // For the ith pair in pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Pairs[i].winner is candidate j
            if (j == pairs[i].winner)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    // Pairs[i].loser is candidate k
                    if (k == pairs[i].loser)
                        victory_strength[i] = preferences[j][k];
                }
            }
        }
    }
    // Sort the pairs[] in decreasing order of strength of victory
    int pair_rank = 0;
    while (pair_rank < pair_count)
    {
        // Get the max victory strength for now
        int max_victory_strength = 0;
        for (int j = 0; j < pair_count; j++)
        {
            if (victory_strength[j] > max_victory_strength)
                max_victory_strength = victory_strength[j];
        }

        for (int i = 0; i < pair_count; i++)
        {
            // Pairs[i] has the most victory strength(for now)
            if (victory_strength[i] == max_victory_strength)
            {
                // Check if pairs_copy[pair_rank] has already updated
                if (pairs_copy[pair_rank].winner == 0)
                {
                    // Update pairs_copy[pair_rank] if pairs_copy[pair_rank] remains untouched
                    pairs_copy[pair_rank] = pairs[i];
                    victory_strength[i] = 0;
                }
                else
                {
                    break;
                }
            }
        }
        pair_rank++;
    }
    // Copy pairs_copy[] to pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = pairs_copy[i];
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Check if adding this edge will create cycle
        if (!has_cycle(pairs[i].loser, pairs[i].winner))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Check if there's a continuous path from i to j
bool has_cycle(int start, int end)
{
    // Variable help: true if start --> end is possible
    bool help = false;
    if (start != end)
    {
        // possible[i]: if start --> i is possible
        // flag[i]: if start --> i --> end is possible
        bool possible[candidate_count];
        bool flag[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            possible[j] = false;
            flag[j] = false;
        }
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[start][k])
                possible[k] = true;
        }
        for (int i = 0; i < candidate_count; i++)
        {
            if (possible[i])
                flag[i] = has_cycle(i, end);
        }
        // Variable help: true if start --> end is possible
        for (int i = 0; i < candidate_count; i++)
        {
            if (flag[i] == true)
                help = true;
        }
    }
    // Else: start == end
    else
    {
        return true;
    }
    return help;
}

// Print the winner of the election
void print_winner(void)
{
    // Initialize winner[] to all 0s
    int winner[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        winner[i] = 0;
    }
    // If there's an arrow pointing at i, winner[i] = 1
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
                winner[i] = 1;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // WINNERS: those who aren't pointed at (winner[i] == 0)
        if (winner[i] == 0)
            printf("%s\n", candidates[i]);
    }
    return;
}
