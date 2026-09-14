#include "inv_search.h"

void create_database(Flist *f_head, Wlist *head[])
{   
    print_Flist(f_head);
    while(f_head)
    {
        //read each file one after the other
        printf("Creating database for the file %s\n", f_head->file_name);
        read_datafile(f_head, head, f_head->file_name);
        //move the file head to next node
        f_head = f_head->link;
    }
    printf("Created database for the file %s\n", f_head->file_name);
}

//function to read the content of file and create dtabase for the word
void read_datafile(Flist *f_head, Wlist *w_head[], char *filename)
{
    printf("Reading datafile for  %s\n", f_head->file_name);
    FILE *fptr = fopen(filename, "r");
    // file_name = filename;
    //validation for open
    if(fptr == NULL){
        printf("Error: Opening the file\n");
        return;
    }

    char word[WORD_SIZE];
    while(fscanf(fptr, "%s", word) != EOF)
    {   
        printf("%s in %s\n", word, filename);
        int flag = 1;
        //find the index
        int index = hash_function(word);
        //check for the true range
        if(!(index >= 0 &&  index <= 25))
        {
            index = 26;
        }
        if(w_head[index] != NULL)
        {
            Wlist *temp = w_head[index];
            while(temp)
            {
                if(strcmp(temp->word, word) == 0)
                {   
                    update_word_count(&temp, filename);
                    flag = 0;
                    break;
                    
                }
                temp=temp->link;
            }
        }
        if(flag == 1)
            insert_at_last(&w_head[index], word, filename);
    }
    fclose(fptr);
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
            printf("Same file name (%s), updated word count is %d\n", filename, temp->word_count);
            return SUCCESS;
        }
        temp = temp->table_link;
    }

    // File was NOT found in the existing Ltable nodes: create a new one
    printf("Word found in new file (%s), creating a new Tlink\n", filename);
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