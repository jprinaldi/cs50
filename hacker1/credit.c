#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

string identify(long long number);
bool isValid(long long number);
bool isAmex(long long number);
bool isMastercard(long long number);
bool isVisa(long long number);
int digitSum(long long number);
int getFirstNDigits(int n, long long number);

int main(void)
{
    printf("Number: ");
    long long number = GetLongLong();
    printf("%s\n", identify(number));
}

string identify(long long number)
{
    if (!isValid(number))
        return "INVALID";
    else if (isAmex(number))
        return "AMEX";
    else if (isMastercard(number))
        return "MASTERCARD";
    else if (isVisa(number))
        return "VISA";
    else
        return "UNKNOWN";
}

bool isValid(long long number)
{
    int sum = 0;
    int x = 1;
    while (number != 0) {
        sum += digitSum(number%10*x);
        x = 3 - x;
        number /= 10;
    }
    return (sum%10 == 0);
}

bool isAmex(long long number)
{
    int x = getFirstNDigits(2, number);
    return (x == 34 || x == 37);
}

bool isMastercard(long long number)
{
    int x = getFirstNDigits(2, number);
    return (x >= 51 && x <= 55);
}

bool isVisa(long long number)
{
    int x = getFirstNDigits(1, number);
    return (x == 4);
}

int digitSum(long long number)
{
    int sum = 0;
    while (number != 0) {
        sum += number%10;
        number /= 10;
    }
    return sum;
}

int getFirstNDigits(int n, long long number)
{
    while (number >= pow(10, n))
        number /= 10;
    return number;
}
