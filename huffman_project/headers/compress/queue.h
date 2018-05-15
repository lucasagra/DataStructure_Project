//
// Created by Lucas on 26-Apr-18.
//

#ifndef HUFFMAN_PROJECT_LIST_H
#define HUFFMAN_PROJECT_LIST_H

/**
 * Why queue?
 *
 *  - Dynamic allocation for header and to write on .huff file
 */

typedef struct _queue Queue_t;

struct _queue {
    Node_t *head;
    Node_t *tail;
    int current_size;
};

Queue_t* create_queue() {

    Queue_t *new_queue = (Queue_t*)malloc(sizeof(Queue_t));

    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->current_size = 0;

    return new_queue;
}

void enqueue(Queue_t *queue, unsigned char bit){

    Node_t *new_node = create_node(bit);

    if(queue->current_size == 0) {
        queue->head = new_node;
        queue->tail = new_node;
    }
    else
    {
        queue->tail->next = new_node;
        queue->tail = queue->tail->next;
    }

    queue->current_size++;

    // Adds a new node at the end of the queue (tail).

}

unsigned char dequeue(Queue_t *queue){

    if(queue->current_size > 0) {

        Node_t *current = queue->head;
        unsigned char bit = queue->head->bit;

        if (queue->current_size == 1)
        {
            queue->head = NULL;
            queue->tail = NULL;
        }
        else
        {
            queue->head = queue->head->next;
        }

        free(current);
        queue->current_size--;
        return bit;
    }
    else
    {
        printf("Error, empty queue\n");
        return 0;
    }

    /* Returns a bit as a character from the head of the
     * queue (first node that has been enqueued), then sets
     * the head to the next node and free the previous one.
     */
}

void free_queue(Queue_t* queue){

    if(queue->head != NULL) {

        Node_t *current = queue->head;

        while (current != NULL) {
            queue->head = queue->head->next;
            free(current);
            current = queue->head;
        }

        free(queue);
    }
}

// ---- Print Functions ---- //

void print_queue(Queue_t* queue){

    if(queue->head != NULL)
    {
        Node_t* current = queue->head;

        while(current != NULL)
        {
            printf("%c ", current->bit);
            current = current->next;
        }
    }

}

#endif //HUFFMAN_PROJECT_LIST_H
