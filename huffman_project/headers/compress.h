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
#include "compress/queue.h"
#include "compress/header.h"

void start_compression(Queue_t* queue, char *fileName, HashTable_t* ht, long int fileLength );

void compress(char *fileName) {

    FILE* file = open_file(fileName, "rb");

    HashTable_t *ht = build_ht(create_hash_table(), file);
    //Builds HashTable with every different byte, counting its respective frequency

    PriorityQueue_t *pq = build_pq(create_priority_queue(), ht);
    //Builds a Priority Queue with the HashTable bytes, sorting from the lowest to highest frequencies

    BinaryTree_t *huff = build_huffman(pq);
    //Builds the Huffman Tree from the Priority Queue

    printf("Building Paths ... ");
    build_paths(huff, ht, create_stack());
    printf("Done\n");

    Queue_t *header = build_header(huff, create_queue(), bits_quantity(ht));
    //Builds a Queue with the header bits, which will manage the bits to be compressed later

    start_compression(header, fileName, ht, get_file_name_length(fileName));
    //Create the compressed file

    free_ht(ht);
    free_pq(pq);
    free_bt(huff);
    free_queue(header);

}

void dequeue_and_write(Queue_t *queue, FILE *file) {

    int i;
    unsigned char string[8];

    for(i = 0; i < 8; i++)
    {
        string[i] = dequeue(queue);
    }
    string[8] = '\0';

    unsigned int decimal = (unsigned int)binary_char_to_int(string, 7, 0);

    fprintf(file, "%c", decimal);

    /* Creates a string of 8 chars, dequeues 8 bits from
     * the queue and put into that string, then convert the
     * string bits into a integer and print it as a char into
     * the selected file.
     */
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

void start_compression(Queue_t* queue, char *fileName, HashTable_t *ht, long int fileLength) {

    printf("Final Stage for Compression ... ");

    FILE *file = open_file(fileName, "rb");

    fileName = change_extension(fileName, fileLength);

    FILE *new_file = open_file(fileName, "wb"); // Create a new .huff file

    int buffer = 0;
    buffer = fgetc(file);

    while (buffer != -1) // Gets char by char of the file and put into an int variable, getting its ascii value
    {
        Node_t *current = ht->table[buffer]->path->top;
        // Set current pointing to the top of the path (byte compressed) of table element 'buffer'

        while(current != NULL)
        {
            enqueue(queue, current->bit);
            current = current->next;
        } // Enqueues all the path stack

        while(queue->current_size >= 8)
        {
            dequeue_and_write(queue, new_file);

            /* While there is 8 or more bits in the queue,
             * Dequeue 8 bits and print its respective char in the file.
             */
        }

        buffer = fgetc(file);
    }

    if(queue->current_size > 0) // If there is trash (less than 8 bits remaining in the queue)
    {
        while (queue->current_size < 8)
        {
            enqueue(queue, '0');
            // Enqueues bits '0' until complete 8
        }

        dequeue_and_write(queue, new_file);

        /* If the current_size is greater than 0, it means that the total queue
         * size is not a multiple of 8, that is, an incomplete byte exists. So,
         * we enqueue bits '0' until the byte is complete
         */
    }

    fclose(file);
    fclose(new_file);

    printf("Done\n"
           "Compression process completed!\n");

    /* Read the file char by char, each char is converted
     * into its respective path of the huffman tree created
     * before in bits values. Those bits are enqueued into
     * the queue. If the queue has 8 or more bits, convert them
     * into a integer and write in the new compressed file as
     * a char.
     */
}

#endif //HUFFMAN_PROJECT_COMPRESS_H
