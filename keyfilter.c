#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void processArguments(int argc, char *argv[], char search[101], int *lengthOfSearch) {
    if (argc != 2 && argc != 1) {
        fprintf(stderr,
                "you put %d arguments\n"
                "try to use command like\n"
                "./keyfilter b <adresy.txt\n", argc);
        exit(1);
        return;
    } else if (argc == 2) {
        int i;
        for (i = 0; argv[1][i] != '\0'; i++) {
            search[i] = toupper(argv[1][i]);
        }
        search[i] = '\0';
        *lengthOfSearch = i;
    }
}

void loadAddress(char address[42][101], int *index) {
    while (scanf("%100[^\n]\n", address[(*index)]) != EOF) {
        for (int i = 0; address[(*index)][i] != '\0'; i++) {
            address[(*index)][i] = toupper(address[(*index)][i]);
        }
        (*index)++;
    }
}

void addUniqueAddress(char letterOfAddress, int *foundedInAscii, char *result, int *lengthOfResult, int *lengthOfValidAddresses,
                      int *lastIndexOfValidAdress, int i) {
    if (foundedInAscii[(int) letterOfAddress] != 1) {
        foundedInAscii[(int) letterOfAddress] = 1;
        result[(*lengthOfResult)] = letterOfAddress;
        (*lengthOfResult)++;
        (*lastIndexOfValidAdress) = i;
    }
    (*lengthOfValidAddresses)++;
}

int main(int argc, char *argv[]) {

    char address[42][101];
    char search[101];
    int lengthOfSearch = 0;

    processArguments(argc, argv, search, &lengthOfSearch);

    int index = 0;
    loadAddress(address, &index);


    char result[42];
    //length of ascii table
    int foundedInAscii[128] = {0};
    int lengthOfValidAddresses = 0;
    int lastIndexOfValidAdderss = -1;
    int lengthOfResult = 0;

    if (argc == 2) {
        if (argv[1]) {
            for (int i = 0; i < index; ++i) {
                int valid = 1;
                char letterOfAddress = address[i][lengthOfSearch];
                for (int l = 0; l < lengthOfSearch; ++l) {
                    if (search[l] != toupper(address[i][l])) {
                        valid = 0;
                        break;
                    }
                }
                if (valid == 1) {
                    if (letterOfAddress == 0) {
                        printf("Found: %s\n", address[i]);
                        return 0;
                    }
                    addUniqueAddress(letterOfAddress, foundedInAscii, result, &lengthOfResult, &lengthOfValidAddresses, &lastIndexOfValidAdderss, i);
                }

            }
        }
    } else {
        for (int i = 0; i < index; ++i) {
            char firstLetterOfAddress = address[i][0];
            addUniqueAddress(firstLetterOfAddress, foundedInAscii, result, &lengthOfResult, &lengthOfValidAddresses, &lastIndexOfValidAdderss, i);
        }
    }

    if (lengthOfValidAddresses == 0) {
        printf("Not found");
    } else if (lengthOfValidAddresses == 1) {
        printf("Found: %s", address[lastIndexOfValidAdderss]);
    } else {
        printf("Enable: %s", result);
    }

    return 0;
}
