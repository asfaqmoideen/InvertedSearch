#include "inv_search.h"

void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i = 1; //executable file is excuded
    int empty;
    while(argv[i] != NULL)
    {   
        empty = isFileEmpty(argv[i]);
        if(empty == FILE_NOTAVAILABLE)
        {
            printf("FIle %s is not avaialable\n", argv[i]);
            printf("Hence we are not adding that file into Linked List\n");
            i++;
            continue;
        }
        else if(empty == FILE_EMPTY)
        {
            printf("Contents are empty\n");
            printf("Hence we are not adding that file into Linked List\n");
            i++;
            continue;
        }
        else
        {
            int ret_val = to_create_list_of_files(f_head, argv[i]);
            if(ret_val == SUCCESS)
            {
                printf("Successfully added %s file into Linked List\n", argv[i]);
            }
            else if(ret_val == REPEATATION)
            {
                printf("The file names %s already exits\n", argv[i]);
            }
            else
            {
                printf("Something went wrong!!!!\n");
            }
            i++;
        }
    }
}
//function is to chek file avaialability and content
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        if(errno == ENOENT)
        {
            return FILE_NOTAVAILABLE;
        }
    }
    fseek(fptr, 0, SEEK_END);
    if(ftell(fptr) == 0)
    {
        return FILE_EMPTY;
    }
}

//create the file linked list
int to_create_list_of_files(Flist **f_head, char *name)
{
    int res = search_file_list(*f_head, name);
    if(res == -4) {
        return REPEATATION;
    }
    
    if(insert_filename_at_last(f_head, name) == FAILURE) {
        return FAILURE;
    }

    return SUCCESS;

}

int search_file_list(Flist *fhead, char *name){

    if(fhead == NULL){
        return FAILURE;
    }
    while (fhead)
    {
        if(strcmp(fhead->file_name, name) == 0) {
            return REPEATATION;
        }
        fhead = fhead->link;
    }
    return 0;
    
}

int insert_filename_at_last(Flist **f_head, char *file_name){

    Flist *new_node = malloc(sizeof(Flist));
    if(!new_node){
        return FAILURE;
    }

    strcpy(new_node->file_name, file_name);
    new_node->link = NULL;

    if(*f_head == NULL){
        *f_head = new_node;
        return SUCCESS;
    }

    Flist *temp = *f_head;
    while(temp->link != NULL){
        temp = temp->link;
    }
    temp->link = new_node;

    return SUCCESS;

}