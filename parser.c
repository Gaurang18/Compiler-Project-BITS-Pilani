/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include <assert.h>


int stack[STACK_SIZE];
int top = -1;
int parse_table[NON_TERMINALS][TERMINALS];

//----------------------------------------------Auxiliary functions--------------------------------------------
int size_of(int *a){ 
    int i=0;
    int count = 0;
    while(a[i]!=-1){
        i++;
        count++;
    }                       //to compute size of an array, given -1 as end-marker
    return count;
}

int presentIn(int *a, int b){

    int i = 0, flag = 0;
    for(i = 0; a[i]!=0; i++){
        if(a[i]==b)
            flag = 1;
    }
    return flag;            //if b is in array a

}
int find_location(char *token){
    int j;
    for(j=0;j<TERMS;j++){
        if(strcmp(terms[j],token)==0){
            return j;
        }
    }
    return -1;
}
int epsInFirst(int alpha, int first[][11]){         //if epsilon is part of first set
    int i = 0;
    for(i=0; i < 11; i++){
        if(first[alpha][i] == EPLS)
            return 1;
    }
    return 0;
}

void findfirst(int result[150], int n, int G[][14]){  //find first set of a given non-terminal
int i, k, j = 0, l;

if(n > 51)
    result[0] = n;

else{

for(i = 0; i < 94; i++)
    if(G[i][0] == n){

        
        if (G[i][1] > 51)
            {if(!presentIn(result, G[i][1])){
                    result[j++] = G[i][1];
                }}

        else{
        for(k = 1; k < size_of(G[i]); k++){
            int flag = 0;
            int subresult[150] = {0};

            findfirst(subresult, G[i][k], G);

            for(l = 0; subresult[l]!=0; l++){
                if(subresult[l] == 109)
                    flag = 1;
                else
                if(!presentIn(result, subresult[l])){
                    result[j++] = subresult[l];
                }
                
            }
            
            if(flag!=1)
                break;



        }
            }


    }}

}

void findfollow(int result[1024], int n, int G[][14]){ //find follow set of a given non-terminal
    int i, j, k, l = 0, m;
    if(n==1){
            result[0] = -1;
            
    }
        
    for(i = 0; i< 94 ; i++){
        for(j = 1; j < size_of(G[i]); j++){

            if(G[i][j]==n){
                for(k = j+1; G[i][k]!=-1; k++){
                        int flag = 0;
                        int subresult[1024] = {0};
                        findfirst(subresult, G[i][k], G);

                        for(m=0; subresult[m]!=0; m++){
                            if(subresult[m] == 109)
                                flag = 1;
                            else
                            if(!presentIn(result, subresult[m])){
                                result[l++] = subresult[m];
                                }

                        }

                        if(flag!=1)
                            break;              
                }

                if(G[i][k]==-1 && G[i][0] != n){

                    int subresult[1024] = {0};
                    findfollow(subresult, G[i][0], G);
                    for(m=0; subresult[m]!=0; m++)
                        if(!presentIn(result, subresult[m])){
                            result[l++] = subresult[m];
                }
                }}}}}

void Initialise_table(int table[][TERMINALS]){ //initialise the parse table with -1's
    int i;
    int j;
    for(i=0;i<NON_TERMINALS;i++){
        for(j=0;j<TERMINALS;j++){
            table[i][j] = -1;
        }
    }
}


parsetree search(parsetree root, int a){       //search a node with value a in parsetree with root as its root 
    parsetree temp;

    if(root == NULL)
        return NULL;
    else if((root->value == a) && !root->isVisited){
        return root;
    }
    else if((temp=search(root->child, a))!=NULL)
        return temp;
    else if ((temp = search(root->right, a))!=NULL)
        return temp;
    else
        return NULL;
    
}

void insertLexeme(parsetree x, node *Lex){
    x->Lex = Lex;
}

