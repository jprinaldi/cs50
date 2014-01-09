#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool dictionaryAttack(string ciphertext);
bool bruteForceAttack(string ciphertext);
bool next(char* word, int n);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./crack ciphertext\n");
        return 1;
    }

    if (dictionaryAttack(argv[1]))
        printf("Password cracked successfully via dictionary attack.\n");
    else if (bruteForceAttack(argv[1]))
        printf("Password cracked successfully via brute force attack.\n");
    else
        printf("Unable to crack password.\n");
}

bool dictionaryAttack(string ciphertext)
{
    printf("Dictionary attack initiated.\n");

    char word[128];
    char salt[2];
    strncpy(salt, ciphertext, 2);
    FILE *wordlist = fopen("/usr/share/dict/words", "r");

    while (fgets(word, 128, wordlist)) {    
        // fgets reads new line characters, and we don't want those
        word[strlen(word) - 1] = '\0';

        if (!strcmp(crypt(word, salt), ciphertext)) {
            printf("Password found: %s\n", word);
            return true;
        }
    }

    fclose(wordlist);

    printf("Dictionary attack failed.\n");

    return false;
}

bool bruteForceAttack(string ciphertext)
{
    printf("Brute force attack initiated.\n");

    char salt[2];
    strncpy(salt, ciphertext, 2);

    for (int length = 1; length <= 8; length++) {
        printf("Trying passwords of length %d...\n", length);

        char* word = calloc(length + 1, sizeof(char));

        do {
            if (!strcmp(crypt(word, salt), ciphertext)) {
                printf("Password found: %s\n", word);
                return true;
            }
        } while (next(word, length));
    }

    printf("Brute force attack failed.\n");

    return false;
}

bool next(char* word, int length)
{
    for (int i = length - 1; i >= 0; i--)
        if (word[i] < 127) {
            word[i]++;
            for (int j = i+1; j < length; j++)
                word[j] = 0;
            return true;
        }

    return false;
}
