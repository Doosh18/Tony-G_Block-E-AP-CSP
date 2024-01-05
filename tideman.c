#include <time.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;
candidate candidates[MAX_CANDIDATES];
int voter_count;
int candidate_count;
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", preferences[i][j]);
        }
        printf("\n");
    }

    return 1;
    while (true)
    {
        tabulate();
        bool won = print_winner();
        if (won)
        {
            break;
        }
        int min = find_min();
        bool tie = is_tie(min);
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
        eliminate(min);
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

bool vote(int voter, int rank, string name)
{
for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[rank][i] = i;
            return true;
            break;
        }
    }
    return false;
}
void tabulate(void)
{
            int candidate;

    for (int i = 0; i < voter_count; i++)
    {
        for (int g = 0; g < candidate_count; g++)
        {
            candidate = preferences[i][g];
            if (!candidates[candidate].eliminated)
            {
                candidates[candidate].votes = candidates[candidate].votes + 1;
                break;
            }
        }
    }
}
bool print_winner(void)
{
    int majority = voter_count / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}
int find_min(void)
{

    int min = candidates[0].votes;

    for (int t = 0; t < candidate_count; t++)
    {
        if (!candidates[t].eliminated && candidates[t].votes < min)
        {
            min = candidates[t].votes;
        }
    }
    return min;
}
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].eliminated == min)
        {
            if (candidates[i].votes == min)
            {
                return true;
            }
        }
    }
    return false;
}
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
