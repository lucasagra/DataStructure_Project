//
// Created by phyllipe on 23/04/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "./headers/tree.h"
#include "./headers/readfile.h"

int main() {

    trie_t* trie = create_empty_trie('*');

    /* Create an empty trie tree with a root set as '*' value */

    char str[20];
    int again = 1;
    int check;

    FILE* fp = open_file();

    /* Read the trainer.txt file. That file contains predefined words which will be inserted into the trie.  */

    trie_train(trie, fp);

    /* Train the trie */

    while (again)
    {
        printf("\n<1> Procurar sugestao:\n<2> Apagar palavra:\n<0> Sair:\nOpcao: ");
        scanf("%d", &again);

        switch (again)
        {
            case 1:
                printf("\n");
                printf("Procurar por sugestoes: ");
                scanf("%s", str);
                search(trie, str);
                break;
            case 2:
                printf("\nPalavra: ");
                scanf("%s", str);
                check = remove_from_trie(trie, str);

                if (check == 1) {
                    printf("Palavra '%s' removida\n", str);
                }

                break;
            case 0:
                exit(0);
            default:
                exit(0);
        }
    }

    return 0;
}