#include "unity.h"
#include "Evaluate.h"
#include "mock_Stack.h"
#include "mock_Token.h"
#include "Error.h"
#include "CException.h"
#include <stdio.h>

extern ErrorCode error;

void setUp(void){}

void tearDown(void){}

void test_evaluateOperator_multiply(void){
	Stack dataStack;
	OperatorToken operator = {.type = OPERATOR_TOKEN, .name = "*" , .precedence = 100};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 8};
	 
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(8,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	evaluateOperator(&dataStack, &operator);	
}

void test_evaluateOperator_add(void){
	Stack dataStack;
	OperatorToken operator = {.type = OPERATOR_TOKEN, .name = "+" , .precedence = 70};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 6};
	 
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(6,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	evaluateOperator(&dataStack, &operator);	
}

void test_evaluateOperator_devide(void){
	Stack dataStack;
	OperatorToken operator = {.type = OPERATOR_TOKEN, .name = "/" , .precedence = 100};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 2};
	 
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(2,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	evaluateOperator(&dataStack, &operator);	
}

void test_evaluateOperator_minus(void){
	Stack dataStack;
	OperatorToken operator = {.type = OPERATOR_TOKEN, .name = "-" , .precedence = 70};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 2};
	 
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(2,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	evaluateOperator(&dataStack, &operator);	
}

void test_evaluateOperator_and(void){
	Stack dataStack;
	OperatorToken operator = {.type = OPERATOR_TOKEN, .name = "&" , .precedence = 20};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 1};
	 
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(0,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	evaluateOperator(&dataStack, &operator);	
}

void test_evaluateALLOperatorsOnStack_multiply_and_devide(void){
	Stack dataStack,operatorStack;

	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "/" , .precedence = 70};
	OperatorToken operator2 = {.type = OPERATOR_TOKEN, .name = "*" , .precedence = 70};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken4 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken5 = {.type = NUMBER_TOKEN, .value = 4}; 
	
	pop_ExpectAndReturn(&operatorStack,&operator1);
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(2,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	
	pop_ExpectAndReturn(&operatorStack,&operator2);
	pop_ExpectAndReturn(&dataStack,&NumberToken3);
	pop_ExpectAndReturn(&dataStack,&NumberToken4);
	createNumberToken_ExpectAndReturn(4,&NumberToken5);
	push_Expect(&dataStack,&NumberToken5);
	
	pop_ExpectAndReturn(&operatorStack, NULL);	
	evaluateALLOperatorsOnStack(&dataStack,&operatorStack);
}

void test_tryEvaluateOperatorsOnStackThenPush_add_and_multiply(void){
	Stack dataStack,operatorStack;

	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "+" , .precedence = 70};
	OperatorToken operator2 = {.type = OPERATOR_TOKEN, .name = "*" , .precedence = 100};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 12};

	
	
	pop_ExpectAndReturn(&operatorStack,&operator2);
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(12,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack,&operator1);

	
	tryEvaluateOperatorsOnStackThenPush(&dataStack, &operatorStack, &operator1);
}


void test_evaluate_1_plus_2(void){
	Stack dataStack,operatorStack;

	Tokenizer tokenizer = {.expression = "1+2" , .startIndex = 0};
	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "+" , .precedence = 70};
	NumberToken NumberToken1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken NumberToken2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken NumberToken3 = {.type = NUMBER_TOKEN, .value = 3};
	

	
	tokenizerNEW_ExpectAndReturn("1+2",&tokenizer);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&NumberToken1);
	push_Expect(&dataStack,&NumberToken1);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator1);
	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&operator1);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&NumberToken2);
	push_Expect(&dataStack,&NumberToken2);
	nextToken_ExpectAndReturn(&tokenizer,NULL);

	
	pop_ExpectAndReturn(&operatorStack,&operator1);
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(3,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	pop_ExpectAndReturn(&operatorStack, NULL);	
	
	pop_ExpectAndReturn(&dataStack,&NumberToken3);
	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"1+2");
	}Catch(error){
	
	}
}

void test_should_return_12_for_4_multiply_3(void){
	Stack dataStack;
	Stack operatorStack;
	int check;
	//Initialize tokenizer,token and stack
	Tokenizer tokenizer = {.expression = "4*3", .startIndex = 0};
	OperatorToken multiply = {.type= OPERATOR_TOKEN, .name = "*", .precedence=100};
	NumberToken NumberToken1 = {.type= NUMBER_TOKEN, .value=4};
	NumberToken NumberToken2 = {.type= NUMBER_TOKEN, .value=3};
	NumberToken NumberToken3 = {.type= NUMBER_TOKEN, .value = 12};

	tokenizerNEW_ExpectAndReturn("4*3",&tokenizer);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&NumberToken1);
	push_Expect(&dataStack,&NumberToken1);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&multiply);
	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&multiply);
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&NumberToken2);
	push_Expect(&dataStack,&NumberToken2);
	nextToken_ExpectAndReturn(&tokenizer,NULL);

	
	pop_ExpectAndReturn(&operatorStack,&multiply);
	pop_ExpectAndReturn(&dataStack,&NumberToken2);
	pop_ExpectAndReturn(&dataStack,&NumberToken1);
	createNumberToken_ExpectAndReturn(12,&NumberToken3);
	push_Expect(&dataStack,&NumberToken3);
	pop_ExpectAndReturn(&operatorStack, NULL);	
	
	pop_ExpectAndReturn(&dataStack,&NumberToken3);
	
	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"4*3");	
	}Catch(error){
	
	}
	
}

