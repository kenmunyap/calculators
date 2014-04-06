#ifndef Evaluate_H
#define Evaluate_H

#include "Token.h"
#include "Stack.h"

int evaluate(Stack *dataStack,Stack *operatorStack,char *expression);	
void tryEvaluateOperatorsOnStackThenPush(Stack *dataStack, Stack *operatorStack  , OperatorToken *operator);
void evaluateALLOperatorsOnStack(Stack *operatorStack,Stack *dataStack);
void evaluateOperator(Stack *dataStack, OperatorToken *operator);

#endif // Evaluate_H
