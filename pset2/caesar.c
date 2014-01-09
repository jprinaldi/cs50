#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(int key, string plaintext);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string plaintext = GetString();

    encrypt(key, plaintext);
}

void encrypt(int key, string plaintext)
{
    int shift;
    for (int i = 0, n = strlen(plaintext); i < n; i++) {
        if (isalpha(plaintext[i])) {
            shift = 'A' + (isupper(plaintext[i]) == 0)*('a' - 'A');
            printf("%c", (plaintext[i] - shift + key)%26 + shift);
        } else
            printf("%c", plaintext[i]);
    }
    printf("\n");
}
