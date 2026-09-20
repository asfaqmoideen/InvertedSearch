#include "../include/inv_search.h"

int hash_function(const char *word){
    return tolower(word[0]) % 97;
}

int print_Flist(Flist *head){
    if(head == NULL){
        printf("The list is empty\n");
    }

    while(head){
        printf("file : %s ->", head->file_name);
        head = head->link;
    }
}