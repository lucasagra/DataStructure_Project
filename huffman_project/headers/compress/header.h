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

int tree_pre_order_size(BinaryTree_t *bt, int *size) {

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

void enqueue_bits(Queue_t *queue, int item, int num_bits){

    unsigned char *bits = int_to_binary_char((unsigned int)item, num_bits);
    //*bits points to a string of size 'num_bits' which contains the bits which represent item

    int i;

    for(i = 0; i < num_bits; ++i)
    {
        enqueue(queue, bits[i]);
        // Enqueues bit by bit as a char to the queue
    }

    free(bits);
}

Queue_t* build_header(BinaryTree_t* huff, Queue_t* new_queue, unsigned long long int bits_quant) {

    printf("Building Header ... ");

    int trash = trash_size(bits_quant);
    //Gets trash size

    int tree_size = 0;
    tree_size = tree_pre_order_size(huff, &tree_size);
    //Gets how many elements the tree has

    enqueue_bits(new_queue, trash, 3);
    // Function will receive trash size as an unsigned int (4 bytes), then will enqueue the last 3 bits 1 by 1;

    enqueue_bits(new_queue, tree_size, 13);
    // Function will receive tree size as an unsigned int (4 bytes), then will enqueue the last 13 bits 1 by 1;

    unsigned char *tree_nodes = malloc(tree_size * sizeof(unsigned char));
    int index = 0;
    get_tree_nodes_pre_order(huff, tree_nodes, &index);
    // Tree_elements will point to a string with all chars of the Huffman Tree in preorder traversal

    int i;

    for(i = 0; i < tree_size; ++i)
    {
        enqueue_bits(new_queue, tree_nodes[i], 8);
        /* The array tree_nodes stores the byte representing the node of
         * position i in the huffman tree (pre-order)
         */
    }

    free(tree_nodes);

    printf("Done\n");

    return new_queue;
}

#endif //HUFFMAN_PROJECT_HEADER_COMPRESS_H