void test_evaluate_43_HASH_44(){

	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;
	int e;
	OperatorToken operator1 = {.type = UNKNOWN_TOKEN, .name = "#", .precedence = 100};
	NumberToken number1={.type = NUMBER_TOKEN, .value = 43};
	NumberToken number2={.type = NUMBER_TOKEN, .value = 44};

	tokenizerNEW_ExpectAndReturn("43#44",&tokenizer);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number1);
	push_Expect(&dataStack,&number1);

	nextToken_ExpectAndThrow(&tokenizer,ERR_NOT_OPERATOR);

	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"43#44");
	}
	Catch(error){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR,error);
	}
}

void test_evaluate_40_plus_multiply(){

	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;

	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	OperatorToken operator2 = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken number1={.type = NUMBER_TOKEN, .value = 40};


	tokenizerNEW_ExpectAndReturn("40+*",&tokenizer);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number1);
	push_Expect(&dataStack,&number1);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator2);
	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&operator2);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator1);
	
	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"40+*");
	}
	Catch(error){
		TEST_ASSERT_EQUAL(ERR_INVALID_TOKEN,error);
	}
}

void test_evaluate_38_space_39(){

	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;


	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken number1={.type = NUMBER_TOKEN, .value = 38};
	NumberToken number2={.type = NUMBER_TOKEN, .value = 39};

	tokenizerNEW_ExpectAndReturn("38 39",&tokenizer);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number1);
	push_Expect(&dataStack,&number1);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number2);

	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"38 39");
	}
	Catch(error){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR,error);
	}
}

void test_evaluate_PLUS(){

	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;


	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken number1={.type = NUMBER_TOKEN, .value = 1};
	NumberToken number2={.type = NUMBER_TOKEN, .value = 2};

	tokenizerNEW_ExpectAndReturn("+",&tokenizer);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator1);

	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"+");
	}
	Catch(error){
		TEST_ASSERT_EQUAL(ERR_INVALID_TOKEN,error);
	}
	
}

void test_evaluate_42_XOR_2_subtract(){

	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;

	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	OperatorToken operator2 = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	NumberToken number1={.type = NUMBER_TOKEN, .value = 42};
	NumberToken number2={.type = NUMBER_TOKEN, .value = 2};

	tokenizerNEW_ExpectAndReturn("42^2-",&tokenizer);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number1);
	push_Expect(&dataStack,&number1);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator1);
	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&operator1);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number2);
	push_Expect(&dataStack,&number2);
	
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator2);
	pop_ExpectAndReturn(&operatorStack,&operator1);
	push_Expect(&operatorStack,&operator1);
	push_Expect(&operatorStack,&operator2);
	
	nextToken_ExpectAndThrow(&tokenizer,ERR_INVALID_TOKEN);	
	
	ErrorCode error;
	Try{
		evaluate(&dataStack,&operatorStack,"42^2-");
	}
	Catch(error){
		TEST_ASSERT_EQUAL(ERR_INVALID_TOKEN,error);
	}
}

void test_evaluate_3_plus_4_plus_5_subtract_6(){

	Tokenizer tokenizer;
	Stack dataStack;
	Stack operatorStack;


	OperatorToken operator1 = {.type = OPERATOR_TOKEN, .name = "+", .precedence =70};
	OperatorToken operator2 = {.type = OPERATOR_TOKEN, .name = "-", .precedence =70};
	OperatorToken operator3 = {.type = OPERATOR_TOKEN, .name = "+", .precedence =70};
	NumberToken number1={.type = NUMBER_TOKEN, .value = 3};
	NumberToken number2={.type = NUMBER_TOKEN, .value = 4};
	NumberToken number3={.type = NUMBER_TOKEN, .value = 5};
	NumberToken number4={.type = NUMBER_TOKEN, .value = 6};
	NumberToken answer1 = {.type = NUMBER_TOKEN, .value =7};
	NumberToken answer2 = {.type = NUMBER_TOKEN, .value =12};
	NumberToken answer3 = {.type = NUMBER_TOKEN, .value =6};


	tokenizerNEW_ExpectAndReturn("3+4+5-6",&tokenizer);
	//push 3
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number1);
	push_Expect(&dataStack,&number1);
	//push +
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator1);
	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&operator1);
	//push 4
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number2);
	push_Expect(&dataStack,&number2);
	
	//check next precedence is larger anot
	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator3);
	pop_ExpectAndReturn(&operatorStack,&operator1);
	pop_ExpectAndReturn(&dataStack,&number2);
	pop_ExpectAndReturn(&dataStack,&number1);
	createNumberToken_ExpectAndReturn(7, &answer1);
	push_Expect(&dataStack, &answer1);

	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&operator3);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number3);
	push_Expect(&dataStack,&number3);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&operator2);
	pop_ExpectAndReturn(&operatorStack,&operator1);
	pop_ExpectAndReturn(&dataStack,&number3);
	pop_ExpectAndReturn(&dataStack,&answer1);
	createNumberToken_ExpectAndReturn(12, &answer2);
	push_Expect(&dataStack, &answer2);

	pop_ExpectAndReturn(&operatorStack,NULL);
	push_Expect(&operatorStack,&operator2);

	nextToken_ExpectAndReturn(&tokenizer,(Token *)&number4);
	push_Expect(&dataStack,&number4);

	nextToken_ExpectAndReturn(&tokenizer,NULL);
	pop_ExpectAndReturn(&operatorStack,&operator2);
	pop_ExpectAndReturn(&dataStack,&answer2);
	pop_ExpectAndReturn(&dataStack,&number4);
	createNumberToken_ExpectAndReturn(6,&answer3);
	push_Expect(&dataStack,&answer3);

	pop_ExpectAndReturn(&operatorStack,NULL);
	pop_ExpectAndReturn(&dataStack,&answer3);
	
	ErrorCode error;
	Try{
	evaluate(&dataStack,&operatorStack,"3+4+5-6");
	}
	Catch(error){
	TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR,error);
	}
}