void insert(parsetree x, int rule, int G[][14], node* Lex){ //to insert a node in the parsetree

    int *r = G[rule-1];
    int i = 1;
    parsetree temp, temp2, right, left;

    x->isVisited = 1;
    x->rule = rule;

    while(r[i]!=-1){
        int j;
        temp = (parsetree) malloc(sizeof (struct Parse_Tree));
        temp->Lex = createnode();
        temp->Lex->tk->line = Lex->tk->line;
        temp->generated = 0;
        //temp->Lex = (node *) malloc sizeof(node);
        //temp->Lex->tk = (tokenInfo *) malloc sizeof (tokenInfo);
        temp->value =  r[i];
        
        if(r[i] > NON_TERMINALS)
        {
            temp->isleaf = 1;
            //temp->Lex = getNextToken();
        }
        else
            {
                //temp->Lex = NULL;
                temp->isleaf = 0;
            }
        temp->left = NULL;
        temp->right = NULL;
        temp->child = NULL;
        temp->parent = x;
        //temp->Lex = Lex;
        temp->isVisited = 0;

        if(x->child==NULL)
            x->child = temp;
        else                            //if x has children already
        {
            temp2 = x->child;
            while(temp2->right!=NULL)
            {
                right = temp2->right;
                temp2 = right;

            }

            temp2->right = temp;
            temp->left = temp2;
             
        }


        i++;
    }

}

void printTree(parsetree head){             //print tree on console
    if((head==NULL)||(head->value==109)){
        //printf("head = NULL\n");
        return;
    }

    printTree(head->child);
    

    char* lexemeCurrentNode = (char*) malloc(30*sizeof(char));
    int lineno;
    char* token = (char*) malloc(30*sizeof(char));
    char* parentNodeSymbol = (char*) malloc(30*sizeof(char));
    char* valueIfNumber = (char*) malloc(30*sizeof(char));
    char* isleafNode = (char*) malloc(30*sizeof(char));
    char* NodeSymbol = (char*) malloc(30*sizeof(char));
    

    strcpy(token, terms[head->value]);
    lineno = head->Lex->tk->line;

    if(head->parent == NULL)
            strcpy(parentNodeSymbol, "ROOT");
        else{
             strcpy(parentNodeSymbol, terms[head->parent->value]);
        }


    if(head->isleaf == 0)
        strcpy(isleafNode, "no");
    else
        strcpy(isleafNode, "yes");




    if(head->value > NON_TERMINALS){
        strcpy(lexemeCurrentNode, head->Lex->tk->value);
        strcpy(NodeSymbol, "----");
        
    }
    else{
        strcpy(lexemeCurrentNode, "----");
        strcpy(NodeSymbol, terms[head->value]);
    }

    if(head->value == 107 || head->value == 108)
        strcpy(valueIfNumber, head->Lex->tk->value);
    else
        strcpy(valueIfNumber, "----");

    

    //int line = head->lexeme->line;
    //printf("copied everything... line= %d\n", line);

    printf("%-25s %-3d %-24s %-14s %-24s %-10s %-24s\n", lexemeCurrentNode, lineno, token, valueIfNumber, parentNodeSymbol, isleafNode, NodeSymbol);
    free(token);
    free(lexemeCurrentNode);
    free(parentNodeSymbol);
    free(valueIfNumber);
    free(isleafNode);
    free(NodeSymbol);

    
    printTree(head->right);
}

void push(int a){           //push functionality for stack
    stack[top+1] = a;
    top++;
}

void initialise_stack(){    //initialise stack with -1's
    int j;
    for(j=0;j<STACK_SIZE;j++){
        stack[j] = -1;
    }
}

int pop(){                  //pop functionality for stack
    int temp = stack[top];
    stack[top] = -1;
    top--;
    return temp;
}

