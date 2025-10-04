#include "rpn.h"

#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>
#include<math.h>
int is_number(char token);
int is_left_associative(char operator);
int test_precedence(char operator1,char operator2);
int get_precedence(char operator);
int is_operator(char token);
int is_bracket(char token);
int numbcheck(char token, int i, char *expr);
int valid(char token);
int mismatched(char *expr);
double evalexpression(double op1, double op2, char token);
/* convert an infix expression to postfix (rpn) using the */
/* shunting yard algorithm. */
/* return a queue containing the postfix expression. */
/* if an error occurs during evaluation, return silently with NULL. */
Queue *infix_to_postfix(char *expr)
{
	char token;
	char *memorytoken;
	int i=0;
	Queue *output=initialise_queue();
	Stack *operators=initialise_stack();
	char *operator;
	char *next;
	char valnext;
	int end=0;
	int j;
	int x=0;
	int total=2;
	char *decimal;
	int bracket;


	/*int numtokens=0;*/
	while (expr[i]){
		token=expr[i];
		bracket=is_bracket(token);
		i++;
		
	

		if ((valid(token)==1)||(mismatched(expr)!=0)){
			free_stack(operators);
			free_queue(output);
			return NULL;
		}
		if (numbcheck(token,i,expr)==1)
		{/*if it is a number*/
			

			
			if (expr[i]=='.'||is_number(expr[i])==1||(is_operator(token)==1)){
				
				total=0;
				x=0;
				if (is_operator(token)==1){
					total=1;
					x=1;
				}

				j=i;
				
				
			
				
				while (is_number(expr[j])==1||expr[j]=='.'){
					total++;
					j++;
					
				}


				j=i-1;

				decimal=(char *) calloc(total+2,sizeof(char)+1);
				if (is_operator(token)==1){
					decimal[0]=token;
					j++;

				}
				
				while (is_number(expr[j])==1||expr[j]=='.'){
					
					decimal[x]=expr[j];
					j++;
					x++;
					

					
				}
				i=j;

				decimal[x]='\0';
			
				

				push_queue(output,decimal,(strlen(decimal)+1));
				free(decimal);
			}
	
			else if (is_number(expr[i])!=1){
				memorytoken=malloc(2);
				memorytoken[0]=token;
				memorytoken[1]='\0';
				
				push_queue(output,memorytoken,2);
				free(memorytoken);
				
			}
		
		}
		
		
		else if (is_operator(token)==1||is_bracket(token)>0)
		{	
			
			
			
			if (bracket==1){
			
						
				memorytoken=malloc(2);
				memorytoken[0]=token;
				memorytoken[1]='\0';
				
				push_stack(operators,memorytoken,2);
				free(memorytoken);
					
		
			}
			
			
			else if (peek_stack(operators)!=NULL){

					next=peek_stack(operators);
					valnext=*next;
		


					end=0;
				
					while ((((test_precedence(valnext,token))==1)&&(is_left_associative(valnext)==1)&&(end==0)&&(is_bracket(valnext)!=1))||((end==0)&&(is_bracket(valnext)!=1)&&(bracket==2)))/*need to add AND not a left bracket*/
					{	
					
						
						operator=pop_stack(operators);

					
						
						push_queue(output,operator,strlen(operator)+1);
						free(operator);
						operator=NULL;
						
							
						

						if (peek_stack(operators)!=NULL){
							next=peek_stack(operators);
							valnext=*next;
							
						
				
						}
						else{
							end=1;
						
					

						}
						
					}

					
					
			}
		
			if (peek_stack(operators)!=NULL){
				
				if ((bracket==2)&&(is_bracket(valnext)==1)){
				
					operator=pop_stack(operators);
					free(operator);
				
				}
			}

			if ((bracket==0)&&(is_number(token)==0)){
				
				memorytoken=malloc(2);
				memorytoken[0]=token;
				memorytoken[1]='\0';
				
				push_stack(operators,memorytoken,2);
				free(memorytoken);
			
			}

			

			
			
		}
					

		
		
	}
	
	
	while ((peek_stack(operators)!=NULL)){
		operator=pop_stack(operators);
		if(operator!=NULL){
			if(is_operator(*operator)==1){
			
				push_queue(output,operator,strlen(operator)+1);
				
				
			}
		}
		free(operator);
	}
	

	
	free_stack(operators);




	return output;
}

int mismatched(char *expr){
	int bracketscount=0;
	int i=0;
	int left=0;
	int right=0;
	for (i=0;expr[i];i++){
		if (right>left){
			return 1;
		}
		if(expr[i]=='('){/*count left brack*/
			left++;
		}
		else if(expr[i]==')'){/*count right brack*/
			right++;

		}
	}
	bracketscount=left-right;
	return bracketscount;
}


int valid(char token){
	if ((is_operator(token)==0)&&(is_bracket(token)==0)&&(is_number(token)==0)&&(token!=' ')){
		return 1;
	}
	return 0;
}

