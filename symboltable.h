#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 20
#define HASHSIZE 20
#define A assert(0);

struct funcNode{
   char name[30];
   char input[100];
   char output[100];
   struct funcNode* next;
};

typedef struct funcNode fnode;
typedef struct funcNode *fnext;

struct func_hash_table
{
    fnode* table[SIZE];
};

struct tokNode{
   char name[30];
   char ifnumvalue[10];
   char scope[15];
   char type[15];
   int offset;
   int width;
   struct tokNode* next;
};

typedef struct tokNode pNode;
typedef struct tokNode *pNext;

struct hash_of_hash_tables{
    struct hash_table *functable[HASHSIZE];
};

struct hash_table
{
    pNode *table[SIZE];
};

struct hash_table* create_table(){
        struct hash_table *node = (struct hash_table *)malloc(sizeof(struct hash_table));
        return node;
}

struct tokNode* create_node(char* key,char* type,char* functionname,char* ifnumvalue){
   struct tokNode *node = (struct tokNode *)malloc(sizeof(struct tokNode));
   strcpy(node->name,key);
   strcpy(node->ifnumvalue,ifnumvalue);
   strcpy(node->scope,functionname);
   strcpy(node->type,type);
   node->offset = 0;
   node->width = 0;
   node->next = NULL;
   return node;
}

struct funcNode* create_func_node(char *lexeme,char *input_parameters,char *output_parameters){
   struct funcNode *node = (struct funcNode *)malloc(sizeof(struct funcNode));
   strcpy(node->name,lexeme);
   strcpy(node->input,input_parameters);
   strcpy(node->output,output_parameters);
   return node;
}

int hash(char *key)
{
    int value = 0;
    int i;
    for (i = 0; i < strlen(key); i++)
         value += (int)key[i];
    return (value % SIZE);
}
