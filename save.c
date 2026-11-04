#include "inverted.h"

int save_database(mnode *arr[])
{
    char filename[50];

    printf("Enter the file name to save database: ");
    scanf("%49s", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error: Unable to open file\n");
        return FAILURE;
    }
    int i;
    mnode *mtemp;
    snode *stemp;
    for (i = 0; i < 27; i++)
    {
        mtemp = arr[i];

        while (mtemp != NULL)
        {
            fprintf(fp, "#%d;%s;%d",i,mtemp->word,mtemp->file_count);
            stemp = mtemp->slink;
            while (stemp != NULL)
            {
                fprintf(fp, ";%s;%d",stemp->filename,stemp->word_count);
                stemp = stemp->link;
            }
            fprintf(fp, "#\n");
            mtemp = mtemp->mlink;
        }
    }
    fclose(fp);
    printf("Database saved successfully in %s\n", filename);
    return SUCCESS;
}