//
// Created by phyllipe on 19/04/18.
//

#ifndef HUFFMAN_PROJECT_READFILE_H
#define HUFFMAN_PROJECT_READFILE_H

/**
 * Why this header?
 *
 *  - Better visualization of file manipulation functions
 */

FILE* open_file(char* name, char* mode) {

    FILE* file = fopen(name, mode);

    if (!file)
    {
        fprintf(stderr, "Unable to open file: %s\n", name);
        exit(0);
    }

    return file;

    /* Function open_file receive two strings as argument (name) and (mode)
     * then, use stdlib fopen function to open the file and verify is the file was opened
     * if not print an error message and return NULL, else return the file pointer
     * */
}

long int get_file_length(FILE* file) {

    fseek(file, 0, SEEK_END);
    long int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    return length;

    /* Function get_file_length receive a FILE pointer as argument
     * run to the end of the file, get the file length, return to
     * the file begin and return the file length
     * */
}

int get_file_name_length(char* fileName) {

    int i, length = 0;

    for (i = 0; fileName[i] != '\0'; ++i)
    {
        ++length;
    }

    return length;
}

#endif //HUFFMAN_PROJECT_READFILE_H
