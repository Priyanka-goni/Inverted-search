#include "inverted.h"

int main(int argc, char *argv[])
{
    Slist *head=NULL;
    mnode *arr[27]={NULL};
    int choice;
    int create=0;
    int update=0;
    if (argc==1)
    {
        printf("INFO: Insufficient argument\nPlease pass argument like a.out <file.txt>\n");
        return FAILURE;
    }
    if(read_validate(argv,&head)==FAILURE)
    {
        printf("ERROR: File validation failed\n");
        return FAILURE;
    }
    while (1)
    {
        printf("\n1. Create database\n2. Display\n3. Search\n4. Save\n5. Update\n6. Exit\nEnter choice:");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                if (create==1)
                {
                    printf("INFO: Database already created\n");
                    break;
                }
                if (update==1)
                {
                    printf("INFO: Database already updated, so create is not possible\n");
                    break;
                }
                if (head==NULL)
                {
                    printf("INFO: No valid files available\n");
                    break;
                }
                if(create_database(head, arr) == SUCCESS)
                {
                    printf("INFO: Database created successfully\n");
                    create=1;
                }
                else
                {
                    printf("INFO: Database creation failed\n");
                }
                break;
            case 2:
                if (is_database_empty(arr) == SUCCESS)
                {
                    printf("INFO: Database is empty\n");
                    break;
                }
                display_database(arr);
                break;
            case 3:
                if (is_database_empty(arr) == SUCCESS)
                {
                    printf("INFO: Database is empty\n");
                    break;
                }
                search_database(arr);
                break;
            case 4:
                if (is_database_empty(arr) == SUCCESS)
                {
                    printf("INFO: Database is empty\n");
                    break;
                }
                if (save_database(arr) == SUCCESS)
                {
                    printf("INFO: Save successful\n");
                }
                else
                {
                    printf("INFO: Save failed\n");
                }
                break;
            case 5:
                if (update==1)
                {
                    printf("INFO: Database already updated, so update is not possible\n");
                    break;
                }
                if (update_database(arr) == SUCCESS)
                {
                    update=1;
                }
                break;
            case 6:
                printf("INFO: Exiting....!\n");
                return SUCCESS;
            default:
                printf("INFO: Invalid choice\n");
                break;
        }
    }
    return SUCCESS;
}