#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100
#define MAX_TEXT_LENGTH 10000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;


void cleanWord(char* word) {
    char* src = word;
    char* dst = word;
    while (*src) {
        if (isalpha((unsigned char)*src)) {
            *dst++ = tolower((unsigned char)*src);
        }
        src++;
    }
    *dst = '\0';
}

int countWords(char* text, WordCount* word_counts, int max_words) {
    char* token = strtok(text, " \n\t");
    int word_index = 0;
    while (token != NULL) {
        cleanWord(token);
        int found = 0;
        for (int i = 0; i < word_index; i++) {
            if (strcmp(word_counts[i].word, token) == 0) {
                word_counts[i].count++;
                found = 1;
                break;
            }
        }
        if (!found && word_index < max_words) {
            strcpy(word_counts[word_index].word, token);
            word_counts[word_index].count = 1;
            word_index++;
        }
        token = strtok(NULL, " \n\t");
    }
    return word_index;
}

void editText(char* text, WordCount* word_counts, int word_count, int remove_count) {
    char* token = strtok(text, " \n\t");
    while (token != NULL) {
        char clean_token[MAX_WORD_LENGTH];
        strcpy(clean_token, token);
        cleanWord(clean_token);
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(word_counts[i].word, clean_token) == 0 && word_counts[i].count == remove_count) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("%s ", token);
        }
        token = strtok(NULL, " \n\t");
    }
    printf("\n");
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <remove_count>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    int remove_count = atoi(argv[2]);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char text[MAX_TEXT_LENGTH];
    if (fread(text, sizeof(char), MAX_TEXT_LENGTH, file) == 0) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }
    fclose(file);

    WordCount word_counts[MAX_WORDS];
    char text_copy[MAX_TEXT_LENGTH];
    strcpy(text_copy, text);
    int word_count = countWords(text_copy, word_counts, MAX_WORDS);

    editText(text, word_counts, word_count, remove_count);

    return 0;
}
