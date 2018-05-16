//
// Created by phyllipe on 24/04/18.
//

#ifndef TRIE_DATA_STRUCTURE_READFILE_H
#define TRIE_DATA_STRUCTURE_READFILE_H

FILE* open_file() {

    FILE* file = fopen("../trainner.txt", "r");

    if (!file)
    {
        printf("Erro ao abrir o trainner.txt\n");
        exit(0);
    }

    return file;

    /* Simply open the train file and check for errors. */
}

int trie_train(trie_t* trie, FILE* file) {

    char *word = malloc(20);
    size_t n = 0;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        if (c != '\n')
        {
            word[n++] = (char)c;
        }
        else
        {
            word[n] = '\0';

            insert_in_trie(trie, word);
            n = 0;

            word[0] = '\0';
        }
    }

    free(word);
    return 1;


    /* Receives a trie and a FILE pointer to the train file, them read each file
     * byte saving it on a array, and when we find a \n character call the insert
     * in trie function, to insert the word into the trie. */
}

#endif //TRIE_DATA_STRUCTURE_READFILE_H