int numbcheck(char token, int i, char *expr){
	if (is_operator(token)&&(get_precedence(token)==1)){/*if token is an operator and is either - or +*/
		/*printf("\n1");*/
		if (is_number(expr[i])==1){/*if there is a number following the token */
			/*printf("\n2");*/
			if (i-1==0){/*if the token is the first item in the expressiob*/
				/*printf("\nsigned number");*/
				return 1;
			}

			
			else if (is_operator(expr[i-2])==1||((expr[i-2]==' ')&&(is_operator(expr[i-3])==1))||(is_bracket(expr[i-2])>0)){/*if the token isn't the first in the expr, and the previous token is an operator or the previous
			token is a space and the token before that is an operator*/
				/*printf("\nsigned number");*/
				return 1;

			}
			
		}
	}
	else if (is_number(token)==1){/*if the token is a number*/
		/*printf("\nnumber");*/
		return 1;
	}
	else{
		/*printf("\n not numb or signed");*/
		return 0;
	}
	/*printf("\n not");*/
	return 0;
	

}
int is_bracket(char token){
	if (token=='('){
		return 1;
	}
	else if(token==')'){
		return 2;
	}
	else{
		return 0;
	}

}
int is_left_associative(char operator){
	/*printf("\nis associative");*/
	if (operator=='^'){
		return 0;
	}
	else{
		return 1;
	}
}

int test_precedence(char operator1,char operator2){
	if (get_precedence(operator1)>=get_precedence(operator2)){
		/*printf("bigger or equal\n");*/
		return 1;
	}
	else{
		/*printf("less than\n");*/
		return 0;
	}

}

int get_precedence(char operator){
	if (operator=='+'||operator=='-'){
		return 1;
	}
	else if(operator=='*'||operator=='/'){
		return 2;
	}
	else{
		return 3;
	}
}

int is_number(char token){
	int i=0;
	char c=i+'0';
	int number=0;
	
	for (i=0;i<10;i++){
		c=i+'0';
		
		/*printf("\n%c",c); */
		if (token ==c){
			number=1;
		}
	}
	return number;
}

int is_operator(char token){
	/*printf("\nisoperator");*/
	if ((token=='+')||(token=='-')||(token=='*')||(token=='/')||(token=='^'))
	{
		/*printf("\nTRUE");*/
		return 1;
	}
	else{
		/*printf("\nFALSE");*/
		return 0;
	}
}


/* evaluate the rpn expression given in *queue. */
/* return the value of the evaluated expression. */
/* if an error occurs during evaluation, return silently with HUGE_VAL. */
/* assume a precision of eight decimal places when performing arithmetic. */
double evaluate_rpn(Queue *queue)
{
	Stack *stack=initialise_stack();
	char *token;
	double tokendouble;
	double *op1;
	double *op2;
	double copyresult;
	/*double op1_double;
	double op2_double;*/
	double result;
	double *dynamicresult;
	double *dynamicoperand;
	char *endptr;
	/*print_queue(queue,print_string);*/
	/*token=pop_queue(queue);*/
	while (queue->head!=NULL){
		/*printf("\nWHILE");*/
		token=pop_queue(queue);
		/*printf("\nTOKEN\n");*/
		/*print_string(token);*/
		tokendouble=strtod(token,&endptr);
		if ((endptr !=token) && (*endptr =='\0')){
			/*printf("\nNUMBER");*/
			if ((token[0]=='-')||(token[0]=='+')){

			}


			
			dynamicoperand=(double *) calloc(1,sizeof(double));/*%0.8f*/
			dynamicoperand[0]=tokendouble;
			/*printf("\nresult:");
			printf("\n%f",result);*/
			/*print_double(dynamicresult);*/
				
			push_stack(stack,dynamicoperand,sizeof(double));

			free(dynamicoperand);
			/*free(endptr);*/

		}
		else if ((*token=='+')||(*token=='-')||(*token=='*')||(*token=='/')||(*token=='^')){
			/*printf("\nOPERATOR");*/
			/*printf("\nSTACK\n");*/
			/*print_stack(stack,print_double);*/
			
			
				/*printf("\nOP2");*/
			op2=(pop_stack(stack));

			op1=(pop_stack(stack));
				
				/*else{
					free_stack(stack);
					return 0;
				}*/
			
			/*else{
				free_stack(stack);
				return 0;
			}*/
			/*printf("\nCALCULATING");*/
			/*op1_double=strtod(op1,&endptr);
			op2_double=strtod(op2,&endptr);*/
			result=evalexpression(*op1,*op2,*token);
			free(op1);
			free(op2);
			dynamicresult=(double *) calloc(1,sizeof(double));/*%0.8f*/
			dynamicresult[0]=result;
			/*printf("\nresult:");*/
			/*printf("\n%f",result);*/
			/*print_double(dynamicresult);*/
				
			push_stack(stack,dynamicresult,sizeof(double));

			free(dynamicresult);
		}

		/*pop_queue(queue);*/
		free(token);
	}
	/* this is just a placeholder return */
	/* you will need to replace it */
	/*free_stack(stack);*/
	dynamicresult=(pop_stack(stack));
	copyresult=*dynamicresult;
	free_stack(stack);
	free(dynamicresult);
	
	return copyresult;
}

double evalexpression(double op1, double op2, char token){
	double result=0;
	if (token=='+'){
		result=op1+op2;
	}
	else if (token=='-'){
		result=op1-op2;
	}
	else if (token=='/'){
		result=op1/op2;
	}
	else if (token=='*'){
		result=op1*op2;
	}
	else if (token=='^'){
		result=pow(op1,op2);


	}
	return result;

}

