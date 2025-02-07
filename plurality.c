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
    int candidatesCount = argc - 1;
    int votersCount = 0;

    if (argc <= 2) {
        printf("Need to be passed at least two candidates.");
        return 2;
    }

    if (candidatesCount > MAX_CANDIDATES) {
        printf("Maximum number of candidates is %i\n.", MAX_CANDIDATES);
        return 2;
    }

    printf("Number of voters: ");
    while (scanf("%d",&votersCount) != 1 || votersCount <= 1 || votersCount > MAX_VOTERS) {
        printf("Invalid input.\nPlease enter a valid number of voters: ");
        while (getchar () != '\n');
    }
    
    char *candidates[99];

    for (int i = 0; i < candidatesCount; i++) {
        candidates[i] = argv[i + 1];
    }

    char **votes = voting(candidates, candidatesCount, votersCount);

    if (votes == NULL) {
        return 1;
    }

    voteCounting(votes, votersCount, candidates, candidatesCount);

    for (int i = 0; i < votersCount; i++) {
        free(votes[i]);
    }
    free(votes);

    return 0;
}

char **voting(char *candidates[], int candidatesCount, int votersCount) {
    char **votes = malloc(votersCount * sizeof(char *)); //[MAX_VOTERS];

    for (int i = 0; i < votersCount; i++) {
        votes[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
        if (votes[i] == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
    }

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
    char result[30][MAX_NAME_LENGTH];
    int resultCount = 0;

    for(int i = 0; i < candidatesCount; i++) {
        int count = 0;

        for(int j = 0; j < votersCount; j++) {
            //printf("%s", votes[j]);

            if (strcmp(votes[j], candidates[i]) == 0) {
                count++;
            }
        }

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

            if(!isDuplicate) {
                strcpy(result[resultCount], candidates[i]);
                resultCount++;
            }
        }
    }

    if (resultCount > 1) {
        printf("Os candidatos com mais votos foram: ");
        for (int i = 0; i < resultCount; i++) {
            printf("%s ", result[i]);
        }
        printf("\nEles receberam %d votos.", frequency);

        return 0;
    }

    printf("O candidato que ganhou foi o ");
    for (int i = 0; i < resultCount; i++) {
        printf("%s ", result[i]);
    }
    printf("\nEle recebeu %d votos.", frequency);

    return 0;
}