void printstack(){          //print all elements of the stack
    int i;
    for(i=0;i<STACK_SIZE;i++){
        if(stack[i] == -1){
            break;
        }
        printf("%s ",terms[stack[i]]);
    }
    printf("\n");
}






void Print_parsing_table(int table[][TERMINALS]){ //to print the parsing table
    int i;
    int j;
    for(i=0;i<NON_TERMINALS;i++){
        for(j=0;j<TERMINALS;j++){
            if(table[i][j] == -1){
                printf("_ ");
            }else{
                printf("%d ",table[i][j]);
            }
        }
        printf("\n");
    }
}

void removePunctuation(parsetree head){

    if(head == NULL)
        return;

    parsetree child = head->child;
    parsetree right = head->right;

    switch(head->value){
        case 55:
        case 58: 
        case 62:
        case 66:
        case 67:
        case 70:
        case 71:

        case 92: 
        case 93: 
        case 94: 
        case 95: 
        case 96: 
        case 98: 
        case 99: 
        case 101: 
        case 102: 
        case 103: 
        case 104: 

        if(head->left==NULL)
        {   
            //parsetree temp = head->parent;
            head->parent->child = head->right;
            if(head->right!=NULL)
                head->right->left = NULL;
            free(head);
            
        }

        else
        {   

            head->left->right = head->right;
            if(head->right!=NULL)
                head->right->left = head->left;
            free(head);
        }

        break;

        default: break;

    }

    removePunctuation(child);
    removePunctuation(right);

    
}

parsetree pullup(parsetree head){
    if(head->left==NULL){
        head->child->right = head->right;
        if(head->right!=NULL)
            head->right->left = head->child;
        head->parent->child = head->child;
        head->child->parent = head->parent;
        parsetree temp = head->child;
        free(head);
        return temp;

    }
    else
    {
        head->left->right = head->child;
        head->child->left = head->left;
        head->child->right = head->right;
        if(head->right!=NULL)
            head->right->left = head->child;
        head->child->parent = head->parent;
        parsetree temp = head->child;
        free(head);
        return temp;
    }
    
}

parsetree modify(parsetree head){

    parsetree temp2 = head->child;

    if(head->left==NULL){
        parsetree next = head->child->right;
        head->child->right = head->right;
        if(head->right!=NULL)
            head->right->left = head->child;
        head->parent->child = head->child;
        head->child->parent = head->parent;
        
        
        if(next!=NULL){
            temp2->child = next;
            next->parent = temp2;
            next->left = NULL;
        }
        next = next->right;
        while(next!=NULL)
        {
            next->parent = temp2;
            next = next->right;
        }
        //free(head);
    }
    else
    {   
        parsetree next = head->child->right;
        head->left->right = head->child;
        head->child->left = head->left;
        head->child->right = head->right;
        if(head->right!=NULL)
            head->right->left = head->child;
        head->child->parent = head->parent;
        if(next!=NULL){
            temp2->child = next;
            next->parent = temp2;
            next->left = NULL;
        }

        next = next->right;
        while(next!=NULL)
        {
            next->parent = temp2;
            next = next->right;
        }
        //free(head);
    }

    parsetree newhead = temp2->child;
    parsetree X = temp2;
    parsetree temp = temp2->child;
/*    while(temp!=NULL && temp->value > NON_TERMINALS && temp->value != 106){
        temp = temp->right;
        //free(temp->left);
    }
    newhead->child = temp;
    newhead = temp;
    */
    temp = temp->right;
    int count = 100;
    while(temp!=NULL){
        if(temp->value <= NON_TERMINALS || temp->value == 106){
            newhead->right = temp;
            newhead->right->left = newhead; 
            newhead = newhead->right;
            temp = temp->right;
        }
        else{
            temp = temp->right;
            //free(temp->left);
        }
    }
    //assert(0);
    newhead->right = NULL;
    //assert(0);
    return X;
}




