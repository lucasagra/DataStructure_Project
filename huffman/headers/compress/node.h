//
// Created by thitc on 30/04/2018.
//

#ifndef HUFFMAN_PROJECT_NODE_H
#define HUFFMAN_PROJECT_NODE_H

/* This is an auxiliary structure
 * Its only use is for saving bits as a list
 */

typedef struct _node Node_t;

struct _node {
    unsigned char bit;
    Node_t *next;
};

Node_t* create_node(unsigned char bit) {

    Node_t *new_node = (Node_t*)malloc(sizeof(Node_t));
    new_node->bit = bit;

    return new_node;

    // Create a node with the designed bit
}

#endif //HUFFMAN_PROJECT_NODE_H
