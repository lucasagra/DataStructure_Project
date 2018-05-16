//
// Created by thiago on 19/04/18.
//

#ifndef HUFFMAN_PROJECT_PRIORITY_QUEUE_H
#define HUFFMAN_PROJECT_PRIORITY_QUEUE_H

/**
 * Why Priority Queue?
 *
 *  - We need a priority queue to build the huffman tree.
 *
 *  - Insertion will not be very costly since there will be a maximum of 255 binary trees in the queue
 */

typedef struct _pq PriorityQueue_t;

struct _pq {
    BinaryTree_t *head;
};

/* Statement of the structure needed to manipulate the priority queue
 * Everyone in line is a binary tree
 */

PriorityQueue_t* create_priority_queue() {

    PriorityQueue_t *new_pq = (PriorityQueue_t*)malloc(sizeof(PriorityQueue_t));
    new_pq->head = NULL;

    return new_pq;

    // Creates an empty priority queue
}

void enqueue_pq(PriorityQueue_t *pq, void *item, unsigned long long int frequency) {

    BinaryTree_t *new_bt = create_binary_tree(item, frequency, NULL, NULL);

    if (pq->head == NULL || (frequency <= pq->head->frequency))
    {
        new_bt->next = pq->head;
        pq->head = new_bt;
    }
    else
    {
        BinaryTree_t *current = pq->head;

        while ((current->next != NULL) && (frequency > current->next->frequency)) {
            current = current->next;
        }

        new_bt->next = current->next;
        current->next = new_bt;
    }

    //Enqueue the binary trees in the priority queue, from lowest to highest frequency
}

PriorityQueue_t* build_pq(PriorityQueue_t *pq, HashTable_t* ht) {

    printf("Building Priority Queue ... ");

    int i = 0;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (ht->table[i] != NULL)
        {
            enqueue_pq(pq, ht->table[i]->item, ht->table[i]->frequency);
        }
    }

    printf("Done\n");

    return pq;

    // Constructs the queue with all non-null positions

}

void free_pq(PriorityQueue_t *pq) {

    BinaryTree_t *aux;

    while (pq->head->next != NULL)
    {
        aux = pq->head->next;
        free(pq->head);
        pq->head = aux;
    }

    free(pq->head);
    free(pq);

    /* Set the space from all the BinaryTree elements free,
     * then set free the space from PriorityQueue.
     */
}

// ---- Print Functions ---- //

void print_pq(PriorityQueue_t *pq) {

    BinaryTree_t *current = pq->head;

    while (current != NULL)
    {
        unsigned char *item = current->item;

        if(*item == 92) // If *(item) points to '\'
        {
            printf("Item '%c' appears %llu times\n", *(item + 1), current->frequency);
            // Value get is from the next element *(item + 1), same as item[1],
        }
        else
        {
            printf("Item '%c' appears %llu times\n", *item, current->frequency);
            // else gets normal value *(item), same as item[0]
        }

        current = current->next;
    }

    /* Prints the decimal value of each item in the priority queue
     * followed by its respective frequency
     */

}

#endif //HUFFMAN_PROJECT_PRIORITY_QUEUE_H