void createAst(parsetree head){

    if(head==NULL)
        return;

    switch(head->rule){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 11:
        case 13:
        case 16:
        case 25:
        case 26:
        case 45:
        case 57:
        case 59:
        case 61:
        case 64:
        case 65:
        case 70:
        case 73:
        case 74:
        case 84:
        case 86:
        case 88:
        case 90: break;

        case 18:
        case 19:
        case 20:
        case 22:
        case 23:
        case 24:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 35:
        case 36:
        case 42:
        case 43:
        case 48: 
        case 49:
        case 52:
        case 54:
        case 55:
        case 62:
        case 63:
        case 67:
        case 68:
        case 69:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 92:
        case 93:
         case 94: 
                // head = pullup(head);
                 //printf("%s", terms[head->value]);
                 break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 12:
        case 14:
        case 15:
        case 17:
        case 21:
        case 27:
        case 33:
        case 34:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 44:
        case 46:
        //case 47:
        case 50:
        case 53:
        case 58:
        case 60:
        case 66:
        case 71:
        case 72:
        case 83:
        case 85:
        case 87:
        case 89:
        case 91: //head = modify(head);
                 break;
    }
    if(head != NULL){
        createAst(head->child);
        createAst(head->right);
    }

}


void createAbstractSyntaxTree(parsetree head){
    removePunctuation(head);
    createAst(head);
}


void countNodes(parsetree head, int *count){

    if(head==NULL)
        return;
    countNodes(head->child, count);

    count[0]++;
    // printf("%d\n", count[0]);


    countNodes(head->right, count); 



}









void printToFile(parsetree head){ //used to print to file

    //fseek(fp, 0, SEEK_END);

    if((head==NULL)||(head->value==109)){
        //printf("head = NULL\n");
       // fclose(fp);
        return;
    }

     printToFile(head->child);

    

    char* lexemeCurrentNode = (char*) malloc(30*sizeof(char));
    int lineno;
    char* token = (char*) malloc(30*sizeof(char));
    char* parentNodeSymbol = (char*) malloc(30*sizeof(char));
    char* valueIfNumber = (char*) malloc(30*sizeof(char));
    char* isleafNode = (char*) malloc(30*sizeof(char));
    char* NodeSymbol = (char*) malloc(30*sizeof(char));         //the different values to be output
    

    strcpy(token, terms[head->value]);
    lineno = head->Lex->tk->line;

    if(head->parent == NULL)
            strcpy(parentNodeSymbol, "ROOT");
        else{
             strcpy(parentNodeSymbol, terms[head->parent->value]);
        }


    if(head->isleaf == 0)
        strcpy(isleafNode, "no");
    else
        strcpy(isleafNode, "yes");




    if(head->value > NON_TERMINALS){
        strcpy(lexemeCurrentNode, head->Lex->tk->value);
        strcpy(NodeSymbol, "----");
        
    }
    else{
        strcpy(lexemeCurrentNode, "----");
        strcpy(NodeSymbol, terms[head->value]);
    }

    if(head->value == 107 || head->value == 108)
        strcpy(valueIfNumber, head->Lex->tk->value);
    else
        strcpy(valueIfNumber, "----");

    int rule = head->rule;

    //to print in columns

    fprintf(stdout, "\r\n %-25s %-6d %-24s %-14s %-24s %-10s %-24s %-4d\n ", lexemeCurrentNode, lineno, token, valueIfNumber, parentNodeSymbol, isleafNode, NodeSymbol, rule);
    

    free(token);
    free(lexemeCurrentNode);
    free(parentNodeSymbol);
    free(valueIfNumber);
    free(isleafNode);
    free(NodeSymbol);

   
    printToFile(head->right);
}

//------------------------------------------------------Main functions-----------------------------------------------------------------------------------

