#pragma once
#include "ExpressionToken.h"
class TokenOperator :
	public ExpressionToken
{
public:
	TokenOperator(char op);
	~TokenOperator();
protected:
	std::string toString() const;
	const char _tokenOperator;
public:
	std::unique_ptr<ExpressionToken> clone() const {
		return std::unique_ptr<ExpressionToken>(new TokenOperator(_tokenOperator));
	};
	double evaluate() const;
};
