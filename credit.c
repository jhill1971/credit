// credit.c
// Programmer: James Hill. Houston, Texas. December, 2024

#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 16

int main(void)
{
    char input[MAX_DIGITS + 1]; // +1 for the null terminator
    int numArray[MAX_DIGITS];
    int ccArray[MAX_DIGITS];

    // Get user input
    printf("Number: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character if present

    // Check if the input length is within the valid range
    size_t len = strlen(input);
    if (len < 13 || len > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // Copy characters to the array without changing order
    for (int i = 0; i < len; i++)
    {
        ccArray[i] = input[i] - '0';
    }

    // Convert characters to numeric values and store in reverse order
    for (int i = len - 1; i >= 0; i--)
    {
        numArray[len - 1 - i] = input[i] - '0';
    }

    // Calculate Checksum
    int sum = 0;
    int secondSum = 0;

    for (int j = 0; j < len; j++)
    {
        // Starting from the second-to last number, multiply every other number by 2
        // Add the digits of the products (NOT the products themselves) to get a sum
        if (j % 2 == 0)
        {
            secondSum += numArray[j];
        }
        else
        {
            int product = numArray[j] * 2;
            sum += (product < 10) ? product : product - 9;
        }
    }

    int total = sum + secondSum;

    // If the last digit of the result is 0, then the user input is valid and the program proceeds to identifying the card type.
    // Otherwise, display "INVALID" and exit,
    if ((total % 10) != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Identify the card type
    else if (len == 15 && (ccArray[0] == 3 && (ccArray[1] == 4 || ccArray[1] == 7)))
    {
        printf("AMEX\n");
    }
    else if (len == 16 && (ccArray[0] == 5 && (ccArray[1] >= 1 && ccArray[1] <= 5)))
    {
        printf("MASTERCARD\n");
    }

    else if ((len == 13 || len == 16) && ccArray[0] == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}
