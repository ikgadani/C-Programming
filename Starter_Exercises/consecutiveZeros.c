#include <stdio.h>

int main() {
    long int num;
    int consecutiveZeros; /*To keep track of consecutive zeros*/
    
    /*Prompt the user to enter a number*/
    printf("Enter a number: ");
    scanf("%ld", &num);

    consecutiveZeros=0;

    /*Loop through the digits of the number*/
    while (num > 0) {
        int currentDigit = num % 10; /*Extract the last digit of the number*/

        /*Check if the current digit is zero*/
        if (currentDigit == 0) {
            consecutiveZeros++; /*Increment the count of consecutive zeros*/
            /*If three consecutive zeros are found, print "YES" and exit the program*/
            if (consecutiveZeros == 3) {
                printf("YES\n");
                return 0;
            }
        } else {
            consecutiveZeros = 0; /*Reset the count if a non-zero digit is encountered*/
        }

        num /= 10; /*Remove the last digit from the number*/
    }

    /*If no three consecutive zeros are found, print "NO"*/
    printf("NO\n");

    return 0;
}
