/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/

#include "tokensymboltable.h"
#include "TypeChecker.c"


void createsymboltable(){
        functable = (struct func_hash_table*)malloc(sizeof(struct func_hash_table*));
        int i;
        char *t = "";
        char *inp = "";
        char *output = "";
        for (i = 0;i < SIZE;i++) {
            functable->table[i] = create_func_node(t,inp,output);
        }
        ht = (struct hash_of_hash_tables*)malloc(sizeof(struct hash_of_hash_tables));
        int j;
        for (j = 0 ; j < HASHSIZE ; j++) {
                ht->functable[j] = create_table();
                for ( i = 0 ; i < SIZE ; ++i ) {
                    char *key = "";
                    char* functionname = "";
                    char* type = "";
                    char* ifnumvalue = "";
                    ht->functable[j]->table[i] = create_node(key,type,functionname,ifnumvalue);
                }
        }
}

// void symboltabledisplay(){
//     int i;
//     for(i=0;i<counter;i++){
//         display
//     }
// }

// int main(){
//     createsymboltable();
//     hash_insert_func("global","INT,INT","INT");
//     // hash_insert_func("global1aa","INT,INT","INT");
//     // hash_insert_func("global2","INT,INT","INT");
//     // hash_insert_func("globalsa","INT,INT","INT");
//     // hashinsert("abralbjvds","STRING","global","___");
//     // hashinsert("217","INT","global","___");
//     // hashinsert("thak","STRING","global","___");
//     display("global");
//     func_display();
//     get_Func_input_type("global");
//     get_Func_output_type("global");
//     automateoffset("global");
//     printf("value of offset of thak :%d ",getoffset("thak","global"));
//     display("global");
// }

// char[20] scope;

