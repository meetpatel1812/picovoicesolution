#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* word;
    int frequency;
} WordFrequency;

int compareWordFrequency(const void* a, const void* b) {
    return ((WordFrequency*)b)->frequency - ((WordFrequency*)a)->frequency;
}

char** find_frequent_words(const char* path, int n) {
    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", path);
        exit(EXIT_FAILURE);
    }

    WordFrequency* wordFreqArray = NULL;
    size_t arraySize = 0;

    char word[100];
    while (fscanf(file, "%99s", word) == 1) {
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        int found = 0;
        for (size_t i = 0; i < arraySize; i++) {
            if (strcmp(word, wordFreqArray[i].word) == 0) {
                wordFreqArray[i].frequency++;
                found = 1;
                break;
            }
        }

        if (!found) {
            arraySize++;
            wordFreqArray = realloc(wordFreqArray, arraySize * sizeof(WordFrequency));
            wordFreqArray[arraySize - 1].word = strdup(word);
            wordFreqArray[arraySize - 1].frequency = 1;
        }
    }

    qsort(wordFreqArray, arraySize, sizeof(WordFrequency), compareWordFrequency);

    char** result = malloc((n + 1) * sizeof(char*));
    for (int i = 0; i < n && i < arraySize; i++) {
        result[i] = strdup(wordFreqArray[i].word);
    }
    result[n] = NULL;

    for (size_t i = 0; i < arraySize; i++) {
        free(wordFreqArray[i].word);
    }
    free(wordFreqArray);

    fclose(file);

    return result;
}

int main() {
    const char* path = "shakespeare.txt";
    int n = 10;

    char** frequentWords = find_frequent_words(path, n);

    printf("Top %d most frequent words:\n", n);
    for (int i = 0; frequentWords[i] != NULL; i++) {
        printf("%d. %s\n", i + 1, frequentWords[i]);
        free(frequentWords[i]);
    }
    free(frequentWords);

    return 0;
}
