#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void encrypt(string keyword, string plaintext);

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2) {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    string keyword = argv[1];
    
    for (int i = 0, n = strlen(keyword); i < n; i++) {
        if (!isalpha(keyword[i])) {
            printf("Keyword cannot contain non-alphabetical characters.\n");
            return 1;
        }
    }
    
    string plaintext = GetString();
    
    encrypt(keyword, plaintext);
}

void encrypt(string keyword, string plaintext)
{
    int m = strlen(keyword);
    int j = 0;
    int shift;
    
    for (int i = 0, n = strlen(plaintext); i < n; i++) {
        if isalpha(plaintext[i]) {
            shift = 'A' + (isupper(plaintext[i]) == 0)*('a' - 'A');
            printf("%c", (plaintext[i] - shift + tolower(keyword[j++%m]) - 'a')%26 + shift);
        } else
            printf("%c", plaintext[i]);
    }
    printf("\n");
}
