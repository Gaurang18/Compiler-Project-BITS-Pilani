/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserDef.h"

int size_of(int *a);
int presentIn(int *a, int b);
int epsInFirst(int alpha, int first[][11]);
void findfirst(int result[150], int n, int G[][14]);
void findfollow(int result[1024], int n, int G[][14]);
void ComputeFirstAndFollowSets(int G[][14], int first[][11], int follow [][15]);
parsetree search(parsetree root, int a);
void insert(parsetree x, int rule, int G[][14], node* Lex);
void printTree(parsetree head);
void push(int a);
void initialise_stack();
int pop();
void printstack();
int find_location(char *token);
void Initialise_table(int table[][TERMINALS]);
void Print_parsing_table(int table[][TERMINALS]);
void f();
void printToFile(parsetree head);
void parsing_table(int table[][TERMINALS],int G[][14]);
parsetree parse_Source_Code();
void printParseTree(parsetree head);
