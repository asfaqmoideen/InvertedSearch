#include "inv_search.h"

void create_database(Flist *f_head, Wlist *head[])
{   
    while(f_head)
    {
        //read each file one after the other
        printf("Creating database for the file %s\n", f_head->file_name);
        read_datafile(f_head, head, f_head->file_name);
        //move the file head to next node
        f_head = f_head->link;
    }
}

//function to read the content of file and create dtabase for the word
void read_datafile(Flist *f_head, Wlist *w_head[], char *filename)
{
    printf("Reading datafile for  %s\n", f_head->file_name);
    FILE *fptr = fopen(filename, "r");
    if(fptr == NULL){
        printf("Error: Opening the file\n");
        return;
    }

    char word[WORD_SIZE];
    while(fscanf(fptr, "%s", word) != EOF)
    {   
        int uniqueword_flag = 1;
        //find the index
        int index = hash_function(word);
        //check for the true range
        if(!(index >= 0 &&  index <= 25))
        {
            index = 26;
        }
        if(w_head[index] != NULL)
        {
            update_wordcount_ifword_exists(w_head[index], word, filename, &uniqueword_flag);
        }
        if(uniqueword_flag)
            insert_at_last(&w_head[index], word, filename);
    }
    fclose(fptr);
}

void update_wordcount_ifword_exists(Wlist *whead, char * word, char* filename, int *uniqueword_flag){

    while(whead)
    {
        if(strcmp(whead->word, word) == 0)
        {   
            update_word_count(&whead, filename);
            *uniqueword_flag = 0;
             return;
        }
        whead=whead->link;
    }
}


int update_word_count(Wlist **head, char *filename)
{
    Ltable *temp = (*head)->Tlink;

    // Traverse all Ltable nodes for this word
    while (temp != NULL)
    {
        // If the file is already linked, just increment the word count
        if (strcmp(temp->file_name, filename) == 0)
        {
            temp->word_count++;
            return SUCCESS;
        }
        temp = temp->table_link;
    }

    // File was NOT found in the existing Ltable nodes: create a new one
    return insert_tlink_at_last(head, filename);
}

int insert_tlink_at_last(Wlist **head, char *filename)
{
    Ltable *new_tlink = malloc(sizeof(Ltable));
    if (new_tlink == NULL) {
        return FAILURE;
    }

    strcpy(new_tlink->file_name, filename);
    new_tlink->word_count = 1;
    new_tlink->table_link = NULL;

    (*head)->file_count++;

    // Base case: If head has no Tlink yet
    if ((*head)->Tlink == NULL) {
        (*head)->Tlink = new_tlink;
        return SUCCESS;
    }

    // Traverse to the last Ltable node and link
    Ltable *temp = (*head)->Tlink;
    while (temp->table_link != NULL) {
        temp = temp->table_link;
    }
    temp->table_link = new_tlink;

    return SUCCESS;
}