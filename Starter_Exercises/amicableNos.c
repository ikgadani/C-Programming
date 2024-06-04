#include <stdio.h>

/* Function to calculate the sum of proper divisors of a number */
int DivisorsSum(int num) {
    int sum = 0;
    
    /*Iterate through numbers from 1 to half of the input number */
    int i;
    for (i = 1; i <= num / 2; i++) {
        /*If 'i' is a divisor of 'num', add it to the sum of divisors*/
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number1;
    int number2;
    int sum1;
    int sum2;

    /*Prompt the user to input two numbers*/
    printf("Enter the first number: ");
    scanf("%d", &number1);

    printf("Enter the second number: ");
    scanf("%d", &number2);

    /*Calculate the sum of divisors for both input numbers*/
    
    sum1 = DivisorsSum(number1);
    sum2 = DivisorsSum(number2);

    /*Check if the input numbers are amicable*/
    if (sum1 == number2 && sum2 == number1) {
        printf("Entered numbers are amicable numbers.\n");
    } else {
        printf("Entered numbers are not amicable numbers.\n");
    }

    return 0;
}

