//
// Created by Bezerra on 12/05/2018.
//

#ifndef ABB_AVL_AVL_H
#define ABB_AVL_AVL_H

struct binary_tree_avl {
    int item;
    int h;
    struct binary_tree_avl *left;
    struct binary_tree_avl *right;
} binary_tree_avl;

struct binary_tree_avl* create_empty_binary_tree_avl () {
    return NULL;
}

int is_empty_avl (struct binary_tree_avl *bt) {
    if(bt == NULL) {
        return 1;
    } else return 0;
}

int max (int a, int b) {
    return (a > b) ? a : b;
}

int h (struct binary_tree_avl *bt) {
    if(is_empty_avl(bt)) {
        return -1;
    } else {
        return 1 + max(h(bt->left), h(bt->right));
    }
}

struct binary_tree_avl* create_binary_tree_avl (int item, struct binary_tree_avl *left, struct binary_tree_avl *right) {
    struct binary_tree_avl *new_bt = (struct binary_tree_avl*) malloc(sizeof(struct binary_tree_avl));
    new_bt->left = left;
    new_bt->right = right;
    new_bt->item = item;

    return new_bt;
}

struct binary_tree_avl* search_avl (struct binary_tree_avl *bt, int item, int* comparacoes) {
    struct binary_tree_avl *current = bt;

    if((current->item == item) || (current == NULL)) {
        *comparacoes = *comparacoes + 1;
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

struct binary_tree_avl* rotate_left (struct binary_tree_avl *bt) {
    struct binary_tree_avl *subtree_root = NULL;

    if(bt != NULL && bt->right != NULL) {
        subtree_root = bt->right;
        bt->right = subtree_root->left;
        subtree_root->left = bt;
    }

    subtree_root->h = h(subtree_root);
    bt->h = h(bt);

    return subtree_root;
}

struct binary_tree_avl* rotate_right (struct binary_tree_avl *bt) {
    struct binary_tree_avl *subtree_root = NULL;

    if(bt != NULL && bt->left != NULL) {
        subtree_root = bt->left;
        bt->left = subtree_root->right;
        subtree_root->right = bt;
    }

    subtree_root->h = h(subtree_root);
    bt->h = h(bt);

    return subtree_root;
}

int balance_factor (struct binary_tree_avl *bt) {
    if(is_empty_avl(bt)){
        return 0;
    } else if((bt->left != NULL) && (bt->right != NULL)){
        return (bt->left->h - bt->right->h);
    } else if ((bt->left != NULL) && (bt->right == NULL)){
        return (1 + bt->left->h);
    } else {
        return (-bt->right->h - 1);
    }
}

struct binary_tree_avl* add_avl (struct binary_tree_avl *bt, int item) {
    if(is_empty_avl(bt)) {
        return create_binary_tree_avl(item, NULL, NULL);
    } else if (item < bt->item) {
        bt->left = add_avl(bt->left, item);
    } else {
        bt->right = add_avl(bt->right, item);
    }

    bt->h = h(bt);
    struct binary_tree_avl *child;

    if(balance_factor(bt) == 2 || balance_factor(bt) == -2) {
        if(balance_factor(bt) == 2) {
            child = bt->left;
            if(balance_factor(child) == -1) {
                bt->left = rotate_left(child);
            }
            bt = rotate_right(bt);
        } else if (balance_factor(bt) == -2) {
            child = bt->right;
            if(balance_factor(child) == 1) {
                bt->right = rotate_right(child);
            }
            bt = rotate_left(bt);
        }
    }
    return bt;
}

void free_all_avl (struct binary_tree_avl *bt) {
    if(!is_empty_avl(bt)) {
        free_all_avl(bt->left);
        free_all_avl(bt->right);
        free(bt);
    }
}

struct binary_tree_avl* clear_avl (struct binary_tree_avl* bt) {
    free_all_avl(bt);
    return create_empty_binary_tree_avl();
}

#endif //ABB_AVL_AVL_H
