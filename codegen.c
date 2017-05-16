int expstate = 0, opcount = 0;
int whilenum=0, conum=0, relnum=0, fornum = 0;
//FILE* fp = fopen("coder.asm","w");
void declarevariables(parsetree head, FILE* fp)
{
    int i;
    char datasection[] = "section .data\n\tnumberin_form:\tdb \"%d\",0\n\n\tnumberout_form:\tdb \"%d\",10,0\n";
    fprintf(fp, "%s", datasection);
    fprintf(fp,"section .bss\n");
   
    char* functionname = "driver";
    int j = get_func_hash_value(functionname);
    for(i=0;i<SIZE;i++){
        pNode* it  = ht->functable[j]->table[i]->next;
        if(it !=NULL && strcmp(it->name,"")!= 0){
        	char* yp = "ARRAY";
        	if(strncmp(it->type,yp,5)!=0)
            fprintf(fp,"\t%s:\t resd %d\n",it->name,1);
        	else{

        		char* type = it->type;
        		char *token = NULL;
            		token = strtok(it->type, "(");
            		if(token!=NULL){
                		token = strtok(NULL, ",");
                		token = strtok(NULL, ")");
                		if(token!=NULL)
                		strcpy(type, token);
            			}

            	int range = atoi(type);
            	fprintf(fp,"\t%s:\t resd %d\n",it->name,range);


        	}
        }


    }
}

void codegen(parsetree head, FILE* fp){
    /*parseTree mf = ast->child->right;
    parseTree typedefinitions = mf->child->child;
    parseTree decl = typedefinitions->right;*/
    //print("\nsection .data\n");
    declarevariables(head, fp);
    fprintf(fp,"\nsection .text\n");
    fprintf(fp,"global main\n");
    fprintf(fp,"extern scanf\n");
    fprintf(fp,"extern printf\n");
    fprintf(fp,"\nmain :\n");
    //handle_stmt(decl->right->child, output, ht);
    //fclose(fp);
}





