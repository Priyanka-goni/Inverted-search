#include "inverted.h"

int validate_backup_file(char *filename)
{
    FILE *fp;
    char line[500];
    fp=fopen(filename, "r");
    if(fp==NULL)
    {
        return FAILURE;
    }
    while(fgets(line, sizeof(line),fp)!=NULL)
    {
        int len;
        line[strcspn(line,"\n")]='\0';
        len=strlen(line);
        if(len<2)
        {
            fclose(fp);
            return FAILURE;
        }
        if(line[0]!='#' || line[len - 1]!='#')
        {
            fclose(fp);
            return FAILURE;
        }
    }
    fclose(fp);
    return SUCCESS;
}
int update_database(mnode *arr[])
{
    char filename[50];
    FILE *fp;
    char line[500];
    if(is_database_empty(arr)==FAILURE)
    {
        printf("INFO: Database is already created, so update is not possible\n");
        return FAILURE;
    }
    printf("Enter the backup file name: ");
    scanf(" %49s", filename);
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("INFO: Backup file does not exist\n");
        return FAILURE;
    }
    fclose(fp);
    if(validate_backup_file(filename)==FAILURE)
    {
        printf("INFO: Given file is not a valid backup file\n");
        return FAILURE;
    }
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("ERROR: Unable to open backup file\n");
        return FAILURE;
    }
    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        char *token;
        int index;
        int file_count;
        mnode *mnew;
        mnode *mtemp;
        mnode *mprev;
        line[strcspn(line, "\n")] = '\0';
        token = strtok(line, ";");
        if (token == NULL)
        {
            continue;
        }
        index = atoi(token + 1);
        if (index < 0 || index > 26)
        {
            fclose(fp);
            return FAILURE;
        }
        token = strtok(NULL, ";");
        if (token == NULL)
        {
            fclose(fp);
            return FAILURE;
        }
        mnew = malloc(sizeof(mnode));
        if (mnew == NULL)
        {
            fclose(fp);
            return FAILURE;
        }
        strcpy(mnew->word, token);
        token = strtok(NULL, ";");
        if (token == NULL)
        {
            free(mnew);
            fclose(fp);
            return FAILURE;
        }
        file_count = atoi(token);
        mnew->file_count = file_count;
        mnew->mlink = NULL;
        mnew->slink = NULL;
        snode *slast = NULL;
        int i;
        for (i = 0; i < file_count; i++)
        {
            char *filename_token;
            char *count_token;
            snode *snew;
            filename_token = strtok(NULL, ";");
            if (filename_token == NULL)
            {
                free(mnew);
                fclose(fp);
                return FAILURE;
            }
            snew = malloc(sizeof(snode));
            if (snew == NULL)
            {
                free(mnew);
                fclose(fp);
                return FAILURE;
            }
            strcpy(snew->filename, filename_token);
            count_token = strtok(NULL, ";");
            if (count_token == NULL)
            {
                free(snew);
                free(mnew);
                fclose(fp);
                return FAILURE;
            }
            snew->word_count = atoi(count_token);
            snew->link = NULL;
            if (mnew->slink == NULL)
            {
                mnew->slink = snew;
            }
            else
            {
                slast->link = snew;
            }
            slast = snew;
        }
        if (arr[index] == NULL)
        {
            arr[index] = mnew;
        }
        else
        {
            mtemp = arr[index];
            mprev = NULL;
            while (mtemp != NULL)
            {
                mprev = mtemp;
                mtemp = mtemp->mlink;
            }
            mprev->mlink = mnew;
        }
    }
    fclose(fp);
    printf("INFO: Database updated successfully\n");
    return SUCCESS;
}
