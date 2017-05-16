/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexerDef.h"

node* createnode();
header initialise_head();
void flush(char* str);
char* Keyword_checker(char val[]);
int remove_extralines(char *B,int forward);
int remove_comments(char *B,int forward);
FILE* getstream(FILE *fp);
FILE* reloadBuff();
void removeComments(char *testcaseFile);
node* getNextToken();