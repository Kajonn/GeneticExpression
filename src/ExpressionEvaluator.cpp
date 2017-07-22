#include "ExpressionEvaluator.h"
#include <iostream>
#include <math.h>

ExpressionEvaluator::ExpressionEvaluator()
{
}


ExpressionEvaluator::~ExpressionEvaluator()
{
}

void ExpressionEvaluator::addToken(const ExpressionToken &token) {
	_tokens.push_back(token.clone());
}

void ExpressionEvaluator::endOperator(std::vector<TokenEvaluationState> &operatorStack) {
	const ExpressionToken* token = operatorStack.back().token;
	operatorStack.pop_back();

	if (!operatorStack.empty()) {

		TokenEvaluationState &oldopState = operatorStack.back();

		if (!oldopState.leftFilled) {
			oldopState.token->addLeftToken(token);
			oldopState.leftFilled = true;
		}
		else {
			oldopState.token->addRightToken(token);
			endOperator(operatorStack);
		}

	}
}

double ExpressionEvaluator::evaluate(bool log) {
	bool syntaxError = false;
	ExpressionToken* root = NULL;
	std::vector<TokenEvaluationState> operatorStack;
	
	for (auto &token : _tokens)
	{
		ExpressionToken* tokenPtr = token.get();
		switch (tokenPtr->getType())
		{
		case ExpressionToken::Operator:
			{
				operatorStack.push_back(TokenEvaluationState(tokenPtr, false));
			}
			break;
		case ExpressionToken::Value:
			
			if (!operatorStack.empty()) {

				TokenEvaluationState &opState = operatorStack.back();
				if (!opState.leftFilled) {
					opState.token->addLeftToken(tokenPtr);
					opState.leftFilled = true;
				} else {

					opState.token->addRightToken(tokenPtr);

					endOperator(operatorStack);

				}

			}
			else if(!root) {
				continue;
			}

			break;
		default: {
				continue;
			}
		}

		if (!root) {
			root = tokenPtr;
		}
	}

	if(!operatorStack.empty()) {
		syntaxError = true;
	}

	if (!syntaxError && root) {
		const double result = root->evaluate();
		if (log) {
			std::cout << root->toString() << " = "<< result << std::endl;
		}
		return result;
	} 
	else
		return sqrt(-1);
}
