#include "Evaluate.h"
#include "Token.h"
#include "Stack.h"
#include "Error.h"
#include <string.h>
#include <stdio.h>
#include "CException.h"

int evaluate(Stack *dataStack,Stack *operatorStack,char *expression){
			Tokenizer *tokenizer;
			Token *token;
			OperatorToken *operator;
			tokenizer = tokenizerNEW(expression);
			NumberToken *result;
			int i;

			while((token = nextToken(tokenizer)) != NULL){	
					if(token->type == NUMBER_TOKEN && i%2 == 0){
						push(dataStack, (NumberToken *)token);
					}
					else if(token->type == OPERATOR_TOKEN && i%2 != 0){	
							tryEvaluateOperatorsOnStackThenPush(dataStack, operatorStack, (OperatorToken *)token);
					}else{
						if(token->type != NUMBER_TOKEN){
							Throw(ERR_INVALID_TOKEN);
						}else if(token->type != OPERATOR_TOKEN){
							Throw(ERR_NOT_OPERATOR);
						}
					}
				i++;
			}
			
			if(token == NULL){
				evaluateALLOperatorsOnStack(dataStack,operatorStack);
				printf("come");	
			}
		
			
	
			result=(NumberToken*)pop(dataStack);
			return result->value;		
}

void tryEvaluateOperatorsOnStackThenPush(Stack *dataStack, Stack *operatorStack  , OperatorToken *operator){
			OperatorToken *operatorCompare;

		do{
			operatorCompare = pop(operatorStack);
			if(operatorCompare == NULL){
				break;	
			}
			else if((operator->precedence) > operatorCompare->precedence){
				push(operatorStack,operatorCompare);
				break;
			}else{
				evaluateOperator(dataStack,operatorCompare);
			}
		}while((operatorCompare = pop(operatorStack)) != NULL);
				push(operatorStack,operator);
		 
}

void evaluateALLOperatorsOnStack(Stack *dataStack,Stack *operatorStack){
		OperatorToken *operator;
		while((operator = pop(operatorStack)) != NULL){
			evaluateOperator(dataStack,operator);
		}	
}

void evaluateOperator(Stack *dataStack, OperatorToken *operator){
	int value3;
	
	NumberToken *value1;
	value1 = pop(dataStack);
	NumberToken *returnNumberToken;
	
	NumberToken *value2;
	value2 = pop(dataStack);
	 
	if(strcmp(operator->name,"+")==0){
		value3 = (value1->value + value2->value);
	}else if(strcmp(operator->name,"-")==0){
		value3 = (value1->value - value2->value);
	}else if(strcmp(operator->name,"/")==0){
		value3 = (value1->value / value2->value);
	}else if(strcmp(operator->name,"*")==0){
		value3 = (value1->value*value2->value);
	}else if(strcmp(operator->name,"%")==0){
		value3 = (value1->value % value2->value);
	}else if(strcmp(operator->name,"^")==0){
		value3 = (value1->value ^ value2->value);
	}else if(strcmp(operator->name,"&")==0){
		value3 = (value1->value & value2->value);
	}else if(strcmp(operator->name,"%")==0){
		value3 = (value1->value | value2->value);
	}else{
		Throw(ERR_NOT_OPERATOR);
	}
	
	returnNumberToken = createNumberToken(value3);
	push(dataStack,returnNumberToken);
}

