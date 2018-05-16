//
// Created by Lucas on 24-Apr-18.
//

#ifndef  HUFFMAN_PROJECT_HUFF_H
#define  HUFFMAN_PROJECT_HUFF_H

/**
 * Why Huffman Encoding?
 *
 *  - The idea is not to have the prefix of one encoding being the prefix of another,
 *  the huffman tree prevents this from happening
 */

unsigned long long int frequency(BinaryTree_t *bt) {

    return (bt->frequency + bt->next->frequency);

    // Return the two current lowest frequencies

}

void enqueue_huff(PriorityQueue_t *pq, BinaryTree_t* new_bt) {

    if (pq->head == NULL || (new_bt->frequency <= pq->head->frequency))
    {
        new_bt->next = pq->head;
        pq->head = new_bt;
    }
    else
    {
        BinaryTree_t *current = pq->head;

        while ((current->next != NULL) && (new_bt->frequency > current->next->frequency)) {
            current = current->next;
        }

        new_bt->next = current->next;
        current->next = new_bt;
    }

    //Enqueues a BinaryTree in the PriorityQueue, from lowest to highest frequency
}

BinaryTree_t* build_huffman(PriorityQueue_t* pq) {

    printf("Building Huffman Tree ... ");

    if(pq->head != NULL)
    {
        unsigned char *huff_symbol = malloc(1);
        *huff_symbol = (unsigned char)42;
        // Standard symbol for new huffman binary trees -> '*'

        if(pq->head->next == NULL) // If there is only 1 item
        {
            BinaryTree_t *new_bt = create_binary_tree(huff_symbol, pq->head->frequency, pq->head, NULL);
            new_bt->next = NULL;
            //Creates a BinaryTree '*' with the item as its left child

            pq->head = new_bt;

            return pq->head;
        }

        while(pq->head->next != NULL) //While there is more than 1 element on queue
        {
            BinaryTree_t *current = pq->head;
            //Creates a pointer to the current queue head

            BinaryTree_t *new_bt = create_binary_tree(huff_symbol, frequency(current), current, current->next);
            new_bt->next = NULL;
            //Sets the elements of the new binary_tree

            pq->head = current->next->next;
            //Sets the head of the priority queue to the third item

            current->next->next = NULL;
            current->next = NULL;
            //Sets the leaves *next to NULL;

            enqueue_huff(pq, new_bt);
            //Puts the new binary_tree on its queue's properly position
        }
    }

    printf("Done\n");

    return pq->head;

    /* While there is more than 1 element on the priority queue,
     * get the 2 lowest ones and make a parent for them (new binary tree),
     * which will have the frequency equal to the sum of its children, and
     * void *item pointing to '*', then put the parent back, sorted, on the
     * priority queue.
     */
}

#endif //HUFFMAN_PROJECT_HUFF_H
