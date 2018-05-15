//
// Created by phyllipe on 23/04/18.
//

#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#define ALPHABET_SIZE 26
#define FALSE 0
#define TRUE 1

#include <string.h>

typedef struct trie trie_t;

struct trie {
    char value;
    trie_t* items[ALPHABET_SIZE];
    trie_t* previous;
    int isLeaf;
};

int alpha_key(char ch) {

    int key = ch;
    return key % 97;

    /* Receives a char (a-z) and return the hash value of that letter on the 26 size ring.
     * The reason why we are returning the value as key mod 97, it is because we are dealing
     * with ASCII values, the 'a' ASCII character value it is 97, in other words, we have
     * a alphabetical size ring, 26. */
}

trie_t* create_empty_trie(char def) {

    trie_t* new_trie = malloc(sizeof(trie_t));
    new_trie->value = def;
    new_trie->previous = NULL;

    int i;

    for (i = 0; i < ALPHABET_SIZE; ++i)
        new_trie->items[i] = NULL;

    new_trie->isLeaf = FALSE;

    /* Receives a char variable and create a empty trie data structure, first we malloc memory
     * space for it, them we set the trie value to the received character, set all the 26
     * trie pointers to NULL and initialize the boolean isLeaf as false. */
}

void insert_in_trie(trie_t* root, char *key) {

    int level;
    int index;

    trie_t* current = root;

    for (level = 0; key[level] != '\0'; ++level)
    {
        index = alpha_key(key[level]);

        if (!current->items[index])
            current->items[index] = create_empty_trie(key[level]);

        current->items[index]->previous = current;
        current = current->items[index];
    }

    // mark last node as leaf
    current->isLeaf = TRUE;
    printf("Adicionado: %s\n", key);

    /* Receives  a trie and a pointer to a char which will be the word that we want to insert,
     * after that we run for each string character always verifying if it will be necessary or
     * not to insert that character. */
}

int find_letter_index(trie_t* trie) {

    int i;

    for (i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (trie->items[i] != NULL)
        {
            return i;
        }
    }

    return -1;

    /* Receives a trie node and search in alphabetical order (0-25) for the nearest letter, if
     * everything ran alright return the letter index, otherwise return -1 as error. */
}

int search(trie_t* root, char* str) {

    int level, index;
    trie_t* current = root;
    char wordSuggestion[20];

    /* 1.0 - Find the last substring letter trie node: */

    for (level = 0; str[level] != '\0'; level++)
    {
        index = alpha_key(str[level]);

        if (!current->items[index])
        {
            printf("Nenhuma sugestao encontrada.\n");
            return -1;
        }

        current = current->items[index];
    }

    int i = 0;

    /* 2.0 - Check the nearest word: */

    while (!current->isLeaf) {

        int letter_index = find_letter_index(current);

        if (letter_index == -1)
        {
            printf("Nenhuma sugestao encontrada.\n");
            return -1;
        }

        current = current->items[letter_index];
        wordSuggestion[i++] = current->value;
    }

    wordSuggestion[i] = '\0';

    printf("%s%s\n", str, wordSuggestion);
    return 1;

    /* Receives a trie and a substring that we want to search for recommendations, and them
     * (Check the function body for the indexes) at the 1.0 part, we will run through the trie
     * and set the "current" pointer to the last letter node. Forward to the 2.0 part, we will
     * always run to the nearest available letter until we find a leaf or not, if we did not find
     * any available letter, the function will print the predefined message and will return -1 as
     * an error. */
}

int hasChild(trie_t* letter) {
    int i;

    for (i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (letter->items[i] != NULL)
        {
            return TRUE;
        }
    }

    return FALSE;

    /* Run through the 26 sized array and verify if at least one of it, it is not null. If all of them
     * are null, return true value, if not return false value. */
}

int remove_from_trie(trie_t* root, char* word) {

    int level;
    int index;
    trie_t* current = root;

    for (level = 0; word[level] != '\0'; ++level)
    {

        index = alpha_key(word[level]);

        if (!current->items[index])
        {
            printf("Palavra nao existe na trie.\n");
            return -1;
        }

        current = current->items[index];
    }

    if (!current->isLeaf)
    {
        printf("Palavra nao existe na trie.\n");
        return -1;
    }

    current->isLeaf = FALSE;

    while (current->previous != NULL)
    {
        if (!hasChild(current) && !current->isLeaf)
        {
            int index = alpha_key(current->value);
            current = current->previous;

            if (current->items[index])
            {
                free(current->items[index]);
                current->items[index] = NULL;
            }
        }
        else
        {
            current = current->previous;
        }
    }

    return 1;

    /* Receives a trie node and a word to be removed. The first step it is to check if that word is
     * contained on the trie, if the word exists, we need to set the isLeaf variable to false, and
     * them do the backtracking process to remove all the letters that can be removed from the trie. */
}

#endif //PROJECT_TREE_H
