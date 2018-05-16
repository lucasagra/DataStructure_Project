//
// Created by Bezerra on 29/04/2018.
//

#ifndef HUFFMAN_PROJECT_HEADER_DECOMPRESS_H
#define HUFFMAN_PROJECT_HEADER_DECOMPRESS_H

/* Functions related to manipulate the header of the compressed.bmp file
 */

void get_trash_and_tree_size(FILE* file, unsigned int* trash, unsigned int* tree) {

    printf("Reading Header ... ");

    unsigned char header_byte = (unsigned char)fgetc(file);
    *(trash) = header_byte >> 5;

    unsigned char five_bytes_from_tree = header_byte << 3;
    *(tree) = five_bytes_from_tree >> 3;
    header_byte = (unsigned char)fgetc(file);
    *(tree) <<= 8;
    *(tree) |= header_byte;

    printf("Done\n");

    /* Get the two first bytes from the file and then, using bitwise operation
     * save the 3 first bits as trash size and the others 13 bits as the tree size */
}

BinaryTree_t* construct_huffman_decompress_tree(BinaryTree_t* bt, FILE* file, int size) {

    if (size < 0) return NULL; // Recursion stop

    unsigned char byte = (unsigned char)fgetc(file);

    if (byte == 42) // If byte is '*'
    {
        bt = create_binary_tree("*", 0, NULL, NULL);

        bt->left = construct_huffman_decompress_tree(bt->left, file, --size);

        bt->right = construct_huffman_decompress_tree(bt->right, file, --size);

        // Creates a Binary Tree with the huff symbol '*'
    }
    else
    {
        if (byte == 92) // If byte is '\'
        {
            unsigned char* double_item = malloc(3);
            double_item[0] = 92;
            //double_item[0] = '\'

            byte = (unsigned char)fgetc(file);
            double_item[1] = byte;
            double_item[2] = '\0';

            bt = create_binary_tree(double_item, 0, NULL, NULL);

            /* If the byte is an escape character, we need to read the next character,
             * which the escape character is referencing, so the node item will be this 3-position string
             */
        }
        else
        {
            unsigned char* single_item = malloc(2);
            single_item[0] = byte;
            single_item[1] = '\0';

            bt = create_binary_tree(single_item, 0, NULL, NULL);
        }
    }

    return bt;

    /* Run through the number of bytes that we got on the previous "get_trash_and_tree_size"
     * and recursively create the huffman tree */
}

#endif //HUFFMAN_PROJECT_HEADER_DECOMPRESS_H
