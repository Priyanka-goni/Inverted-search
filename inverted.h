#ifndef INVERTED_H
#define INVERTED_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct mainnode
{
    char word[20];
    int file_count;
    struct mainnode *mlink;
    struct subnode *slink;
}mnode;

typedef struct subnode{
    int word_count;
    char filename[20];
    struct subnode *link;
}snode;

typedef struct node
{
    int data;
    char filename[20];
    struct node *link;
}Slist;

int read_validate(char *argv[], Slist **head);
int validate_filename(char *filename);
int file_exists(char *filename);
int is_file_empty(char *filename);
int is_file_repeated(char *filename, Slist *head);
int insert_at_last(Slist **head, char *filename);

int create_database(Slist *head, mnode *arr[]);
mnode *create_mainnode(char *word, char *filename);
snode *create_subnode(char *filename);

void display_database(mnode *arr[]);
void search_database(mnode *arr[]);
int save_database(mnode *arr[]);
int update_database(mnode *arr[]);
int is_database_empty(mnode *arr[]);
#endif