//
// Created by Bezerra on 26/04/2018.
//

#ifndef HUFFMAN_PROJECT_HEADER_COMPRESS_H
#define HUFFMAN_PROJECT_HEADER_COMPRESS_H

/**
 * Functions related to creating the header of the file to be compressed
 *
 *  - 3 bits for trash size
 *
 *  - 13 bits for tree size
 *
 *  - The rest of the bits are from each byte of each node of the tree
 */

int trash_size(unsigned long long int bits_quantity) {

    if(bits_quantity % 8 == 0)
    {
        return 0;
    }
    else
    {
        return (int)(8 - (bits_quantity % 8));
    }

    //Returns the trash size
}

unsigned int tree_pre_order_size(BinaryTree_t *bt, unsigned int *size) {

    if(bt != NULL)
    {
        if (bt->left != NULL)
        {
            *size = *size + 1;

            if(*(unsigned char*)bt->left->item == 92)
            {
                *size = *size + 1;
            }

            tree_pre_order_size(bt->left, size);
        }

        if (bt->right != NULL)
        {
            *size = *size + 1;

            if(*(unsigned char*)bt->right->item == 92)
            {
                *size = *size + 1;
            }

            tree_pre_order_size(bt->right, size);
        }

        return *size + 1; // + 1 from the bt root;
    }
    else
    {
        return *size;   // + 0 if root is null;
    }

    /* Gets how many nodes the tree have
     * Note: if the element is '\', it means that there is a '*' or '\' behind, therefore adds 1 extra size;
     */

}

void first_headers_byte(BinaryTree_t* huff, unsigned long long int bits_quant, unsigned char *first_byte, unsigned char *second_byte) {

    int trash = trash_size(bits_quant);

    *(first_byte) = (unsigned char)(trash << 5);
    // Set the 3 bits from the trash to the variable, 'NNN00000'

    unsigned int tree_size = 0;
    tree_size = tree_pre_order_size(huff, &tree_size);

    *(second_byte) = (unsigned char)tree_size;
    // Cast an unsigned char to a integer type to get only the last 8 bits from the left.

    unsigned char byteAux = tree_size >> 8;
    // Move all the bits of tree_size 8 times to the left and put into an char type, '000NNNNN'

    *(first_byte) = *(first_byte) | byteAux;
    // Sets the lasts 5 bits of the first byte.
}

#endif //HUFFMAN_PROJECT_HEADER_COMPRESS_H
