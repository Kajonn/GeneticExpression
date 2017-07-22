#pragma once
#include <vector>
#include "ExpressionToken.h"

class ExpressionEvaluator;
typedef std::shared_ptr<ExpressionEvaluator> ExpressionEvaluatorPtr;

class ExpressionEvaluator
{
	std::vector<std::unique_ptr<ExpressionToken> > _tokens;
	struct TokenEvaluationState{ 
		ExpressionToken* token;
		bool leftFilled;
		TokenEvaluationState(ExpressionToken* token_,
			bool leftFilled_) : token(token_), leftFilled(leftFilled_) {}
	};
	void endOperator(std::vector<TokenEvaluationState> &operatorStack);
public:
	ExpressionEvaluator();
	~ExpressionEvaluator();
	void addToken(const ExpressionToken &token);
	double evaluate(bool log = false);
};

