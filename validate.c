#include "inverted.h"
int validate_filename(char *filename);
int file_exists(char *filename);
int is_file_empty(char *filename);
int is_file_repeated(char *filename, Slist *head);
int insert_at_last(Slist **head, char *filename);
mnode *create_mainnode(char *word, char *filename);
snode *create_subnode(char *filename);
int is_database_empty(mnode *arr[]);

int read_validate(char *argv[], Slist **head)
{
    int i;
    for(i=1;argv[i]!=NULL;i++)
    {
        if(validate_filename(argv[i])==FAILURE)
        {
            printf("%s : Invalid file extension. File  isn't a .txt file\n", argv[i]);
            continue;
        }
        if(file_exists(argv[i]) == FAILURE)
        {
            printf("%s : File does not exist\n", argv[i]);
            continue;
        }
        if (is_file_empty(argv[i]) == SUCCESS)
        {
            printf("%s : File is empty\n", argv[i]);
            continue;
        }
        if (is_file_repeated(argv[i], *head) == SUCCESS)
        {
            printf("INFO: %s-This file is repeated ,so it will not be stored into database\n", argv[i]);
            continue;
        }
        printf("%s : Valid file\n", argv[i]);
        if (insert_at_last(head, argv[i]) == SUCCESS)
        {
            printf("INFO: Successful: Inserting file name %s into file linked list\n", argv[i]);
        }
        else
        {
            printf("Error: Failed to add %s\n", argv[i]);
        }
    }
    return SUCCESS;
}
int validate_filename(char *filename)
{
    if (strstr(filename, ".txt") != NULL)
    {
        return SUCCESS;
    }
    return FAILURE;
}
int file_exists(char *filename)
{
    FILE *fp=fopen(filename, "r");
    if (fp==NULL)
        return FAILURE;
    fclose(fp);
    return SUCCESS;
}
int is_file_empty(char *filename)
{
    FILE *fp=fopen(filename,"r");
    if (fp==NULL)
        return FAILURE;

    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        fclose(fp);
        return SUCCESS;   
    }
    fclose(fp);
    return FAILURE;       
}
int is_file_repeated(char *filename, Slist *head)
{
    Slist *temp = head;
    while(temp != NULL)
    {
        if(strcmp(filename, temp->filename)==0)
        {
            return SUCCESS;   
        }
        temp=temp->link;
    }
    return FAILURE;          
}
int insert_at_last(Slist **head,char *filename)
{
    Slist *new=malloc(sizeof(Slist));
    if(new==NULL)
    {
        return FAILURE;
    }
    strcpy(new->filename, filename);
    new->link=NULL;
    if(*head==NULL)
    {
        *head=new;
        return SUCCESS;
    }
    Slist *temp=*head;
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    temp->link=new;
    return SUCCESS;
}
mnode *create_mainnode(char *word, char *filename)
{
    mnode *new = malloc(sizeof(mnode));
    if (new==NULL)
    {
        return NULL;
    }
    strcpy(new->word, word);
    new->file_count=1;
    new->mlink=NULL;
    new->slink=create_subnode(filename);
    if(new->slink==NULL)
    {
        free(new);
        return NULL;
    }
    return new;
}
snode *create_subnode(char *filename)
{
    snode *new=malloc(sizeof(snode));
    if (new==NULL)
    {
        return NULL;
    }
    strcpy(new->filename, filename);
    new->word_count=1;
    new->link=NULL;
    return new;
}

int is_database_empty(mnode *arr[])
{
    int i;
    for(i = 0;i < 27;i++)
    {
        if(arr[i] != NULL)
        {
            return -1;       
        }
    }
    return 0;             
}

