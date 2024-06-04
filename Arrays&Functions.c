#include <stdio.h>


int getValidLength() {
    int length;

    while (1) {
        printf("Enter the length (up to 64): ");
        if (scanf("%d", &length) != 1 || length < 1 || length > 64) {
            printf("(!) Not a number, or out of range (1..64), try again.\n");

            /*Clear the input buffer*/
            while (getchar() != '\n');
        } else {
            /*Valid input, break out of the loop*/
            break;
        }
    }

    return length;
}

/*Function to reverse the elements of an array*/
void reverse_array(int arr[], int length) {
    int start = 0;
    int end = length - 1;
    int temp;
    int i;
    

    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }

    printf("{ ");
    for (i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) {
            printf(" ");
        }
    }
    printf(" }\n");
}

/*Function to find the index of an element in the array*/
int find_element(int arr[], int length) {
    int element;
    int i;

    while (1) {
        printf("Enter the element to find: ");
        if (scanf("%d", &element) != 1) {
            printf("Invalid input for element. Please enter a valid number.\n");
            /*Clear the input buffer*/
            while (getchar() != '\n');
        } else {
            /*Valid input, break out of the loop*/
            break;
        }
    }

    
    for (i = 0; i < length; i++) {
        if (arr[i] == element) {
            printf("Element found at index: %d\n", i);
            return 1; /* Element found, return success */
        }
    }

    printf("Element not found\n");
    return 0; /* Element not found */
}

/*Function to replace all occurrences of a value in the array*/
int replace_element(int arr[], int length) {
    int oldValue;
    int newValue;
    int replacements;
    int i;

    replacements=0;

    while (1) {
        printf("Enter values to search and replace (space separated): ");
        if (scanf("%d %d", &oldValue, &newValue) != 2) {
            printf("Invalid input for values. Please enter valid numbers.\n");
            /*Clear the input buffer*/
            while (getchar() != '\n');
        } else {
            /*Valid input, break out of the loop*/
            break;
        }
    }

    
    for (i = 0; i < length; i++) {
        if (arr[i] == oldValue) {
            arr[i] = newValue;
            replacements++;
        }
    }

    if (replacements > 0) {
        printf("Replaced %d time(s)\n{ ", replacements);
        for (i = 0; i < length; i++) {
            printf("%d", arr[i]);
            if (i < length - 1) {
                printf(" ");
            }
        }
        printf(" }\n");
    } else {
        printf("%d is not in the array\n", oldValue);
    }

    return replacements;
}

int main() {
    int length;
    int arr[64];
    int i;
    int choice;

    length = getValidLength();

    
    printf("Enter %d numbers (-1000 to 1000, space separated):\n", length);

    for (i = 0; i < length; i++) {
    /*Read integers from the user and store them in the array*/
        while (1) {
            printf("Enter element %d: ", i + 1);
            if (scanf("%d", &arr[i]) != 1 || arr[i] < -1000 || arr[i] > 1000) {
                printf("(!) Not a number, or out of range (-1000..1000), try again. \n");
                /*Clear the input buffer*/
                while (getchar() != '\n');
            } else {
                /*Valid input, break out of the loop*/
                break;
            }
        }
    }

    do {
        printf("Choose an operation:\n");
        printf("0 - Exit             | 1 - Print array      | 2 - Reverse array\n");
        printf("3 - Search array     | 4 - Replace in array\n");
        printf("-> ");
        scanf("%d", &choice);

        switch (choice) {
            int i;
            case 1:
                printf("{ ");
                for (i = 0; i < length; i++) {
                    printf("%d", arr[i]);
                    if (i < length - 1) {
                        printf(" ");
                    }
                }
                printf(" }\n");
                break;
            case 2:
                reverse_array(arr, length);                
                break;
            case 3: {
                find_element(arr, length);
                break;
            }
            case 4: {
                replace_element(arr, length);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice\n");
                break;
        }

    } while (choice != 0);

    return 0;
}
