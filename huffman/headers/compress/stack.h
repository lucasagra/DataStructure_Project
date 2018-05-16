//
// Created by thiago on 25/04/18.
//

#ifndef HUFFMAN_PROJECT_STACK_H
#define HUFFMAN_PROJECT_STACK_H

/**
 * Why Stack?
 *
 *  > We chose to use a stack to let the manipulation of the paths while traversing tree easier
 *  because while the tree is traversed, the binaries (0 or 1) are pushed on the stack, however in
 *  this way they are reversed, but by copying the stack in the path of each byte in the hash table,
 *  it reverses again, and the inverse of the reverse is the original path.
 *
 *  - Insertion: O(1)
 *
 *  - Removal: O(1)
 *
 */

typedef struct _stack Stack_t;

struct _stack {
    Node_t *top;
    short int current_size;
};

/* Statement of the structure needed to manipulate the stack
 * This stack stores the compressed.bmp binary of each byte
 * Each node represents each bit of the compressed.bmp element
 */

Stack_t* create_stack() {

    Stack_t *new_stack = (Stack_t*)malloc(sizeof(Stack_t));
    new_stack->top = NULL;
    new_stack->current_size = 0;

    return new_stack;

    // Create a empty stack
}

void push(Stack_t *stack, unsigned char bit) {

    Node_t *new_node = create_node(bit);

    new_node->next = stack->top;
    stack->top = new_node;
    stack->current_size++;

    // Insert at the top of the stack
}

void pop(Stack_t *stack) {

    if (stack->top != NULL)
    {
        Node_t *temp = stack->top;
        stack->top = stack->top->next;
        stack->current_size--;
        free(temp);
    }

    // Remove the top of the stack

}

void free_stack(Stack_t *stack) {

    while (stack->current_size > 0)
    {
        pop(stack);
    }

    free(stack);
}

// ---- Print Functions ---- //

void print_stack(Stack_t *stack) {

    Node_t *current = stack->top;

    while (current != NULL)
    {
        printf("%c", current->bit);
        current = current->next;
    }

}

#endif //HUFFMAN_PROJECT_STACK_H
