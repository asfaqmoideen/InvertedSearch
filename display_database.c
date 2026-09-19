#include "inv_search.h"
#define BOLD "\033[1m"
#define RESET "\033[0m"

void display_database(Wlist *head[])
{
    //Display the content of all the head
    printf("\n+-------+--------------------+------------+------------+------------+\n");
    printf("| %-5s | %-18s | %-10s | %-10s | %-10s |\n", BOLD "Index", "Word","File Count" ,"File Name", "Word Count" RESET);
    printf("+-------+--------------------+------------+------------+------------+\n");
    for(int i = 0; i < 27;i++)
    {
        //print alphabetically one after the other
        if(head[i] != NULL)
        {
            print_word_details(head[i]);
        }
    }
}
int print_word_details(Wlist *head)
{
    //traverse through the Wlst
    while(head != NULL)
    {   

       printf("| %-5d | %-18s | %-10d ", hash_function(head->word), head->word, head->file_count);
        //traverse through the Tlink table
        Ltable *Thead = head->Tlink;
        while(Thead)
        {   
            printf("| %-10s | %-10d |\n", Thead->file_name, Thead->word_count);
            Thead = Thead->table_link;
            if(Thead != NULL) printf("| %-5s | %-18s | %-10s ", "", "", "");
        }
        head = head->link;
        printf("+-------+--------------------+------------+------------+------------+\n");
    }
}

            
