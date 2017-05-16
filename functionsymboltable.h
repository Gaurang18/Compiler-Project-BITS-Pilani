/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/
#include "symboltable.h"

struct hash_of_hash_tables *ht;
struct func_hash_table *functable;

int count, funcnum = 0;
char arr[100][100];



int hash_insert_func(char *key,char* input_parameters,char* output_parameters)
{
    int h = hash(key);
    struct funcNode* it = create_func_node(key,input_parameters,output_parameters);
    if (it == NULL){
        return 0;
    }
    while(functable->table[h]->next != NULL){
        h++;
    }
    functable->table[h]->next = it;
    strcpy(arr[funcnum++], key);
    return h;
}




int get_func_hash_value(char* functionname){
    int h = hash(functionname);
    while(functable->table[h]->next != NULL){
        if(strcmp(functable->table[h]->next->name,functionname) == 0){
            return h;
        }
        h++;
    }
    return -1;
}

void func_display(){
    int i;
    fnode* it;
    int j=1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            it = functable->table[i]->next;
            //printf("%d. I am    %s    module\n",j++,functable->table[i]->next->name);
        }
    }
}

void get_Func_input_type(char* functionname){
    int i;
    fnode* it;
    char inputtype[1000] = {'\0'};
    int j=1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(inputtype, functable->table[i]->next->input);
                printf("I am    %s    module and input parameters are..\n",functable->table[i]->next->name);
                    char *token;
                    token = strtok(functable->table[i]->next->input, ";");
                    while( token != NULL ) {
                       printf( "%d. %s\n", j++,token );
                       token = strtok(NULL, ";");
                    }
                // return functable->table[i]->next->input;
            }
        }
        // return "";
    }
    // return inputtype;
}

void get_Func_output_type(char* functionname){
    int i;
    fnode* it;
    int j=1;
    char outputtype[1000] = {'\0'};
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(outputtype, functable->table[i]->next->output);
                printf("I am    %s    module and output parameters are..\n",functable->table[i]->next->name);
                    char *token;
                    token = strtok(functable->table[i]->next->output, ";");
                    while( token != NULL ) {
                       printf( "%d. %s\n", j++,token );
                       token = strtok(NULL, ";");
                    }
                    // return functable->table[i]->next->output;
            }
        }
    }

    // return "";
    // return outputtype;
}

char* get_Function_input_type(char* functionname){
    int i;
    fnode* it;
    char inputtype[1000] = {'\0'};
    int j=1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(inputtype, functable->table[i]->next->input);
                
                // return functable->table[i]->next->input;
            }
        }
        // return "";
    }
    return inputtype;
}

char* get_Function_output_type(char* functionname){
    int i;
    fnode* it;
    int j=1;
    char outputtype[1000] = {'\0'};
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(outputtype, functable->table[i]->next->output);
                
                    // return functable->table[i]->next->output;
            }
        }
    }

    // return "";
    return outputtype;
}

int check_func_present(char* functionname){
    int i;
    fnode* it;
    int j=1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
               return 1;
            }
        }
    }
    return 0;
}

fnode* directfunctionpointer(char* functionname){
    int i;
    fnode* it;
    int j=1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
               return functable->table[i]->next;
            }
        }
    }
    return NULL;
}