void ExpressionCode(FILE *fpdummy, parsetree head, FILE *fp, char *scope)
{
	
	int noField,i,nofield1,nofield2;

	if(head==NULL || head->value==109)
		return;



	ExpressionCode(fpdummy,head->child, fp, scope);

	// printf("%s \n", terms[head->value]);



	switch(head->value){
	
		case 107:
			// printf("Here I am %d\n", head->parent->parent->value);
			if(head->parent->parent->parent->value==37 && expstate == 0){
				// assert(0);
				if(head->parent->parent->right->rule ==70 && head->parent->parent->parent->right->rule==65)
				{	
				 // assert(0);
				// expstate =1;
				fprintf(fp,"mov eax,%s\npush eax\n",head->Lex->tk->value);
				// expstate = 0;
				return;
				}}




			if(expstate==1){
				// printf(" expstate before fprintf %d\n", expstate);
				opcount++;
				if(opcount<=2){
				fprintf(fp,"mov eax,%s\npush eax\n",head->Lex->tk->value);
				return;
			}
			

			}

			break;
			

		case 106:
			if(head->parent->parent->parent->value==37){
			if((TypeChecker(fpdummy,head, scope))==0 && head->parent->parent->right->rule ==70 && head->parent->parent->parent->right->rule==65 && expstate==0)
			{	
				// assert(0);
				// expstate =1;
				fprintf(fp,"mov eax,%s\npush eax\n",head->Lex->tk->value);
				// expstate = 0;
				return;
			}}

			if((TypeChecker(fpdummy,head, scope))==0 && expstate ==1)
				{
					opcount++;
				if(opcount<=2){
					fprintf(fp,"push dword[%s]\n",head->Lex->tk->value);
					return;
					}
					
				}
				else
				{
					
				}

				break;
		
		case 82:

			// printf("%d %s %s %s \n", head->parent->parent->parent->value, terms[head->parent->parent->parent->value], terms[head->parent->parent->value], terms[head->parent->value]);
			if(!expstate){
			if(head->parent->parent->parent->value==38){
            			// printf("%s %s \n", head->parent->parent->parent->child->right, head->parent->right);
					expstate = 1;
					// assert(0);
					ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
					ExpressionCode(fpdummy,head->parent->right,fp,scope);
					//assert(0);
					expstate = 0;
					opcount = 0;
					// printf(" expstate %d\n", expstate);
            	}

					if(head->parent->parent->parent->value==35){
						// printf("%s %s \n", terms[head->parent->parent->parent->child->value], terms[head->parent->right->value]);
						// assert(0);
						expstate = 1;
						ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);

						ExpressionCode(fpdummy,head->parent->right,fp,scope);
						expstate = 0;
						opcount = 0;
						// printf(" expstate %d\n", expstate);
					}
		
			
				fprintf(fp,"pop ebx\npop eax\nadd eax,ebx\npush eax\n");
			}
				return;
		
		case 84:
		if(!expstate){
		if(head->parent->parent->parent->value==41){
            			// printf("%s %s \n", head->parent->parent->parent->child->right, head->parent->right);
					expstate = 1;
					assert(0);
					ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
					ExpressionCode(fpdummy,head->parent->right,fp,scope);
					expstate = 0;
					opcount = 0;
            	}

					if(head->parent->parent->parent->value==37){
						// printf("%s %s \n", terms[head->parent->parent->parent->child->value], terms[head->parent->right->value]);
						expstate = 1;
						
						ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
						// assert(0);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);
						// assert(0);
						expstate = 0;
						opcount = 0;
						
					}
		
			fprintf(fp,"pop ebx\npop eax\nimul ebx\npush eax\n");
		}
			return;

		case 85:
		if(!expstate){
		if(head->parent->parent->parent->value==41){
            			// printf("%s %s \n", head->parent->parent->parent->child->right, head->parent->right);
					expstate = 1;

					ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
					ExpressionCode(fpdummy,head->parent->right,fp,scope);
					expstate = 0;
					opcount = 0;
            	}

					if(head->parent->parent->parent->value==37){
						// printf("%s %s \n", terms[head->parent->parent->parent->child->value], terms[head->parent->right->value]);
						expstate = 1;

						ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);
						expstate = 0;
						opcount = 0;
					}

		
			fprintf(fp,"pop ebx\npop eax\npush edx\nmov edx,0\nidiv ebx\npop edx\npush eax\n");
		}
			return;
	
		case 83:

		if(head->value==83 && head->parent->value==30)
            	{		
            			ExpressionCode(fpdummy,head->right, fp, scope);
            			// noField = ExpressionCode(fpdummy,head->children[0],fp,scope);
						fprintf(fp,"pop ebx\nmov eax,0\nsub eax,ebx\npush eax\n");
						return;
						}
						



		else
		{	if(!expstate){
			if(head->parent->parent->parent->value==38){
            			// printf("%s %s \n", head->parent->parent->parent->child->right, head->parent->right);
					expstate = 1;
					ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
					ExpressionCode(fpdummy,head->parent->right,fp,scope);
					expstate = 0;
					opcount = 0;
            	}

			if(head->parent->parent->parent->value==35){
						// printf("%s %s \n", terms[head->parent->parent->parent->child->value], terms[head->parent->right->value]);
						expstate = 1;
						ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);
						expstate = 0;
						opcount = 0;
				}

			
				fprintf(fp,"pop ebx\npop eax\nsub eax,ebx\npush eax\n");
			}
				return;
			
			
		}

		case 74:
		// if(!expstate){
				if(head->parent->parent->parent->value==42){
						ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);
					}


					if(head->parent->parent->parent->value==48){

						ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);

				}
		
		fprintf(fp,"pop ebx\npop eax\nor eax, ebx\npush eax\n");

	// }
		return;

		case 73:
		// if(!expstate){
		if(head->parent->parent->parent->value==42){
						ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);
					}


					if(head->parent->parent->parent->value==48){

						ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
						ExpressionCode(fpdummy,head->parent->right,fp,scope);
					
				}
		
		fprintf(fp,"pop ebx\npop eax\nand eax, ebx\npush eax\n");
		// }
		return;

		case 86:
				if(!expstate){
					assert(0);
				if(head->parent->parent->parent->value==43){

					expstate = 1;
					ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
					ExpressionCode(fpdummy,head->parent->right,fp,scope);
					expstate = 0;
					opcount = 0;
				}

				if(head->parent->parent->parent->value==49){
					expstate = 1;
					ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
					ExpressionCode(fpdummy,head->parent->right,fp,scope);
					expstate = 0;
					opcount = 0;
				}
		
		fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njl .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
		relnum++;
	}
		return;

		case 87:

			if(!expstate){
			if(head->parent->parent->parent->value==43){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}

			if(head->parent->parent->parent->value==49){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}
		fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njle .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
		relnum++;
	}
		return;

		case 88:

		if(!expstate){
		if(head->parent->parent->parent->value==43){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
				
			}

			if(head->parent->parent->parent->value==49){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}

		fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njge .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
		relnum++;
	}
		return;

		case 89:
		if(!expstate){
		if(head->parent->parent->parent->value==43){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
				
			}

			if(head->parent->parent->parent->value==49){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}
		fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njg .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
		relnum++;
	}
		return;
		
		case 90:
		if(!expstate){
			if(head->parent->parent->parent->value==43){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}

			if(head->parent->parent->parent->value==49){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}
		fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\nje .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
		relnum++;
	}
		return;
		
		case 91:
			if(!expstate){
			if(head->parent->parent->parent->value==43){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
				
			}

			if(head->parent->parent->parent->value==49){
				expstate = 1;
				ExpressionCode(fpdummy,head->parent->parent->parent->child->right,fp,scope);
				ExpressionCode(fpdummy,head->parent->right,fp,scope);
				expstate = 0;
				opcount = 0;
			}

		fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njne .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
		relnum++;
	}
		return;

		default: break;

		

}

