#include "../include/inv_search.h"

int update_database(Wlist *head[], Flist **f_head)
{
    //prompt user to enter the new file
    char file_name[FNAME_SIZE];
    printf("Enter the file to be added to the file linked list: ");
    scanf("%s", file_name);

    //validation of file entered
    //4. TODO -- file_validation_n_file_list -- copy and paste without the loop and cntinue
    //single file we are adding to the file linked list
    //create the database for the updated file -- bring the f head to the last node
    int file_status;
     printf("%s is being validated\n", file_name);
        file_status = isFileEmpty(file_name);
        if(file_status == FILE_NOTAVAILABLE)
        {
            printf("FIle %s is not avaialable\n",file_name);
            printf("Hence we are not adding that file into Linked List\n");
        }
        else if(file_status == FILE_EMPTY)
        {
            printf("Contents are empty\n");
            printf("Hence we are not adding that file into Linked List\n");
        }
        else
        {
            int file_creation_status = to_create_list_of_files(f_head, file_name);
            if(file_creation_status == SUCCESS)
            {
                printf("Successfully added %s file into Linked List\n", file_name);
            }
            else if(file_creation_status == REPEATATION)
            {
                printf("The file names %s already exits\n", file_name);
            }
            else
            {
                printf("Something went wrong!!!!\n");
            }
        }


    while(*f_head)
    {
        if(strcmp((*f_head)->file_name, file_name) == 0)
        {
            create_database(*f_head, head);
        }
        *f_head = (*f_head) -> link;
    }
}