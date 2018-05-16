//
// Created by phyllipe on 19/04/18.
//

#ifndef HUFFMAN_PROJECT_TREE_H
#define HUFFMAN_PROJECT_TREE_H

/**
 * Why Tree?
 *
 *  > We need to create binary trees to build the huffman tree
 */

typedef struct _bt BinaryTree_t;

struct _bt {
    void *item;
    unsigned long long int frequency;
    BinaryTree_t *left;
    BinaryTree_t *right;
    BinaryTree_t *next;
};

/* Statement of the structures needed to manipulate the binary trees
 * Each binary tree represents an element of the hash table
 */

int is_empty(BinaryTree_t* bt) {

    return (bt == NULL);

    // Return if a given binary_tree structure it is NULL or not
}

int is_leaf(BinaryTree_t* bt) {

    return (bt->left == NULL && bt->right == NULL);

    // Returns 1 if its a leaf
}

BinaryTree_t* create_binary_tree(void *item, unsigned long long int frequency, BinaryTree_t* left, BinaryTree_t* right) {

    BinaryTree_t *new_bt = (BinaryTree_t*)malloc(sizeof(BinaryTree_t));
    new_bt->item = item;
    new_bt->frequency = frequency;
    new_bt->left = left;
    new_bt->right = right;

    return new_bt;

    /* Create and return a binary_tree structure, with
     * a given void pointer (item), an integer representing
     * the frequency of (item), and two binary_tree pointers,
     * left and right.
     */
}

void free_bt(BinaryTree_t* bt) {

    if(!is_empty(bt))
    {
        free_bt(bt->left);
        free_bt(bt->right);

        if(*(unsigned char*)bt->item != 42) // If bt->item != '*'
        {
            free(bt->item);
            // Free space allocated to store the bytes (characters)
        }

        free(bt);
        // Set free the space allocated for this binary_tree;
    }

    // Set free all the space allocated to the tree, leaf by leaf.
}

// ---- Print Functions ---- //

void print_pre_order(BinaryTree_t *bt) {

    if(!is_empty(bt))
    {
        unsigned char *item = bt->item;

        if(*item == 92) // If *(item) points to '\'
        {
            printf("%c%c ", *item, *(item + 1));
            // Value get is from the pointer *(item) and next element *(item + 1), same as item[1],
        }
        else
        {
            printf("%c ", *item);
            // else gets normal value *(item), same as item[0]
        }

        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }

    // Print a given binary_tree struct in traversal pre-order

}

#endif //HUFFMAN_PROJECT_TREE_H
