#include <stdio.h>
#include <cs50.h>

void print(long long number);
bool check_validity(long long number);
bool check_lohn(long long number);

int main(void)
{
    // Get Number
    long long number;
    do
    {
        number = get_long_long("Credit Card Number: ");
    }
    while (number < 0);

    // Check Validation
    if (check_validity(number))
    {
        print(number);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_validity(long long number)
{
    // Get Length
    long long temp_number = number;
    int length = 0;
    for (length = 0; temp_number != 0; temp_number /= 10, length++);

    // Validation with Length and Luhn's Algo
    if ((length == 13 || length == 15 || length == 16) && check_lohn(number))
    {
        return true;
    }
    return false;
}

bool check_lohn(long long number)
{
    int sum = 0;
    for (int i = 0; number != 0; i++, number /= 10)
    {
        if (i % 2 == 0)
        {
            sum += number % 10;
        }
        else {
            sum += 2 * (number % 10) / 10 + 2 * (number % 10) % 10;
        }
    }
    return (sum % 10) == 0;
}

void print(long long number)
{
    if ((number >= 34e13 && number < 35e13) || (number >= 37e13 && number < 38e13))
    {
        printf("AMEX\n");
    }
    else if (number >= 51e14 && number < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((number >= 4e12 && number < 5e12) || (number >= 4e15 && number < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}