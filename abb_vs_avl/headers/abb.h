//
// Created by Bezerra on 12/05/2018.
//

#ifndef ABB_AVL_ABB_H
#define ABB_AVL_ABB_H

struct binary_tree {
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

struct binary_tree* create_empty_binary_tree () {
    return NULL;
}

int is_empty (struct binary_tree *bt) {
    if(bt == NULL) {
        return 1;
    } else return 0;
}

struct binary_tree* create_binary_tree (int item, struct binary_tree *left, struct binary_tree *right) {
    struct binary_tree *new_bt = (struct binary_tree*) malloc(sizeof(struct binary_tree));
    new_bt->left = left;
    new_bt->right = right;
    new_bt->item = item;

    return new_bt;
}

struct binary_tree* add (struct binary_tree *bt, int item) {
    if(is_empty(bt)) {
        bt = create_binary_tree(item, NULL, NULL);
    } else if (item < bt->item) {
        bt->left = add(bt->left, item);
    } else {
        bt->right = add(bt->right, item);
    }
    return bt;
}

struct binary_tree* search (struct binary_tree *bt, int item, int* comparacoes) {

    struct binary_tree *current = bt;

    if((current->item == item) || (current == NULL)) {
        if(current->item == item){
            *comparacoes = *comparacoes + 1;
        }
        return current;
    } else {
        while(!(current->left == NULL && current->right == NULL)) {
            *comparacoes = *comparacoes + 1;
            if(item < current->item){
                if(current->left != NULL) current = current->left;
                else break;
            } else {
                if(current->right != NULL) current = current->right;
                else break;
            }
            if(current->item == item) {
                *comparacoes = *comparacoes + 1;
                return current;
            }
        }
        return NULL;
    }
}

void free_all (struct binary_tree *bt) {
    if(!is_empty(bt)) {
        free_all(bt->left);
        free_all(bt->right);
        free(bt);
    }
}

struct binary_tree* clear (struct binary_tree * bt) {
    free_all(bt);
    return create_empty_binary_tree();
}

void print_pre_order (struct binary_tree *bt) {
    if(!is_empty(bt)) {
        printf("%d ", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

#endif //ABB_AVL_ABB_H
