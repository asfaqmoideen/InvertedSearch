#include "include/inv_search.h"

int main(int argc, char* argv[]){

    int option = 0;

    Wlist *head[27] = {NULL};


    if(argc <= 1){
        printf("Enter the valid number of arguments\n");
        printf("./Slist.exe file1.txt file2.txt\n");
        return 0;
    }
    //Create the File linked list
    Flist *f_head = NULL;

    //Validation of file avaialability, dupicate, empty file
    printf("Validating the given file\n");
    file_validation_n_file_list(&f_head, argv);

   // print_Flist(f_head);
    if(f_head == NULL){
        printf("No files are added to the list\n");
        printf("Hence the process got terminated\n");
        return -1;
    }

    printf("Inverted Search - Fastest way to find words in different files\n");
    while(1){
        printf("1. Create Database\n2. Display Database\n3. Update Database\n4. Search Word\n5. Save to Database\n6. Exit\n");
        printf("Enter any of the above option : ");
        scanf("%d", &option);
        getchar();
        switch(option)
        {
            case 1:
                create_database(f_head, head);
                break;
            case 2:
                 display_database(head);
                break;
            case 3:
                update_database(head,&f_head);
                break;
            case 4:
                try_search_word(head);
                break;
            case 5:
                save_database(head);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid Choice\n");
        }
        printf("\nMain Menu\n");
    }
    return 0;
}