#pragma once
#include "ExpressionToken.h"
class TokenOperator :
	public ExpressionToken
{
public:
	TokenOperator(char op);
	~TokenOperator();
	void addLeftToken(ExpressionTokenPtr token);
	void addRightToken(ExpressionTokenPtr token);
protected:
	std::string TokenOperator::toString() const;
	const char _tokenOperator;
	ExpressionTokenPtr _rightToken;
	ExpressionTokenPtr _leftToken;
public:
	ExpressionTokenPtr clone() const { return ExpressionTokenPtr(new TokenOperator(_tokenOperator)); };
	double evaluate();
};