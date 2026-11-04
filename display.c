#include "inverted.h"

void display_database(mnode *arr[])
{
    int i;
    mnode *mtemp;
    snode *stemp;
    printf("Index\tWord\tFile_count\tFile_name\tWord_count\n");
    for(i=0;i<27;i++)
    {
        mtemp = arr[i];
        while (mtemp != NULL)
        {
            printf("%d\t%s\t%d\t\t",i,mtemp->word,mtemp->file_count);
            stemp = mtemp->slink;
            while (stemp != NULL)
            {
                printf("%s\t\t%d\n",stemp->filename,stemp->word_count);
                if (stemp->link != NULL)
                {
                    printf("\t\t\t\t");
                }
                stemp = stemp->link;
            }
            mtemp = mtemp->mlink;
        }
    }
}
