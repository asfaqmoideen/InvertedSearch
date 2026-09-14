#include "inv_search.h"

int save_database(Wlist *head[])
{
    char file_name[FNAME_SIZE];
    //.txt or CSV
    printf("Enter the filename: ");
    scanf("%s", file_name);

    // open the file
    FILE *fptr = fopen(file_name, "w");
    if(fptr == NULL){
        printf("Eror: opening the file\n");
        return FAILURE;
    }
    for (int i = 0; i < 27; i++)
    {
        // check if the list is empty or not
        if(head[i] != NULL)
        {
           write_databasefile(head[i], &fptr);
        }
    }
}

void write_databasefile(Wlist *head, FILE** databasefile){

    

}