void ComputeFirstAndFollowSets(int G[][14], int first[][11], int follow [][15]){ //Compute the first and follow Sets, given Grammar
    int i, j;
    for(i = 1; i < 52; i++){
        //printf("%d - ", i);
        int result[1024] = {0};
        findfirst(result, i, G);
        for(j = 0; result[j]!=0; j++){
             first[i][j] = result[j];

        }

        first[i][j] = -1;

    }

    for(i = 1; i < 52; i++){
        //printf("%d - ", i);
        int result[1024] = {0};
        findfollow(result, i, G);
        for(j = 0; result[j]!=0; j++){
             
             if(result[j]==-1)
                follow[i][j] = 0;
             else{
                follow[i][j] = result[j];
             }
    }

        follow[i][j] = -1;

    }



}


void parsing_table(int table[][TERMINALS],int G[][14]){ //To make parse table, from grammar and first and follow sets
    int lhead,head;
    int rule,right,termfirst;
    int alpha,foll;
    int b,term;
    int flag;
    table[0][43] = 1;
    table[25][14] = 47;
    for(rule = 0;rule < TOTAL_RULES;rule++){
        flag = 0;
        lhead = G[rule][0];
        head = lhead-1;
        for(right = 1; right < 14; right++){  
            alpha = G[rule][right];
            if(alpha == -1){
                break;
            }
            if(alpha == EPLS){
                flag =1;
                break;
            }
            if(alpha > NON_TERMINALS){
                table[head][alpha - NON_TERMINALS] = rule+1;
                break;
            }
            for(termfirst = 0; termfirst < size_of(first[alpha-1]); termfirst++){

                term = first[alpha-1][termfirst];
                if (term != 109 && term > NON_TERMINALS){
                    table[head][term - NON_TERMINALS] = rule+1;
                }
            }
            if(!epsInFirst(alpha, first))
                break;
            else if(epsInFirst(alpha, first) && G[rule][right+1] == -1){
                flag = 1;
                break;
            }else{

            }
        }

        if(flag == 1){
            for(foll = 0; foll < size_of(follow[head]); foll++){
                    b = follow[head][foll];
                    if(b==-1){
                        break;
                    }
                    if(b==0){
                        table[head][b] = rule+1;
                    }
                    else{
                        table[head][b-NON_TERMINALS] = rule+1;
                    }
                }
        }
    }   
}
char arra[1000][40] = {"0"};
// int lineno[1000] = {0};
int popl =0;

void addLexeme(parsetree head, node* Lex){

    if(head==NULL){
        return;
    }
    else{
    addLexeme(head->child, Lex);

    /*if(head->value > NON_TERMINALS && head->value!=109){
        if(strcmp(Lex->tk->token,"COMMENTMARK")==0){
            Lex = getNextToken();
        }
        if(strcmp(Lex->tk->value,"declare")==0 && head->value!=59){
            Lex = getNextToken();
        }
        head->Lex = Lex;
        printf("%s\n", terms[head->value]);
        Lex = getNextToken();
    }*/
    if(head->isleaf == 1 && head->value!=109 ){
        
        // head->Lex->tk->line = lineno[pop1];
        strcpy(head->Lex->tk->value,arra[popl++]);
         
        //printf("%s     -     %s\n",terms[head->value],head->Lex->tk->value);
    }
    addLexeme(head->right, Lex);
    }
}



void populateLexemes(parsetree head, char *filename){



    /*FILE* fp = fopen("testcase5.txt","r");
    rewind(fp);
    fseek( fp, 0, SEEK_SET);
    fp = getstream(fp);*/
 
           node* Lex = getNextToken();                  //Call method in lexer
                    int i = 1;
                    int j = 0;
                    while(strcmp(Lex->tk->value,"$")!=0){

                         //if(strcmp(Lex->tk->value, "**")!=0)
                         // lineno[j] = Lex->tk->value;
                         strcpy(arra[j++],Lex->tk->value);

                         //printf("%s \n", arra[j-1]);
                //printf("%d. token = %s, value = %s, line = %d\n", i++,Lex->tk->token, Lex->tk->value, Lex->tk->line);   //print tokens to console
                        free(Lex);
                        node* Lex = getNextToken();
                    }               //Call method in lexer
    addLexeme(head, Lex);
}




