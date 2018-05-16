//
// Created by thitc on 26/04/2018.
//

#ifndef HUFFMAN_PROJECT_COMPRESS_H
#define HUFFMAN_PROJECT_COMPRESS_H

/**
 * Intuitively in this header, the functions of each structure used in the
 * compression process are included, also including the implementation of
 * the main function: compress()
 */

#include "compress/readfile.h"
#include "compress/decimal_binary.h"
#include "compress/tree.h"
#include "compress/node.h"
#include "compress/stack.h"
#include "compress/hashtable.h"
#include "compress/priority_queue.h"
#include "compress/huff.h"
#include "compress/header.h"

void start_compression(BinaryTree_t* huff, char *fileName, HashTable_t *ht, long int fileLength, unsigned char first_byte,
                       unsigned char second_byte);

void compress(char *fileName) {

    FILE* file = open_file(fileName, "rb");

    HashTable_t *ht = build_ht(create_hash_table(), file);
    //Builds HashTable with every different byte, counting its respective frequency

    PriorityQueue_t *pq = build_pq(create_priority_queue(), ht);
    //Builds a Priority Queue with the HashTable bytes, sorting from the lowest to highest frequencies

    BinaryTree_t *huff = build_huffman(pq);
    //Builds the Huffman Tree from the Priority Queue

    printf("Building Paths ... ");

    Stack_t *stack = create_stack();

    build_paths(huff, ht, stack);

    free_stack(stack);

    printf("Done\n");

    unsigned char first_byte, second_byte;

    first_headers_byte(huff, bits_quantity(ht), &first_byte, &second_byte);
    // Gets the first 2 bytes of the header which contains the trash size and tree preorder size

    start_compression(huff, fileName, ht, get_file_name_length(fileName), first_byte, second_byte);
    // Creates the compressed.bmp file

    free_ht(ht);
    free_pq(pq);
    free_bt(huff);
}

char* change_extension(char *fileName, long int fileLength) {

    fileName = realloc(fileName, (size_t)(fileLength + 6));

    fileName[fileLength] = '.';
    fileName[fileLength + 1] = 'h';
    fileName[fileLength + 2] = 'u';
    fileName[fileLength + 3] = 'f';
    fileName[fileLength + 4] = 'f';
    fileName[fileLength + 5] = '\0';

    return fileName;

    // Changes de extension to .huff

}

void print_pre_order_tree_on_file(FILE* file, BinaryTree_t* huff) {
    if (!is_empty(huff))
    {
        fprintf(file, "%c", *(unsigned char*)huff->item);

        if (*(unsigned char*)huff->item == 92)
        {
            fprintf(file, "%c", *(unsigned char*)(huff->item + 1));
        }

        print_pre_order_tree_on_file(file, huff->left);
        print_pre_order_tree_on_file(file, huff->right);
    }
}

void start_compression(BinaryTree_t* huff, char *fileName, HashTable_t *ht, long int fileLength, unsigned char first_byte,
                       unsigned char second_byte) {

    printf("Final Stage for Compression ... ");


    FILE *file = open_file(fileName, "rb");

    fileName = change_extension(fileName, fileLength);

    FILE *new_file = open_file(fileName, "wb");
    // Creates a new .huff file

    fprintf(new_file, "%c%c", first_byte, second_byte);
    // Prints the first and second bytes of the header in the file

    print_pre_order_tree_on_file(new_file, huff);
    // Prints the remaining bytes of the header (preorder) in the file

    unsigned int Queue = 0;
    // This integer is used as a queue of bits
    int queue_size = 0;

    int buffer = 0;
    buffer = fgetc(file);

    while (buffer != -1) // Gets char by char of the file and put into an int variable, getting its ascii value
    {
        Node_t *current = ht->table[buffer]->path->top;
        // Set current pointing to the top of the path (byte compressed.bmp) of table element 'buffer'

        while(current != NULL)
        {
            queue_size++;
            // Increase the queue_size

            Queue = Queue << 1;
            // Set all the bits to the left, creating a new 0 on the right

            if(current->bit == '1')
            {
                Queue = Queue | 1;
                // Sets last bit created to 1
            }

            current = current->next;
        }

        while(queue_size >= 8)
        {
            unsigned char byteAux = Queue >> (queue_size - 8);
            // Gets the highest 8 bits (the 8 from the left) of the Queue and put into byteAux

            queue_size = queue_size - 8;

            fprintf(new_file, "%c", byteAux);

            /* While there is 8 or more bits in the queue,
             * Gets the oldest 8 bits and print its respective char in the file.
             */
        }

        buffer = fgetc(file);
    }

    if(queue_size > 0) // If there is trash (remaining bits in the queue)
    {
        Queue = Queue << (8 - queue_size);
        // Move the remaining bits (8 - queue_size) times to the left, creating the same number of bits 0's

        unsigned char byteAux = Queue;

        fprintf(new_file, "%c", byteAux);

        /* If the current_size is greater than 0, it means that the total queue
         * size is not a multiple of 8, that is, an incomplete byte exists. So,
         * we insert bits 0's until the byte is complete
         */
    }

    fclose(file);
    fclose(new_file);

    printf("Done\n"
           "Compression process completed!\n");

    /* Prints the first and second bit (trash and tree size),
     * then print the preorder, then start to read the file.
     * Read the file char by char, each char is converted
     * into its respective path of the huffman tree created
     * before in bits values. Those bits are sets in a long int variable,
     * in a way that it work like a Queue. If the queue has 8 or more bits,
     * convert them to char and write in the new compressed.bmp file.
     */
}

#endif //HUFFMAN_PROJECT_COMPRESS_H