void populateFunctionDefinitions(FILE *fp, parsetree head, char* functionname){

    if(head==NULL)
        return;

    populateFunctionDefinitions(fp, head->child, functionname);

    


    if((strcmp(head->Lex->tk->value, functionname)==0) && head->parent->value == 7){
        parsetree iplist = head->right;
        char inputtype[1000] = {'\0'};
        char outputtype[1000] = {'\0'};
        switch(iplist->child->right->rule){
            {
                case 18: strcat(inputtype, "INTEGER");
                    break;
                case 19:strcat(inputtype, "REAL");
                    break;
                case 20:strcat(inputtype, "BOOLEAN");
                    break;
                case 21: 
                    //int range = head->parent->right->child->right->child->right->right->Lex->tk->value - head->parent->right->child->right->child->Lex->tk->value;
                    //char value[3]; 
                    //value[0] = range;
                    //value[1] = '\0';
                    {parsetree range = iplist->child->right->child->right;

                   int r1 = atoi(range->child->Lex->tk->value);
                    int r2 = atoi(range->child->right->right->Lex->tk->value);
                    int r = r2 -r1 + 1;
                    char size[3];
                    //sprintf(size,"%d",r);

                    // printf("range %d\n", r);

                    char type[100] = {'\0'};



                    switch(range->right->rule){
                        case 22: strcat(inputtype, "ARRAY(INTEGER, ");
                                 strcat(inputtype, size);
                                 strcat(inputtype, ")");
                                 
                                break;
                        case 23:strcat(inputtype, "ARRAY(REAL, ");
                                 strcat(inputtype, size);
                                 strcat(inputtype, ")");
                                 
                                break;
                        case 24:strcat(inputtype, "ARRAY(BOOLEAN, ");
                                 strcat(inputtype, size);
                                 strcat(inputtype, ")");
                                 
                                break;
                    }}
                    break;
            }
        }

       parsetree iplistprime = iplist->child->right->right;

        while(iplistprime->rule!=11){

            switch(iplistprime->child->right->rule){
            {
                case 18: strcat(inputtype, "; INTEGER");
                    break;
                case 19:strcat(inputtype, "; REAL");
                    break;
                case 20:strcat(inputtype, "; BOOLEAN");
                    break;
                case 21: 
                    //int range = head->parent->right->child->right->child->right->right->Lex->tk->value - head->parent->right->child->right->child->Lex->tk->value;
                    //char value[3]; 
                    //value[0] = range;
                    //value[1] = '\0';
                    {parsetree range = iplistprime->child->right->child->right;

                   int r1 = atoi(range->child->Lex->tk->value);
                    int r2 = atoi(range->child->right->right->Lex->tk->value);
                    int r = r2 -r1 + 1;
                    char size[3];
                    //sprintf(size,"%d",r);

                    // printf("range %d\n", r);

                    char type[100] = {'\0'};



                    switch(range->right->rule){
                        case 22: strcat(inputtype, "; ARRAY(INTEGER, ");
                                 strcat(inputtype, size);
                                 strcat(inputtype, ")");
                                 
                                break;
                        case 23:strcat(inputtype, "; ARRAY(REAL, ");
                                 strcat(inputtype, size);
                                 strcat(inputtype, ")");
                                 
                                break;
                        case 24:strcat(inputtype, "; ARRAY(BOOLEAN, ");
                                 strcat(inputtype, size);
                                 strcat(inputtype, ")");
                                 
                                break;
                    }}
                    break;
            }
        }

        iplistprime = iplistprime->child->right->right;

        }

        if(head->right->right->rule != 13){
            parsetree oplist = head->right->right->child->right;

            switch(oplist->child->right->rule)
            {
                
                        case 22: strcat(outputtype, "INTEGER");
                        break;
                        case 23:strcat(outputtype, "REAL");
                        break;
                        case 24:strcat(outputtype, "BOOLEAN");
                        break;
            }

        parsetree oplistprime = oplist->child->right->right;

        while(oplistprime->rule!=16){

            switch(oplistprime->child->right->rule)
            {           case 22: strcat(outputtype, "; INTEGER");
                        break;
                        case 23:strcat(outputtype, "; REAL");
                        break;
                        case 24:strcat(outputtype, "; BOOLEAN");
                        break;
                    }
                    

        oplistprime = oplistprime->child->right->right;

        }
    }

    hash_insert_func(head->Lex->tk->value,inputtype, outputtype);
    return;
}

 populateFunctionDefinitions(fp, head->right, functionname);

}
void populateSymbolTable(FILE *fp, parsetree head, char *scope){

    if(head==NULL)
        return;

    if(head->value==4){
         hash_insert_func("driver","", "");
         strcpy(scope, "driver");
         // assert(0);
        }

    populateSymbolTable(fp, head->child, scope);

    

    if(head->value==106){

        if(head->parent->value==5)
        {
            
            if(check_func_present(head->Lex->tk->value))
                fprintf(fp,"ERROR 1: Function %s already Defined, Erroneous declaration, line number %d", head->Lex->tk->value,head->Lex->tk->line);
            else{

                parsetree root = head;
                while(root->value!=1)
                    root = root->parent;


                
                populateFunctionDefinitions(fp, root, head->Lex->tk->value);
                //if(check_func_present(head->Lex->tk->value))
                    //printf("Yay\n");
            }
        }

        if(head->parent->value == 7)
        {
            if(!check_func_present(head->Lex->tk->value))
                populateFunctionDefinitions(fp, head, head->Lex->tk->value);
        }



        //Changes scope
        if(head->parent->value==7)
        {
            strcpy(scope, head->Lex->tk->value);
        }

        //Declare Statements

        if(head->parent->value == 33 && head->parent->parent->value==20)
        {   
            if(checksymbolpresent(head->Lex->tk->value, scope))
                fprintf(fp,"ERROR 9: Redeclaration of variable %s in the same scope, line number %d\n", head->Lex->tk->value, head->Lex->tk->line);
            
            
            switch(head->parent->right->rule)
            {
                case 18: hashinsert(head->Lex->tk->value,"INTEGER",scope,"___");
                    break;
                case 19:hashinsert(head->Lex->tk->value,"REAL",scope,"___");
                    break;
                case 20:hashinsert(head->Lex->tk->value,"BOOLEAN",scope,"___");
                    break;
                case 21: 

                    // int range = atoi(head->parent->right->child->right->child->right->right->Lex->tk->value) - atoi(head->parent->right->child->right->child->Lex->tk->value);
                    // char value[3] = {"0"};
                    // value[0] = range;
                    // value[1] = '\0';
                    {parsetree range = head->parent->right->child->right;
                    int r1 = atoi(range->child->Lex->tk->value);
                    int r2 = atoi(range->child->right->right->Lex->tk->value);
                    int r = r2 -r1 +1;
                    char size[3];
                    ////sprintf(size,"%d",r);

                    // printf("range %d\n", r);
                    char type[100] = {'\0'};



                    switch(range->right->rule){
                        case 22: strcat(type, "ARRAY(INTEGER, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                        case 23:strcat(type, "ARRAY(REAL, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                        case 24:strcat(type, "ARRAY(BOOLEAN, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                    }}
                    break;
            }
        }

        //Declaring more than one identifier

        if(head->parent->value == 34)
        {
                parsetree temphead = head;
                while(temphead->parent->value!=33)
                    temphead = temphead->parent;

            if(temphead->parent->value == 33 && temphead->parent->parent->value==20){
            
            switch(temphead->parent->right->rule)
            {
                case 18: hashinsert(head->Lex->tk->value,"INTEGER",scope,"___");
                    break;
                case 19:hashinsert(head->Lex->tk->value,"REAL",scope,"___");
                    break;
                case 20:hashinsert(head->Lex->tk->value,"BOOLEAN",scope,"___");
                    break;
                case 21: 

                    // int range = atoi(head->parent->right->child->right->child->right->right->Lex->tk->value) - atoi(head->parent->right->child->right->child->Lex->tk->value);
                    // char value[3] = {"0"};
                    // value[0] = range;
                    // value[1] = '\0';
                    {parsetree range = temphead->parent->right->child->right;
                    int r1 = atoi(range->child->Lex->tk->value);
                    int r2 = atoi(range->child->right->right->Lex->tk->value);
                    int r = r2 -r1 +1;
                    char size[3];
                    //sprintf(size,"%d",r);

                    // printf("range %d\n", r);
                    char type[100] = {'\0'};



                    switch(range->right->rule){
                        case 22: strcat(type, "ARRAY(INTEGER, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                        case 23:strcat(type, "ARRAY(REAL, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                        case 24:strcat(type, "ARRAY(BOOLEAN, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                    }}
                    break;
            }
        }}

        //input parameters declaration

        if(head->parent->value == 8 || head->parent->value == 9){

            

            // printf("%s \n", head->Lex->tk->value);

            switch(head->right->rule){
                case 18: hashinsert(head->Lex->tk->value,"INTEGER",scope,"___");
                    break;
                case 19:hashinsert(head->Lex->tk->value,"REAL",scope,"___");
                    break;
                case 20:hashinsert(head->Lex->tk->value,"BOOLEAN",scope,"___");
                    break;
                case 21: 

                    // int range = atoi(head->parent->right->child->right->child->right->right->Lex->tk->value) - atoi(head->parent->right->child->right->child->Lex->tk->value);
                    // char value[3] = {"0"};
                    // value[0] = range;
                    // value[1] = '\0';
                    {parsetree range = head->right->child->right;

                   int r1 = atoi(range->child->Lex->tk->value);
                    int r2 = atoi(range->child->right->right->Lex->tk->value);
                    int r = r2 -r1 + 1;
                    char size[3];
                    //sprintf(size,"%d",r);

                    // printf("range %d\n", r);

                    char type[100] = {'\0'};



                    switch(range->right->rule){
                        case 22: strcat(type, "ARRAY(INTEGER, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                        case 23:strcat(type, "ARRAY(REAL, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                        case 24:strcat(type, "ARRAY(BOOLEAN, ");
                                 strcat(type, size);
                                 strcat(type, ")");
                                 hashinsert(head->Lex->tk->value, type ,scope, "___");
                                break;
                    }}
                    break;
            }

        }

        //outputparameters declaration

        if(head->parent->value == 11 || head->parent->value == 12){

        

            // printf("%s \n", head->Lex->tk->value);

            switch(head->right->rule){
                        case 22: hashinsert(head->Lex->tk->value,"INTEGER",scope, "___");
                        break;
                        case 23:hashinsert(head->Lex->tk->value,"REAL",scope,"___");
                        break;
                        case 24:hashinsert(head->Lex->tk->value,"BOOLEAN",scope,"___");
                        break;
                    }
        }


        // display(scope);
        // printf("------------------\n");

        if(head->parent->value != 7 && head->parent->value != 5 && head->parent->value != 26 && !checksymbolpresent(head->Lex->tk->value, scope))
            fprintf(fp,"ERROR 2: identifier %s not declared, line number %d\n", head->Lex->tk->value, head->Lex->tk->line);


        //Module Reuse Statement

        if(head->parent->value == 26){
            if(!check_func_present(head->Lex->tk->value))
                fprintf(fp,"ERROR 3: Function definition for %s not found, line number %d\n", head->Lex->tk->value, head->Lex->tk->line);

            else{

                char inputtype[1000] = {'\0'};
                char outputtype[1000] = {'\0'};
                if(head->parent->child->rule == 56){
                    parsetree outlist = head->parent->child->child;
                    strcat(outputtype, gettype(outlist->child->Lex->tk->value, scope));
                    parsetree outlistprime = outlist->child->right;

                    while(outlistprime->rule!= 59){
                        strcat(outputtype, "; ");
                        strcat(outputtype, gettype(outlistprime->child->Lex->tk->value, scope));
                        outlistprime = outlistprime->child->right;
                    }
                }

                parsetree inputlist = head->right;
                strcat(inputtype, gettype(inputlist->child->Lex->tk->value, scope));

                parsetree inputlistprime = inputlist->child->right;

                    while(inputlistprime->rule!= 59){
                        strcat(inputtype, "; ");
                        strcat(inputtype, gettype(inputlistprime->child->Lex->tk->value, scope));
                        inputlistprime = inputlistprime->child->right;
                    }
                 
                if(strcmp(inputtype, get_Function_input_type(head->Lex->tk->value))!=0){
                    fprintf(fp,"\nERROR 4: input types do not match at line number %d \n", head->Lex->tk->line);
                    fprintf(fp,"Entered input parameters - %s\n", inputtype);
                    fprintf(fp,"Expected input parameters - %s\n", get_Function_input_type(head->Lex->tk->value));
                }
                if(strcmp(outputtype, get_Function_output_type(head->Lex->tk->value))!=0){
                    fprintf(fp,"\nERROR 5: output types do not match at line number %d\n", head->Lex->tk->line);
                    fprintf(fp,"Entered output parameters - %s\n", outputtype);
                    fprintf(fp,"Expected output parameters - %s\n", get_Function_output_type(head->Lex->tk->value));
                }





            }
          }

          //Check that array index is always integer
          if(head->parent->value==24){
            //assert(0);
            if(strcmp(gettype(head->Lex->tk->value, scope), "INTEGER")!=0)
                fprintf(fp,"ERROR 6: Array index should be of type integer but here, %s has type %s, line number %d\n", head->Lex->tk->value, gettype(head->Lex->tk->value, scope), head->Lex->tk->line);
            }

          if(head->parent->rule == 41 && head->right->rule==44)
          {
            //char[100] type = {'\0'};
            //type = gettype(head->Lex->tk->value, scope);
            char *token = NULL;
            token = strtok(gettype(head->Lex->tk->value, scope), "(");
            if(token==NULL)
                fprintf(fp,"ERROR 7: Indexing cannot be done on %s which is not an array, but of type %s , line number %d\n", head->Lex->tk->value, gettype(head->Lex->tk->value, scope), head->Lex->tk->line);
            if(strcmp(token,"ARRAY")!=0){
                fprintf(fp,"ERROR 8: Indexing cannot be done on %s which is not an array, but of type %s , line number %d\n", head->Lex->tk->value, gettype(head->Lex->tk->value, scope), head->Lex->tk->line);
            }
          }

          
    }

    //type checking for assignment
    if(head->value==100 && (head->parent->value == 28 || head->parent->value == 29)){
        //printf("Type checking for line number %d\n", head->Lex->tk->line);
        int err = TypeChecker(fp, head, scope);
        //printf("err is %d\n", err);
    }

    if(head->value==21){
        int type2, error = 0;
        int type = TypeChecker(fp, head->child->right, scope);
        parsetree caseStmts = head->child->right->right->right;
        //assert(0);

        if(type==1)
            fprintf(fp,"ERROR 9: The switch statement cannot have identifier of type real, line number %d\n", head->Lex->tk->line);

        else{

            if(type==0 && caseStmts->right->rule != 85)
                fprintf(fp,"ERROR 10: The switch statement has identifier of type integer but no default statement, line number %d\n", head->Lex->tk->line);

            if(type==-1 && caseStmts->right->rule != 84)
                fprintf(fp,"ERROR 11: The switch statement has identifier of type boolean cannot have default statement, line number %d\n", caseStmts->right->Lex->tk->line);



             while(caseStmts->child->value!=109)
            {   
                // printf("%s\n", terms[caseStmts->child->right->child->value]);
                type2 = TypeChecker(fp, caseStmts->child->right->child, scope);

                if(type == type2){
                    caseStmts = caseStmts->child->right->right->right->right;
                    //assert(0);
                }
                else
                {   
                    error = 1;
                    break;
                }

            }

        }
       
        if(error){

            fprintf(fp,"ERROR 12: The type of identifier of switch statement is different from the types of case labels, line number %d\n", caseStmts->child->right->child->Lex->tk->line);
        }
    }

    if(head->value==22 && head->rule==39){
        int type = TypeChecker(fp, head->child->right, scope);
        if(type!=0)
            fprintf(fp,"ERROR 13: The identifier in FOR loop has to be integer, line number %d\n", head->Lex->tk->line);

    }

    if(head->value==22 && head->rule==40){
        int type = TypeChecker(fp, head->child->right, scope);
        if(type!=-1)
            fprintf(fp,"ERROR 14: The expression in WHILE loop has to be of type boolean, line number %d\n", head->Lex->tk->line);



    }




    populateSymbolTable(fp, head->right, scope);
    
}


// void typeCheckExpression(parsetree head, char* type){
//     if(head->rule==52)
//         typeCheckExpression(head->child, type);
//     if(head->rule == 53)
//         typeCheckExpression(head->child->right, type);

//     if(head->rule==61)
//         switch(head->child->child->child->rule){
//             case 43: strcpy(type, "REAL");
//                      break;
//             case 42: strcpy(type, "INTEGER");
//                      break;

//             case 41: {strcpy(type, gettype(head->Lex->tk->value, scope));

//             char *token = NULL;
//             token = strtok(gettype(head->Lex->tk->value, scope), "(");
//             if(token!=NULL){
//                 token = strtok(NULL, ",");
//                 strcpy(type, token);
//             }}
//             break;
            

//         }




// }



