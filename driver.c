/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.c"
#include "symboltable.c"
#include "codegen.c"

int parse_table[NON_TERMINALS][TERMINALS]; 

int main (int argc, char* argv[]){
	
	int input;
	int a,b;
	int flagger =0; 
	int tyu = 0;
	int parsetreenodes[1] = {0};
    int astnodes[1] = {0};

	if(argc != 3){
		printf("Please enter according to the correct format\n");
		return 0;
	}
	printf("\nLevel 4: All Modules \n\tAbstract Syntax Tree\n\tsymboltable\n\tsemantic checking\n\ttypechecking\n\tcode generation\n\tSUCCESSFULLY IMPLEMENTED\n\n");
	printf("\n1 : for printing the token list \n2 : for parsing to verify the syntactic correctness of the input source code and produce parse tree on console\n3 : for creating the abstract syntax tree and printing it on console\n4 : for displaying the amount of allocated memory and number of nodes to each of parse tree and abstract syntax tree\n5 : for printing the Symbol Table\n6 : Type Checking and Semantic Verification\n7 : Code Generation\n0 : Exit\n\n");
	
	FILE* fp1 = fopen(argv[1],"a");
	FILE* fp2 = fopen(argv[2],"w");

	FILE *semantic = fopen("Type&SemanticErrors.txt", "w+");

	if(fp1==NULL)
    {
        printf("File not found\n");
        return 0;
    }
    if(fp2==NULL)
    {
        printf("File not found\n");
        return 0;
    }

	fprintf(fp1,"%s","\r\n$");
	fclose(fp1);
	createsymboltable();
	FILE* fp = fopen(argv[1], "r");
	int symcount = 0;
	parsetree head = NULL;

		scanf("%d", &input);

	do{

			if(input==1){
					rewind(fp);
					fseek( fp, 0, SEEK_SET);
					fp = getstream(fp);
				    
					node* Lex = getNextToken();					//Call method in lexer
				    int i = 1;
				    int j = 0;
					while(strcmp(Lex->tk->value,"$")!=0){
						if(strcmp(Lex->tk->token,"ERROR") == 0){
							j++;
						}else{
				        	printf("%d. token = %s, value = %s, line = %d\n", i++,Lex->tk->token, Lex->tk->value, Lex->tk->line);	//print tokens to console
				   		}
				        free(Lex);
				        node* Lex = getNextToken();
				    }
				    printf("\nTotal Tokens :- %d\n",i+j);
				    printf("Valid Tokens Found:- %d\n",i);
				    printf("Error Found:- %d\n",j);
			}


			if(input==2){
				int firsts[51][11] = {-1};
				int follows[51][15] = {-1};
				ComputeFirstAndFollowSets(G, firsts, follows);
				Initialise_table(parse_table);
    			parsing_table(parse_table,G);
    			initialise_stack();
       			head = parse_Source_Code(argv[1]);
       			countNodes(head, parsetreenodes);
       			populateLexemes(head, argv[1]);
			printf("\nTREE TRAVERSAL:  PRE ORDER\n");
       			printParseTree(head);
       			flagger =2;
			}

			if(input == 3){
				if(head == NULL || flagger < 2){
					printf("Please run parser first\n");
				}else{
				createAbstractSyntaxTree(head);
       			countNodes(head, astnodes);
			printf("\nTREE TRAVERSAL:  PRE ORDER\n");
       			printParseTree(head);
			flagger = 3;
				}
			}

			if(input== 4){
				if(flagger <3){
					printf("Please create AST\n");
				}else{
				a = parsetreenodes[0]*sizeof(struct Parse_Tree);
				b = astnodes[0]*sizeof(struct Parse_Tree)/2;
				printf("\nParse tree\t\tNumber of nodes = %d Allocated Memory = %d Bytes\n",parsetreenodes[0],parsetreenodes[0]*sizeof(struct Parse_Tree));
				printf("Abstract Syntax tree\tNumber of nodes = %d Allocated Memory = %d Bytes\n",astnodes[0]/2,astnodes[0]*sizeof(struct Parse_Tree)/2);
				float percentage = ((float)((a-b)*100)/(float)(a));
				printf("AST Compression percentage = %.2f\n",percentage);
				}	
			}


			if(input == 5){
				if(flagger <3){
					printf("Please create AST\n");
				}else{
				if(symcount == 0){
				char scope[100];
  				memset(scope, '\0', sizeof(scope));

  					
       				populateSymbolTable(semantic, head, scope);
       				displaySymbolTable();
				symcount =1;
				}else{
					printf("\nSymbol Table Printed Above\n");
				}
				}
			}

   			if(input == 6){

   				if(semantic!=NULL)
   				fclose(semantic);

   				FILE *fptr = fopen("Type&SemanticErrors.txt", "r");
   				char c;
   				fseek(fptr,0,SEEK_SET);
				
   				c = fgetc(fptr);
   				    while (c != EOF){
   				        printf ("%c", c);
   				        c = fgetc(fptr);
					tyu++;
   				    }
				flagger = 6;
   				fclose(fptr);
				if(tyu == 0){
					printf("\n Successfully Compiled Code\n")	;
				}

			// Typechecking
   				/*FILE* fptr = fopen("typecheck.txt","r");
   				fseek(fptr,0,SEEK_SET);
   				c = fgetc(fptr);
   				    while (c != EOF){
   				        printf ("%c", c);
   				        c = fgetc(fptr);
   				    }
   				fclose(fptr);*/
			}
       			
   			if(input == 7){

   				FILE *fpdummy = fopen("ignore.txt", "W");
				if(flagger < 6 || tyu != 0){
				  printf("Please Use Semantic and Typechecking first\n");
				}
				else{

				char scope[100];
				memset(scope, '\0', sizeof(scope));
				codegen(head, fp2);

   			 	GenerateCodeStmts(fpdummy, head, fp2, scope);
   			 	// assert(0);
				}
   			 	 fclose(fp2); 

   			 	// fclose(fpdummy);
			}
       			 	 
			printf("\n1 : for printing the token list \n2 : for parsing to verify the syntactic correctness of the input source code and produce parse tree on console\n3 : for creating the abstract syntax tree and printing it on console\n4 : for displaying the amount of allocated memory and number of nodes to each of parse tree and abstract syntax tree\n5 : for printing the Symbol Table\n6 : Type Checking and Semantic Verification\n7 : Code Generation\n0 : Exit\n\n");
			scanf("%d", &input);
	}
		while(input==1 || input==2||input ==3 || input ==4 || input==5 || input==6||input ==7);
		printf("\nThank You For Using Compiler\n");

	return 0;
}
