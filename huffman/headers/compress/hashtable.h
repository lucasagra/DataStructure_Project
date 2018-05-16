//
// Created by thiago on 19/04/18.
//

#ifndef HUFFMAN_PROJECT_HASH_TABLE_H
#define HUFFMAN_PROJECT_HASH_TABLE_H

/**
 * Why Hash Table?
 *
 *  - No collision problem in this algorithm
 *
 *  - Search: O(1)
 *
 *  - Insertion: O(1)
 */

#define MAX_SIZE 256

typedef struct _el Element_t;
typedef struct _ht HashTable_t;

struct _el {
    void *item;
    unsigned long long int frequency;
    Stack_t *path;
};

struct _ht {
    Element_t *table[MAX_SIZE];
};

/* Statement of the structures needed to manipulate the hash tables
 * Each position of the table points to an element
 * Each element has its representative, its frequency and its bit path (compressed.bmp with the huffman tree)
 */

HashTable_t* create_hash_table() {

    HashTable_t *new_ht = (HashTable_t*)malloc(sizeof(HashTable_t));

    int i;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        new_ht->table[i] = NULL;
    }

    return new_ht;

    // Create a hash table, pointing each table index to NULL
}

void put(HashTable_t *ht, int item) {

    int index = item;
    /* Index receive an int type which represents the ascii value
     * from a char read in the build_ht function (that's the hash function)
     */

    if (ht->table[index] == NULL)
    {
        Element_t *new_el = (Element_t*)malloc(sizeof(Element_t));
        new_el->path = create_stack();

        if(index == 42 || index == 92) // If item is '*' or '\'
        {
            unsigned char *new_char = malloc(2);
            //Allocate 2 bytes, 1 for the element '\' and another for the item

            *new_char = (unsigned char)92;
            //First element is '\'

            *(new_char + 1) = (unsigned char)item;
            //Second element is item (same as new_char[1])

            new_el->item = new_char;
            //Struct void *item points to the first space allocated above
        }
        else
        {
            unsigned char *new_char = malloc(1);
            //Allocate 1 byte for a char type

            *new_char = (unsigned char)item;
            //The space allocated receive the char item

            new_el->item = new_char;
            //Struct void *item points to the space allocated above
        }

        new_el->frequency = 1;
        ht->table[index] = new_el;
    }
    else
    {
        ++ht->table[index]->frequency;
    }

    /* Adds an item to the hash table, if its position is empty,
     * the item is created with frequency 1, if its position is occupied,
     * that is to say that the item is repeated, its frequency increases
     */
}

HashTable_t* build_ht(HashTable_t *ht, FILE* file) {

    printf("Reading File & Building Hash Table ...  ");

    int buffer = 0;
    buffer = fgetc(file);
    //Gets char by char of the file and put into an int variable, getting its ascii value

    while (buffer != -1)
    {
        put(ht, buffer);
        buffer = fgetc(file);
    }

    fclose(file);

    printf("Done\n");

    return ht;

    /* Constructs a hash table from each character, 1 by 1,
     * of the file called filename
     */
}

Stack_t* add_to_path(Stack_t *stack)  {

    Node_t *current = stack->top;
    Stack_t *new_stack = create_stack();

    while (current != NULL)
    {
        push(new_stack, current->bit);
        current = current->next;
    }

    return new_stack;

    /* Receives a stack, creates a new stack,
     * copies all the elements of the first one
     * to the new stack, then returns it.
     */
}

void build_paths(BinaryTree_t *huff, HashTable_t *ht, Stack_t *current) {

    if (!is_empty(huff))
    {
        if (is_leaf(huff))
        {
            if(*(unsigned char*)huff->item == 92) //If item is '\'
            {
                ht->table[*(unsigned char*)(huff->item + 1)]->path = add_to_path(current);
                //Sets pointer to next element *(item + 1)
            }
            else
            {
                ht->table[*(unsigned char*)huff->item]->path = add_to_path(current);
                //Else gets *(item)
            }
        }
        else
        {
            push(current, '0');
            build_paths(huff->left, ht, current);
            pop(current);

            push(current, '1');
            build_paths(huff->right, ht, current);
            pop(current);
        }
    }

    /* Recursive function that read all the tree, saving the path
     * in a stack as 0 for left and 1 for right. When reach a leaf,
     * copy the current stack to its respective HashTable path.
     */
}

unsigned long long int bits_quantity(HashTable_t* ht) {

    unsigned long long int bits = 0;

    int i;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        if(ht->table[i] != NULL)
        {
            bits += ((ht->table[i]->path->current_size) * (ht->table[i]->frequency));
        }
    }

    return bits;

    // Calculate how many bits the file will have after compressed.bmp (excluding the header)
}

void free_ht(HashTable_t *ht) {

    int i;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        if (ht->table[i] != NULL)
        {
            free(ht->table[i]);
        }
    }

    free(ht);

    /* Set free all the elements from the hash table,
     * then set free the hash table itself.
     */
}

// ---- Print Functions ---- //

void print_ht_bin(HashTable_t *ht) {

    int i;
    unsigned long long int bytes = 0;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        if(ht->table[i] != NULL)
        {

            printf("%d - ", ((*(unsigned char*)ht->table[i]->item) == 92) ? // If item = '\'
                            (*(unsigned char*)(ht->table[i]->item + 1)) :  // prints element of *(item+1)
                            (*(unsigned char*)ht->table[i]->item)          // else print element of *(item)
            );

            print_stack(ht->table[i]->path);
            printf(" - (bits)*(frequency) = (%d * %llu) = %llu \n", ht->table[i]->path->current_size, ht->table[i]->frequency,
                   (ht->table[i]->path->current_size)*(ht->table[i]->frequency));

            bytes = bytes + ht->table[i]->frequency;
        }
    }

    printf("\nBytes before compression: %llu bytes\n", bytes);

}

void print_ht(HashTable_t *ht) {

    int i;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        if(ht->table[i] != NULL)
        {
            unsigned char *item = ht->table[i]->item;

            if(*item == 92) // If *(item) points to '\'
            {
                printf("Item '%d' appears %llu times\n", *(item + 1), ht->table[i]->frequency);
                // Value get is from the next element *(item + 1), same as item[1],
            }
            else
            {
                printf("Item '%d' appears %llu times\n", *item, ht->table[i]->frequency);
                // else gets normal value *(item), same as item[0]
            }
        }
    }

}

#endif //HUFFMAN_PROJECT_HASH_TABLE_H
