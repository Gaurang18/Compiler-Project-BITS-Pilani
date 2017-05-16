//#include "symboltable.c"
/*
Batch Number - 37
AKSHAY R - 2013B3A7543P
GAURANG BANSAL - 2014A7PS128P
*/

//FILE* ftype = ("typecheck.txt","w");

// FILE *semantic = fopen("Type&SemanticErrors.txt", "w+");

// FILE *typecheck = fopen("TypeCheckErrors.txt", "w+");

int TypeChecker(FILE *fp, parsetree head, char *scope){
	int type1, type2;
	int i,error=0;

	switch(head->value){

		case 100:
		{	
			
				type1 = TypeChecker(fp, head->parent->parent->parent->child, scope);
				type2 = TypeChecker(fp, head->right, scope);


				if(type2==-2 || type1==-2) return -2;
				else
					if(type2!=type1) 
					{
						fprintf(fp,"\nERROR 15: Type of left variable %s not equal to type of right expression, line number %d\n", head->parent->parent->parent->child->Lex->tk->value, head->Lex->tk->line);
						//printf("Left type %d Right Type %d\n", type1, type2);
						return -2;
					}
				else return type2;
				
		} break;

		case 106:{ 	
					// if(head->value==4){
     //     				strcpy(scope, "driver");
     //     				break;
     //    			}
					// if(head->parent->value==7)
     //   				 {
     //        			strcpy(scope, head->Lex->tk->value);
     //        			break;
     //    			 }

				if(!checksymbolpresent(head->Lex->tk->value, scope))
					return -2;
				else{

					char type[25] = {'\0'};
					strcpy(type, gettype(head->Lex->tk->value, scope));
					char *token = NULL;
            		token = strtok(gettype(head->Lex->tk->value, scope), "(");
            		if(token!=NULL){
                		token = strtok(NULL, ",");
                		if(token!=NULL)
                		strcpy(type, token);
            			}
            		// printf("%s %s\n", head->Lex->tk->value, type);



            		if(strcmp(type, "INTEGER")==0)
            			return 0;
            		if(strcmp(type, "REAL")==0)
            			return 1;
            		if(strcmp(type, "BOOLEAN")==0)
            			return -1;
            	}
            } break;


            case 107: return 0;

            case 108: return 1;

            case 68:
            case 69: return -1;

            case 82:
            case 83:
            		if(head->value==83 && head->parent->value==30)
            		{
            			return TypeChecker(fp, head->right, scope);
            		}

            		if(head->parent->parent->parent->value==38){
            			//printf("%s %s \n", terms[head->parent->parent->parent->child->right->value], terms[head->parent->right->value]);

            		if((type1 = TypeChecker(fp, head->parent->parent->parent->child->right,scope))==-2)
						return -2;
					if((type2 = TypeChecker(fp, head->parent->right, scope))==-2)
						return -2;
					}

					if(head->parent->parent->parent->value==35){

						//printf("%s %s \n", terms[head->parent->parent->parent->child->value], terms[head->parent->right->value]);
						if((type1 = TypeChecker(fp, head->parent->parent->parent->child,scope))==-2)
						return -2;
						if((type2 = TypeChecker(fp, head->parent->right, scope))==-2)
						return -2;
					}
					
					// printf("%d, %d", type1, type2);

					if(type1!=type2)
					{
						fprintf(fp,"ERROR 16: Types don't match, line number %d\n",head->Lex->tk->line);
						return -2;
					}		
					if(type1==-1)
					{
						fprintf(fp,"ERROR 17: Boolean expressions cannot be added or subtracted, line number %d\n", head->Lex->tk->line);
						return -2;
					}	
					return type1;
					break;

            case 84:
            case 85:
            		// printf("MUL value %d\n",head->parent->parent->parent->value );
            		if(head->parent->parent->parent->value==41){
            			// printf("41 %s %s \n", terms[head->parent->parent->parent->child->right->value], terms[head->parent->right->value]);

            		if((type1 = TypeChecker(fp, head->parent->parent->parent->child->right,scope))==-2)
						return -2;
					if((type2 = TypeChecker(fp, head->parent->right, scope))==-2)
						return -2;
					}

					if(head->parent->parent->parent->value==37){

						//printf("37 %s %s \n", terms[head->parent->parent->parent->child->value], terms[head->parent->right->value]);
						if((type1 = TypeChecker(fp, head->parent->parent->parent->child,scope))==-2)
						return -2;
						if((type2 = TypeChecker(fp, head->parent->right, scope))==-2)
						return -2;
					}
					
					//printf("%d, %d", type1, type2);

					if(type1!=type2)
					{
						fprintf(fp,"ERROR 18: Types don't match, line number %d\n",head->Lex->tk->line);
						return -2;
					}		
					if(type1==-1)
					{
						fprintf(fp,"ERROR 19: Boolean expressions cannot be added or subtracted, line number %d\n", head->Lex->tk->line);
						return -2;
					}	
					return type1;
					break;

			case 86:
			case 87:
			case 88:
			case 89:
			case 90:
			case 91:
					if(head->parent->parent->parent->value==43){
					if((type1 = TypeChecker(fp, head->parent->parent->parent->child,scope))==-2)
						return -2;
					if((type2 = TypeChecker(fp, head->parent->right, scope))==-2)
						return -2;
					}

					if(head->parent->parent->parent->value==49){
					if((type1 = TypeChecker(fp, head->parent->parent->parent->child->right,scope))==-2)
						return -2;
					if((type2 = TypeChecker(fp, head->parent->right, scope))==-2)
						return -2;
					}

					if((type1!=0&&type1!=1)||(type2!=0&&type2!=1))
					{
						fprintf(fp,"ERROR 20: Invalid expression. Relational operations possible only on int and real, line number %d\n", head->Lex->tk->line);
						return -2;
					}
					if(type1!=type2)
					{
						fprintf(fp,"ERROR 21: Types of expressions should be same while comparing, line number %d\n", head->Lex->tk->line);
						return -2;
					}
				return -1;

				break;

			case 73:
			case 74:

					if(head->parent->parent->parent->value==42){
						if((type1 = TypeChecker(fp, head->parent->parent->parent->child,scope))!=-1)
					{
						fprintf(fp,"ERROR 22: Logical operators can only be applied to boolean type, line number %d\n",  head->Lex->tk->line);
						return -2;
					}
					if((type2 = TypeChecker(fp, head->parent->right, scope))!=-1)
					{
						fprintf(fp,"ERROR 23: Logical operators can only be applied to boolean type, line number %d\n",  head->Lex->tk->line);
						return -2;
					}
					}


					if(head->parent->parent->parent->value==48){
					if((type1 = TypeChecker(fp, head->parent->parent->parent->child->right,scope))!=-1)
					{
						fprintf(fp,"ERROR 24: Logical operators can only be applied to boolean type, line number %d\n",  head->Lex->tk->line);
						return -2;
					}
					if((type2 = TypeChecker(fp, head->parent->right, scope))!=-1)
					{
						fprintf(fp,"ERROR 25: Logical operators can only be applied to boolean type, line number %d\n",  head->Lex->tk->line);
						return -2;
					}
				}
				return -1;
				break;

			default: 
			{
				parsetree child = head->child;

				while(child!=NULL && child->value!=109 )
				{	
					if(child->value==24){

					}
					/*else if(child->left->value == 49 ){
						return type1;
					}*/
					//child = child->right;

					else if((type1 = TypeChecker(fp, child,scope))==-2)
						error=1;
					if(type1 == -1 && child->value == 45){
						return -1;
					}
					
					child = child->right;
				}

				if(error==1)
					return -2;

				return type1;
			}

			
				
		 		
	}

	return 1;
}
