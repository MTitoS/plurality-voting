#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define candidadateMAX 9
#define voterMAX 15

int voting (char *candidates[], int candidatesCount, int votersCount);

int main (int argc, char argv[]) {
    int candidatesCount = argc - 1;
    int votersCount = 0;

    if (argc <= 2) {
        printf("Need to be passed at least two candidates.");
        return 2;
    }

    if (candidatesCount > candidadateMAX) {
        printf("Maximum number of candidates is %i\n.", candidadateMAX);
        return 2;
    }

    printf("Number of voters: ");
    while (scanf("%d",&votersCount) != 1 || votersCount <= 1 || votersCount > voterMAX) {
        printf("Invalid input. Please enter a valid number of voters: ");
        while (getchar () != '\n');
    }

    // do {
    //     printf("Number of voters: ");
    //     scanf("%d", &votersCount); //Entender melhor depois.
    //     printf("Voters count: %d", votersCount);
    //     while (getchar () != '\n');
    // } while (!isdigit(votersCount) || votersCount <= 1 || votersCount > voterMAX);

    voting(argv, candidatesCount, votersCount);

    return 0;
}

int voting (char *candidates[], int candidatesCount, int votersCount) {
    // ----------------------------------------------------------------
    //TO:DO Arrumar ponteiros e forma como voting está recebendo a argv
    // ----------------------------------------------------------------
    char *votes[99];

    //Uma outra ideia seria implementar hash, e aí eu poderia consultar diretamente o nome do candidato na tabela, facilitando a lógica e aumentando performance.
    for (int i = 0; i < votersCount; i++) {
        printf("Eleitor %d. Voto: ", i + 1);
        scanf("%s", &votes[i]);

        for (int j = 0, h = 1; j < candidatesCount; j++, h++) {
            int compare = strcmp(votes[i], candidates[h]);

            if (compare == 0) {
                printf("Valid vote.\n");
                break;
            }

            if (j = candidatesCount) {
                printf("Invalid vote.");
                return 1;
            }
        }
    }
}