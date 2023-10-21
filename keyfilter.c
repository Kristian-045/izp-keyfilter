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

void addUniqueAddress(char letterOfAddress, int *foundedInAscii, int *lengthOfValidAddresses,
                      int *lastIndexOfValidAdress, int i) {
    if (foundedInAscii[(int) letterOfAddress] != 1) {
        foundedInAscii[(int) letterOfAddress] = 1;
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



    //length of ascii table
    int foundedInAscii[128] = {0};
    int lengthOfValidAddresses = 0;
    int lastIndexOfValidAdderss = -1;

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
                    addUniqueAddress(letterOfAddress, foundedInAscii, &lengthOfValidAddresses, &lastIndexOfValidAdderss, i);
                }

            }
        }
    } else {
        for (int i = 0; i < index; ++i) {
            char firstLetterOfAddress = address[i][0];
            addUniqueAddress(firstLetterOfAddress, foundedInAscii, &lengthOfValidAddresses, &lastIndexOfValidAdderss, i);
        }
    }

    if (lengthOfValidAddresses == 0) {
        printf("Not found");
    } else if (lengthOfValidAddresses == 1) {
        printf("Found: %s", address[lastIndexOfValidAdderss]);
    } else {
        int resultIndex=0;
        char sorterResult[42];
        for (int i = 0; i < 128; i++) {
            if (foundedInAscii[i] == 1) {
                sorterResult[resultIndex++] = (char) i;
            }
        }
        sorterResult[resultIndex]='\0'

        printf("Enable: %s", sorterResult);
    }

    return 0;
}
