#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int coin_count = 0;
    float dollars;

    do {
        printf("Show me the money: ");
        dollars = GetFloat();
    } while (dollars < 0);

    int cents = (int) round(dollars*100);

    // Count quarters
    coin_count += cents/25;
    cents %= 25;

    // Count dimes
    coin_count += cents/10;
    cents %= 10;

    // Count nickels
    coin_count += cents/5;
    cents %= 5;

    // Count cents
    coin_count += cents;

    printf("%d\n", coin_count);
}