ExpressionCode(fpdummy,head->right, fp, scope);
}
		

void GenerateCodeStmts(FILE *fpdummy, parsetree head, FILE *fp, char *scope){

	if(head==NULL)
		return;

	if(head->value== 4)
		strcpy(scope, "driver");

	if(head->value==106 && head->parent->value==7)
		strcpy(scope, head->Lex->tk->value);

	switch(head->value){

		case 22:

		if(head->generated!=1){

				if(head->rule==40){

				expstate = 0;
				fprintf(fp,".while%d:\n",whilenum);
				ExpressionCode(fpdummy,head->child->right,fp,scope);
				fprintf(fp,"pop eax\ncmp eax,0000h\nje .endwhile%d\n", whilenum);

				GenerateCodeStmts(fpdummy,head->child->right->right->right, fp, scope);
				fprintf(fp,"jmp .while%d\n", whilenum);
				fprintf(fp,".endwhile%d:\n", whilenum);
				whilenum++;
			


			}

			if(head->rule==39){

				expstate = 0;
				fprintf(fp, ".for%d\n", fornum);
				parsetree id = head->child->right;

				fprintf(fp,"push dword[%s]\n",id->Lex->tk->value);
				fprintf(fp, "pop eax\n");
				// printf("%s\n", id->right->Lex->tk->value);
				// printf("%s\n", id->right->right->child->right->right->Lex->tk->value);

				int start = atoi(id->right->right->child->Lex->tk->value);
				int end = atoi(id->right->right->child->right->right->Lex->tk->value);
				// assert(0);
				fprintf(fp, "mov ecx, %d\n", start);
				fprintf(fp, "cmp eax, ecx\n");
				fprintf(fp, "jl .endfor%d\n", fornum);
				fprintf(fp, "mov ecx, %d\n", end);
				fprintf(fp, "cmp eax, ecx\n");
				fprintf(fp, "jg .endfor%d\n", fornum);
				GenerateCodeStmts(fpdummy,head->child->right->right->right->right, fp, scope);
				fprintf(fp,"jmp .for%d\n", fornum);
				fprintf(fp,".endfor%d:\n", fornum);
				fornum++;





			}

			

		}	head->generated = 1;

			break;
		case 18:
			if(head->generated!=1){
			if(head->child->value==63)
				 {
			fprintf(fp,"\n\tpush %s\n\tcall printf\n",head->child->right->Lex->tk->value);
			//fprintf(fp,"\n\tmov edi, numberout_form\n\tmov esi,[%s]\n\tmov al, 0\n\tcall printf\n",head->child->right->Lex->tk->value);
				 		

				 }			 				 
				 	// else
				 	// fprintf(fp,"call _UserInput\nmov dword[%s.%s], eax\n",stmt->children[1]->children[0]->str,stmt->children[1]->children[1]->str );
				 
			else
				 {	
				 	if(!(head->child->right->rule==41 && head->child->right->child->right->rule==44)){
				 		if(head->child->right->rule==41)
		fprintf(fp,"\n\tpush %s\n\tpush numberin_form\n\tcall scanf\n",head->child->right->child->Lex->tk->value);
				 		else
				 		{
		fprintf(fp,"\n\tpush %s\n\tpush numberin_form\n\tcall scanf\n",head->child->right->child->Lex->tk->value);
				 		}

				 	}	
				 }}

				 head->generated = 1;
				 break;

	}


	GenerateCodeStmts(fpdummy,head->child, fp, scope);

	switch(head->value){

		case 4: strcpy(scope, "driver");
				// assert(0);
				break;

		case 106: if(head->parent->value==7)
        			{
            			strcpy(scope, head->Lex->tk->value);
        			}				

        		break;

		case 100: 



			if(head->generated!=1){

			if(head->parent->value==28){

				parsetree id = head->parent->parent->parent->child;

				// printf("%s %s\n", id->Lex->tk->value, scope);

				int type = TypeChecker(fpdummy,id, scope);
				 // printf("%d\n", type);
				if(type==0){
					// assert(0);
					ExpressionCode(fpdummy,head->right, fp, scope);
					
					fprintf(fp,"pop eax\nmov dword[%s],eax\n",id->Lex->tk->value);
					//assert(0);

				}

				head->generated = 1;

				}


			}

			

			break;

		


	}



	GenerateCodeStmts(fpdummy,head->right, fp, scope);




}
