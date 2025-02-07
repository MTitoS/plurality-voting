#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 15
#define MAX_NAME_LENGTH 30

char **voting(char *candidates[], int candidatesCount, int votersCount);
int voteCounting(char **votes, int votersCount, char *candidates[], int candidatesCount);

int main(int argc, char *argv[]) {
    int candidatesCount = argc - 1; //If just argc, it will consider also the calling of the function
    int votersCount = 0;

    if (argc <= 2) {
        printf("Need to be passed at least two candidates.");
        return 2;
    }

    if (candidatesCount > MAX_CANDIDATES) {
        printf("Maximum number of candidates is %i\n.", MAX_CANDIDATES);
        return 2;
    }

    //If invalid input, keep scanning.
    printf("Number of voters: ");
    while (scanf("%d",&votersCount) != 1 || votersCount <= 1 || votersCount > MAX_VOTERS) {
        printf("Invalid input.\nPlease enter a valid number of voters: ");
        while (getchar () != '\n');
    }
    
    char *candidates[99];

    //Pass down the candidates to an array insted of using argv.
    for (int i = 0; i < candidatesCount; i++) {
        candidates[i] = argv[i + 1];
    }

    //Receives the returning array from voting.
    char **votes = voting(candidates, candidatesCount, votersCount);

    if (votes == NULL) {
        printf("No valid votes.");
        return 1;
    }

    //Calls the voteCouting function to read votes and print the winner
    voteCounting(votes, votersCount, candidates, candidatesCount);

    for (int i = 0; i < votersCount; i++) {
        free(votes[i]);
    }
    free(votes);

    return 0;
}

char **voting(char *candidates[], int candidatesCount, int votersCount) {
    char **votes = malloc(votersCount * sizeof(char *)); //Allocate the memory to the quantity of voters, each of size of a char pointer.

    for (int i = 0; i < votersCount; i++) {
        //Alocate memory to the voting indexes.
        votes[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
        if (votes[i] == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
    }

    //Read votes
    for (int i = 0; i < votersCount; i++) {
        printf("Eleitor %d. Voto: ", i + 1);
        scanf("%s", votes[i]);

        int validVote = 0;

        for (int j = 0; j < candidatesCount; j++) {
            if (strcmp(votes[i], candidates[j]) == 0) {
                printf("Valid vote.\n");
                validVote = 1;
                break;
            }
        }

        if (!validVote) {
            printf("Invalid vote. Stopping the program.\n");
            return NULL;
        }
    }

    return votes;
}

int voteCounting(char **votes, int votersCount, char *candidates[], int candidatesCount) {
    int frequency;
    char result[99][MAX_NAME_LENGTH];
    int resultCount = 0;

    for(int i = 0; i < candidatesCount; i++) {
        int count = 0;

        for(int j = 0; j < votersCount; j++) {
            //Count each vote based on the candidate that is receiving it.
            if (strcmp(votes[j], candidates[i]) == 0) {
                count++;
            }
        }

        //If it appears more than the actual frequency, then add the candidate to the result array and starts the resultCount.
        if(count > frequency) {
            frequency = count;
            resultCount = 0;
            strcpy(result[resultCount], candidates[i]);
            resultCount++;
        } else if(count == frequency) {
            int isDuplicate = 0;
            for (int k = 0; k < resultCount; k++) {
                if (strcmp(result[k], candidates[i]) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }

            //If it isn't a dpulicate, then the candidate will also go to the array of results.
            if(!isDuplicate) {
                strcpy(result[resultCount], candidates[i]);
                resultCount++;
            }
        }
    }

    if (resultCount > 1) {
        printf("The winner candidates are: ");
        for (int i = 0; i < resultCount; i++) {
            printf("%s ", result[i]);
        }
        printf("\nThey received %d votes.", frequency);

        return 0;
    }

    printf("The winner candidate is ");
    for (int i = 0; i < resultCount; i++) {
        printf("%s ", result[i]);
    }
    printf("\nHe received %d votes.", frequency);

    return 0;
}