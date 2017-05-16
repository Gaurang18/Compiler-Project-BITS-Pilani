/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/
#include "functionsymboltable.h"

int offseter = 0;
int sequencenumber = 1;
int offset = 0;
int hashinsert(char* key,char* type,char* functionname,char* ifnumvalue)
{
    int j = get_func_hash_value(functionname);
    int h = hash(key);
    struct tokNode* it = create_node(key,type,functionname,ifnumvalue);
    if (it == NULL){
        return 0;
    }
    while(ht->functable[j]->table[h]->next != NULL){
        h++;
    }
    ht->functable[j]->table[h]->next = it;
    int width =0;
       if(strcmp(ht->functable[j]->table[h]->next->type,"INTEGER") ==0){
        width = 2;
       }
       if(strcmp(ht->functable[j]->table[h]->next->type,"REAL") ==0){
        width = 4;
       }
       if(strcmp(ht->functable[j]->table[h]->next->type,"STRING") ==0){
        width = strlen(ht->functable[j]->table[h]->next->name);
       }
       if(strcmp(ht->functable[j]->table[h]->next->type,"BOOLEAN") ==0){
           width = 1;
       }
       if(strncmp(ht->functable[j]->table[h]->next->type,"ARRAY",5) ==0){
        char type[50];
        memset(type, '\0', sizeof(type));
        strcpy(type, ht->functable[j]->table[h]->next->type);
        int range = 0;
        
                char *token = NULL;
                    token = strtok(type, "(");
                    if(token!=NULL){
                        token = strtok(NULL, ",");

                        if(strcmp(token, "INTEGER")==0)
                            width = 2;
                        if(strcmp(token, "REAL")==0)
                            width = 4;
                        if(strcmp(token, "BOOLEAN")==0)
                            width = 1;


                        token = strtok(NULL, ")");
                        if(token!=NULL){
                            range = atoi(token);

                        }}

                
                // assert(0);

        width = width*range;
       }
        ht->functable[j]->table[h]->next->width = width;
        
        ht->functable[j]->table[h]->next->offset = offset; 
        offset += width;
    return 1;
}


void display(char* functionname){
    int i;
    int j = get_func_hash_value(functionname);
      
    for(i=0;i<SIZE;i++){
        pNode* it  = ht->functable[j]->table[i]->next;

        if(it !=NULL && strcmp(it->name,"")!= 0){

            if(strncmp(ht->functable[j]->table[i]->next->type,"ARRAY",5)==0)
                printf("%-3d %-20s %-22s %-20s %-5d %-6d\n",(sequencenumber++),ht->functable[j]->table[i]->next->name,"ARRAY",ht->functable[j]->table[i]->next->scope,ht->functable[j]->table[i]->next->width,offseter);
           
            else
                printf("%-3d %-20s %-22s %-20s %-5d %-6d\n",(sequencenumber++),ht->functable[j]->table[i]->next->name,ht->functable[j]->table[i]->next->type,ht->functable[j]->table[i]->next->scope,ht->functable[j]->table[i]->next->width,offseter);
            offseter += ht->functable[j]->table[i]->next->width;
            //printf("%d.\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n",(sequencenumber++),ht->functable[j]->table[i]->next->name,ht->functable[j]->table[i]->next->type,ht->functable[j]->table[i]->next->ifnumvalue,ht->functable[j]->table[i]->next->scope,ht->functable[j]->table[i]->next->offset); 
        }
    }
}
void displaySymbolTable(){
    int i;
    printf("\t\t\t\t Symbol Table\n");
    printf("%-3s %-20s %-22s %-20s %5s %6s\n","No.","Identifier name","Type", "Module Scope","Width","Offset");
      
    for(i=0; i<funcnum; i++)
        display(arr[i]);

    //assert(0);


}


// int hashinsert(char* key,char* type,char* functionname,char* ifnumvalue)
// {
//     int j = get_func_hash_value(functionname);
//     int h = hash(key);
//     struct tokNode* it = create_node(key,type,functionname,ifnumvalue);
//     if (it == NULL){
//         return 0;
//     }
//     while(ht->functable[j]->table[h]->next != NULL){
//         h++;
//     }
//     ht->functable[j]->table[h]->next = it;
//     return 1;
// }

int checksymbolpresent(char* key,char* functionname){
    int j = get_func_hash_value(functionname);
    int h = hash(key);
    if(ht->functable[j]->table[h]==NULL){
        return 0;
    }
    while(ht->functable[j]->table[h]->next != NULL){
        if(strcmp(key,ht->functable[j]->table[h]->next->name) == 0){
            return 1;
        }
        h++;
    }
    return 0;
}

int getoffset(char* key,char* functionname){
    int j = get_func_hash_value(functionname);
    int h = hash(key);
    while(ht->functable[j]->table[h]->next != NULL){
        if(strcmp(key,ht->functable[j]->table[h]->next->name) == 0){
            return ht->functable[j]->table[h]->next->offset;
        }
        h++;
    }
    return -1;
}


char* gettype(char* key,char* functionname){
    int j = get_func_hash_value(functionname);
    int h = hash(key);
    while(ht->functable[j]->table[h]->next != NULL){
        if(strcmp(key,ht->functable[j]->table[h]->next->name) == 0){
            return ht->functable[j]->table[h]->next->type;
        }
        h++;
    }
    return NULL;
}



void automateoffset(char* functionname){
    int i;
    int j = get_func_hash_value(functionname);
    int offset = 0;
    for(i=0;i<SIZE;i++){
        pNode* it  = ht->functable[j]->table[i]->next;
        if(it !=NULL && strcmp(it->name,"")!= 0){
            if(strcmp(ht->functable[j]->table[i]->next->type,"INTEGER") ==0){
            	offset += 4;
            }
            if(strcmp(ht->functable[j]->table[i]->next->type,"REAL") ==0){
            	offset += 8;
            }
            if(strcmp(ht->functable[j]->table[i]->next->type,"STRING") ==0){
            	offset += strlen(ht->functable[j]->table[i]->next->name);
            }
            if(strcmp(ht->functable[j]->table[i]->next->type,"ARRAY") ==0){
            	offset += 0;
            }
         	ht->functable[j]->table[i]->next->offset = offset;   
        }
    }
}

pNode* getdirectpointer(char* key,char* functionname){
	int j = get_func_hash_value(functionname);
    int h = hash(key);
    while(ht->functable[j]->table[h]->next != NULL){
        if(strcmp(key,ht->functable[j]->table[h]->next->name) == 0){
            return ht->functable[j]->table[h]->next;
        }
        h++;
    }
    return NULL;
}
