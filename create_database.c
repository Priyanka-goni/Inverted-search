#include "inverted.h"
int create_database(Slist *head, mnode *arr[])
{
    Slist *temp = head;
    while (temp != NULL)
    {
        FILE *fp = fopen(temp->filename, "r");
        if (fp == NULL)
        {
            printf("Unable to open %s\n", temp->filename);
            return FAILURE;
        }
        char word[20];
        while (fscanf(fp, "%19s", word) != EOF)
        {
            int index;
            index = tolower(word[0]) - 'a';
            if (index < 0 || index > 25)
            {
                index = 26;
            }
            if (arr[index] == NULL)
            {
                mnode *mnew = create_mainnode(word,temp->filename);
                if (mnew == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }
                arr[index] = mnew;
            }
            else
            {
                mnode *mtemp = arr[index];
                mnode *mprev = NULL;
                while (mtemp != NULL)
                {
                    if (strcmp(mtemp->word, word) == 0)
                    {
                        break;
                    }
                    mprev = mtemp;
                    mtemp = mtemp->mlink;
                }
                if(mtemp == NULL)
                {
                    mnode *mnew = create_mainnode(word,temp->filename);
                    if (mnew == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }
                    mprev->mlink = mnew;
                }
                else
                {
                    snode *stemp = mtemp->slink;
                    snode *sprev = NULL;
                    while (stemp != NULL)
                    {
                        if (strcmp(stemp->filename,temp->filename) == 0)
                        {
                            break;
                        }
                        sprev = stemp;
                        stemp = stemp->link;
                    }
                    if (stemp != NULL)
                    {
                        stemp->word_count++;
                    }
                    else
                    {
                        snode *snew =create_subnode(temp->filename);
                        if (snew == NULL)
                        {
                            fclose(fp);
                            return FAILURE;
                        }
                        sprev->link = snew;
                        mtemp->file_count++;
                    }
                }
            }
        }
        fclose(fp);
        temp = temp->link;
    }
    return SUCCESS;
}