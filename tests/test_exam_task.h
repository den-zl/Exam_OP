//
// Created by Denis on 07.06.2024.
//

#ifndef EXAM_TASK_TEST_EXAM_TASK_H
#define EXAM_TASK_TEST_EXAM_TASK_H


#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100
#define MAX_TEXT_LENGTH 10000

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

void editText(char* text, WordCount* word_counts, int word_count, int remove_count);
int countWords(char* text, WordCount* word_counts, int max_words);
void cleanWord(char* word);

void test_exam_task ();

#endif //EXAM_TASK_TEST_EXAM_TASK_H
