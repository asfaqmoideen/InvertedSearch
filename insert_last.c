#include "inv_search.h"
// extern char *file_name;

int insert_at_last(Wlist **head, data_t *data, char *filename)
{
    // create the node
    Wlist *new = malloc(sizeof(Wlist));
    if (new == NULL)
        return FAILURE;

    // update the fields
    new->file_count = 1;
    strcpy(new->word, data);
    new->Tlink = NULL;
    new->link = NULL;
    update_link_table(&new, filename);
    // 2. head is empty
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    //if list is non empty
    Wlist *temp = *head;
    while(temp->link)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}
int update_link_table(Wlist *head[], char*filename)
{
    //create node
    Ltable *new = malloc(sizeof(Ltable));
    if(new == NULL)
    return FAILURE;
    //update the fields
    new->word_count = 1;
    strcpy(new->file_name,filename);
    new->table_link = NULL;
    (*head)->Tlink = new;
    return SUCCESS;
}