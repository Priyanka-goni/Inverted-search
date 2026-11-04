#include "inverted.h"

void search_database(mnode *arr[])
{
    char word[20];
    int index;

    mnode *mtemp;
    snode *stemp;

    printf("Enter the word to search: ");
    scanf("%19s", word);
    index = tolower(word[0]) - 'a';
    if (index < 0 || index > 25)
    {
        index = 26;
    }
    mtemp = arr[index];
    while (mtemp != NULL)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("\nWord '%s' is present in %d file\n", word,mtemp->file_count);
            stemp = mtemp->slink;
            while (stemp != NULL)
            {
                printf("%s = %d\n",stemp->filename,stemp->word_count);
                stemp = stemp->link;
            }
            return;
        }
        mtemp=mtemp->mlink;
    }
    printf("\nWord '%s' is not present\n", word);
}