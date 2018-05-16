//
// Created by Bezerra on 29/04/2018.
//

#ifndef HUFFMAN_PROJECT_DECOMPRESS_H
#define HUFFMAN_PROJECT_DECOMPRESS_H

/**
 * Intuitively in this header, the functions of each structure used in the
 * compression process are already included (most will not be used), also
 * including the implementation of the main function: decompress()
 */

#include "decompress/header.h"

void start_decompression(FILE* file, char* fileName, BinaryTree_t* huffTree, int trashSize, long int compressedBytesLength);

void decompress(char *fileName) {

    FILE* file = open_file(fileName, "rb");
    // Open the file to read the bytes

    long int compressed_byte_length = get_file_length(file);
    // Calculates how bytes the file has

    unsigned int trash_size, tree_size;
    get_trash_and_tree_size(file, &trash_size, &tree_size);
    // Get the trash and tree sizes from the compressed.bmp file header

    compressed_byte_length = (long int)(compressed_byte_length - 2 - tree_size);
    /* Calculates how many compressed.bmp bytes the file has, minus 2 bytes of the trash and
     * minus the size of the tree (bytes of each node of the tree that are in the header)
     */

    printf("Building Huffman Tree ... ");

    BinaryTree_t* huffman_tree = NULL;

    huffman_tree = construct_huffman_decompress_tree(huffman_tree, file, tree_size);
    // Create the huffman tree with the pre-order traversal

    printf("Done\n");

    start_decompression(file, fileName, huffman_tree, (int)trash_size, compressed_byte_length);
    // Start the file decompression

    fclose(file);
    free_bt(huffman_tree);

}

void start_decompression(FILE* file, char* fileName, BinaryTree_t* huffTree, int trashSize, long int compressedBytesLength) {

    printf("Final Stage for Decompression ... ");

    int fileNameLength = get_file_name_length(fileName) - 4;
    fileName = realloc(fileName, (size_t)(fileNameLength));
    fileName[fileNameLength - 1] = '\0';
    // Recalculate the decompressed file name size

    FILE* decompressed = open_file(fileName, "wb"); // Create a file to write

    unsigned char byte;
    long int bytesRead = 0;
    int i;

    BinaryTree_t *current = huffTree;

    while (bytesRead < compressedBytesLength - 1) // Run through the compressed.bmp bytes, but not the last one
    {

        fscanf(file, "%c", &byte);
        // Read a byte from the file

        for (i = 7; i >= 0; --i)
        {
            if (is_bit_set((unsigned int)byte, i)) // Verify each bit from the byte and check
            {
                current = current->right; // If it is 1, go to the right
            }
            else
            {
                current = current->left; // Else, go to the left
            }

            if (is_leaf(current)) // If we find a leaf, it means that it is time to print that tree value
            {
                unsigned char* outputByte = current->item;

                if (outputByte[0] == 92) // If it's '\'
                {
                    fprintf(decompressed, "%c", outputByte[1]);
                }
                else
                {
                    fprintf(decompressed, "%c", outputByte[0]);
                }
                // Check if we have the escape character or not

                current = huffTree;
                // Return to root
            }
        }

        ++bytesRead;
    }

    /* So far the algorithm has read up to the last but one byte, because the last byte will depend
     * on the size of the trash, so the functions below represent the last byte of the file.
     */

    fscanf(file, "%c", &byte);

    for (i = 7; i >= trashSize; --i) // Check each bit from the last byte, excluding the trash
    {
        if (is_bit_set((unsigned int)byte, i))
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }

        if (is_leaf(current))
        {
            unsigned char* outputByte = current->item;

            if (outputByte[0] == 92) // If it's '\'
            {
                fprintf(decompressed, "%c", outputByte[1]);
            }
            else
            {
                fprintf(decompressed, "%c", outputByte[0]);
            }

            current = huffTree;
        }
    }

    fclose(decompressed);

    printf("Done\n"
           "Decompression process completed!\n");

    /* This function is the core for the decompression function, here the compressed.bmp bytes
     * are checked, bit by bit, run the tree and since we find a leaf, the new decompressed
     * byte (the tree value) will be printed on the new file
     */
}

#endif //HUFFMAN_PROJECT_DECOMPRESS_H