parsetree parse_Source_Code(char *filename){   //to Parse Source Code

    parsetree head;

    head = (parsetree) malloc (sizeof(struct Parse_Tree));
    head->Lex = createnode();
    strcpy(head->Lex->tk->token, "PROGRAM");
    strcpy(head->Lex->tk->value, "program");
    head->Lex->tk->line = 1;
    head->value = 1;
    head->child = NULL;
    head->left = NULL;
    head->right = NULL;
    head->isleaf = 0;
    head->isVisited = 0;
    head->parent = NULL;


    FILE* fp = fopen(filename,"r");
    //char B[4096];
    //int bufflen =4096;
    rewind(fp);
    fseek( fp, 0, SEEK_SET);
    fp = getstream(fp);
    push(0);
    push(1);
     
    node* Lex = getNextToken();
    //assert(0);
    int po=0;
    int count = 0;
    printf("token = %s, value = %s, line = %d\n", Lex->tk->token, Lex->tk->value, Lex->tk->line);
    while(strcmp(Lex->tk->value,"$")!=0){
        char *token = Lex->tk->token;
        printf("Parsing Token -> %s\n",token);
        if(strcmp(token,"COMMENTMARK") == 0){
            Lex = getNextToken();
            token = Lex->tk->token;
            if(stack[top] == 0 || stack[top] == 3){
                break;
            }
        }
        if(stack[top] > NON_TERMINALS){
            if(stack[top] == (find_location(token))){
                
                pop();
                count++;
                Lex = getNextToken();
                token = Lex->tk->token;
                printstack();
            }else{
                printf("\nERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is %s\n",Lex->tk->token,Lex->tk->value,Lex->tk->line,terms[stack[top]]); //Terminal is not a match
                exit(0);
            }
        }else{
            int rule = parse_table[stack[top] - 1][(find_location(token)-NON_TERMINALS)];
            
            if(rule == -1){
                printf("\nERROR_5: The token %s for lexeme %s does not match at line %d. The expected token here is %s\n",Lex->tk->token,Lex->tk->value,Lex->tk->line,terms[stack[top]]); //Rule not found
                //exit(0);
                Lex = getNextToken();
                token = Lex->tk->token;
                while((rule = parse_table[stack[top] - 1][(find_location(token)-NON_TERMINALS)]) == -1){
                    Lex = getNextToken();
                    token = Lex->tk->token;
                }
            }else{
                if(head->child==NULL)
                    insert (head, rule, G, Lex);    //populate parse tree 
                else{
                  parsetree tmp = search(head, stack[top]);
                  insert(tmp, rule, G, Lex);
                }
                int right;
                pop();  
                for(right = size_of(G[rule-1])-1; right > 0; right--){
                    int alpha = G[rule-1][right];
                       
                    if(alpha != EPLS)               
                        push(alpha);
                }
                printstack();
            }
        }
    }
    count++;
    if(stack[top] == 3){
            pop();
    }
    //printstack();
    if(stack[top] == 0){                //Stack is empty - Successful Parsing
        pop();
        printf("\nSUCCESFUL PARSING.... THANK YOU\n");
    }
    printf("Count %d\n",count);

    //populateLexemes(head, filename);

    return head;
}



void printParseTree(parsetree head){ //Print Parse tree to file, name of file is "outfile"

    printf("\r\n %-25s %-6s %-24s %-10s %-24s %-3s %-24s %-4s\n ", "lexemeCurrentNode", "lineno", "token", "valueIfNumber", "parentNodeSymbol", "isleafNode", "NodeSymbol", "rule");
    
    // createAbstractSyntaxTree(head);
    printToFile(head);
    //fclose(fp);

}
