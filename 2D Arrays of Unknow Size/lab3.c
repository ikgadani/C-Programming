#include <stdio.h>
#include <stdlib.h>

/*Function declarations*/
void printRectangle(char **rectangle, int width, int height);
void fillRow(char **rectangle, int row, char fillChar, int width);
void fillColumn(char **rectangle, int col, char fillChar, int height);
void setChar(char **rectangle, int row, int col, char setChar);
int replaceChar(char **rectangle, int width, int height, char oldChar, char newChar);

int main() {
    
    unsigned int width;
    unsigned int height;
    unsigned int i;
    unsigned int j;
    int choice;
    char **rectangle;
    int max_attempts = 3;
    int attempt = 0;

    printf("Enter rectangle width: ");
    while (attempt < max_attempts) {
        if (scanf("%u", &width) != 1) {
            /*Check for EOF*/
            if (feof(stdin)) {
                fprintf(stderr, "EOF detected. Program terminated.\n");
                return 3; /* Exit with status 3 */
            }

            /*Handle invalid input*/
            printf("(!) Not a number, or out of range (1..4294967295), try again.\n");
            while (getchar() != '\n'); /*Clear input buffer*/
            attempt++;

        } else {
            break;
        }
    }

    /*Check if the maximum attempts were reached*/
    if (attempt == max_attempts) {
        fprintf(stderr, "Maximum attempts reached. Program terminated.\n");
        return 3;
    }

    printf("Enter rectangle height: ");
    attempt = 0;
    while (attempt < max_attempts) {
        if (scanf("%u", &height) != 1) {
            /*Check for EOF*/
            if (feof(stdin)) {
                fprintf(stderr, "EOF detected. Program terminated.\n");
                return 3; /* Exit with status 3 */
            }

            /*Handle invalid input*/
            printf("(!) Not a number, or out of range (1..4294967295), try again.\n");
            while (getchar() != '\n'); /*Clear input buffer*/
            attempt++;
        } else {
            break;
        }
    }

    /*Check if the maximum attempts were reached*/

    if (attempt == max_attempts) {
        fprintf(stderr, "Maximum attempts reached. Program terminated.\n");
        return 3;
    }
    
    rectangle= (char **)malloc(height * sizeof(char *));
    if (rectangle == NULL) {
        fprintf(stderr, "(!) Memory allocation error.\n");
        return 4;
    }
    for (i = 0; i < height; i++) {
        rectangle[i] = (char *)malloc(width * sizeof(char));
        if (rectangle[i] == NULL) {
            fprintf(stderr, "(!) Memory allocation error.\n");
            /*Free memory allocated until this point*/
            for (j = 0; j < i; j++) {
                free(rectangle[j]);
            }
            free(rectangle);
            return 4;
        }
        /*Initialize rectangle with dots*/
        for (j = 0; j < width; j++) {
            rectangle[i][j] = '.';
        }
    }

    do {
        /*Display menu*/
        printf("1 - Fill Row     | 2 - Fill Column  | 3 - Set Char     \n"
               "4 - Replace Char | 5 - Exit          \n-> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                /*Fill Row*/
                {
                    char fillChar;
                    int row;
                    printf("Enter char: ");
                    scanf(" %c", &fillChar);  /*Use space before %c to consume newline character*/
                    printf("Enter row: ");
                    scanf("%d", &row);
                    if (row >= 1 && row <= height) {
                        fillRow(rectangle, row - 1, fillChar, width);
                        printRectangle(rectangle, width, height);
                    } else {
                        printf("(!) Invalid row number.\n");
                    }
                }
                break;

            case 2:
                /*Fill Column*/
                {
                    char fillChar;
                    int col;
                    printf("Enter char: ");
                    scanf(" %c", &fillChar);  /*Use space before %c to consume newline character*/
                    printf("Enter column: ");
                    scanf("%d", &col);
                    if (col >= 1 && col <= width) {
                        fillColumn(rectangle, col - 1, fillChar, height);
                        printRectangle(rectangle, width, height);
                    } else {
                        printf("(!) Invalid column number.\n");
                    }
                }
                break;

            case 3:
        
                {
                    char charToSet;
                    int row, col;
                    printf("Enter char: ");
                    scanf(" %c", &charToSet);  /*Use space before %c to consume newline character*/
                    printf("Enter column: ");
                    scanf("%d", &col);
                    printf("Enter row: ");
                    scanf("%d", &row);
                    if (row >= 1 && row <= height && col >= 1 && col <= width) {
                        setChar(rectangle, row - 1, col - 1, charToSet);
                        printRectangle(rectangle, width, height);
                    } else {
                        printf("(!) Invalid row or column number.\n");
                    }
                }
                break;
                
            case 4:
                /*Replace Char*/
                {
                    char oldChar, newChar;
                    int replacements;

                    printf("Enter char to replace: ");
                    scanf(" %c", &oldChar);  /*Use space before %c to consume newline character*/
                    printf("Enter new char: ");
                    scanf(" %c", &newChar);  /*Use space before %c to consume newline character*/
                    replacements = replaceChar(rectangle, width, height, oldChar, newChar);
                    if (replacements > 0) {
                        printf("Replaced %d times\n", replacements);
                        printRectangle(rectangle, width, height);
                    } else {
                        printf("The character was not found\n");
                    }
                }
                break;

            case 5:
                /*Exit*/
                break;

            default:
                printf("(!) Invalid choice. Try again.\n");
        }

    } while (choice != 5);

    /*Free allocated memory*/
    for (i = 0; i < height; i++) {
        free(rectangle[i]);
    }
    free(rectangle);

    return 0;
}

/*Function to print the rectangle*/
void printRectangle(char **rectangle, int width, int height) {
    int i;
    int j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%c", rectangle[i][j]);
        }
        printf("\n");
    }
}

/*Function to fill a row with a character*/
void fillRow(char **rectangle, int row, char fillChar, int width) {
    int j;
    for (j = 0; j < width; j++) {
        rectangle[row][j] = fillChar;
    }
}

/*Function to fill a column with a character*/
void fillColumn(char **rectangle, int col, char fillChar, int height) {
    int i;
    for (i = 0; i < height; i++) {
        rectangle[i][col] = fillChar;
    }
}

/*Function to set a character in the rectangle*/
void setChar(char **rectangle, int row, int col, char setChar) {
    rectangle[row][col] = setChar;
}

/*Function to replace a character in the rectangle*/
int replaceChar(char **rectangle, int width, int height, char oldChar, char newChar) {
    int replacements = 0;
    int i;
    int j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (rectangle[i][j] == oldChar) {
                rectangle[i][j] = newChar;
                replacements++;
            }
        }
    }
    return replacements;
}
