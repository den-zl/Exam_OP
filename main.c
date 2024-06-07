#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tests/test_exam_task.h"


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


    test_exam_task ();

    return 0;
}
