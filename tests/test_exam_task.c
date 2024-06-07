#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "test_exam_task.h"

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


int tests_passed = 0;
int tests_failed = 0;

void assert_int_equal(int expected, int actual, const char* message) {
    if (expected == actual) {
        printf("PASS: %s\n", message);
        tests_passed++;
    } else {
        printf("FAIL: %s\n", message);
        tests_failed++;
    }
}

void assert_string_equal(const char* expected, const char* actual, const char* message) {
    if (strcmp(expected, actual) == 0) {
        printf("PASS: %s\n", message);
        tests_passed++;
    } else {
        printf("FAIL: %s\n", message);
        tests_failed++;
    }
}

void test_exam_task () {
    char test_word[] = "Hello123";
    cleanWord(test_word);
    assert_string_equal("hello", test_word, "cleanWord test");

    WordCount word_counts[MAX_WORDS];
    char test_text[] = "Hello world hello";
    int word_count = countWords(test_text, word_counts, MAX_WORDS);
    assert_int_equal(2, word_count, "countWords test");

    editText(test_text, word_counts, word_count, 1);
    assert_string_equal("world ", test_text, "editText test");

    printf("\nTests completed. Passed: %d, Failed: %d\n", tests_passed, tests_failed);
}

