#pragma once
#include "ExpressionToken.h"
class TokenValue :
	public ExpressionToken
{
public:
	TokenValue(double value);
	~TokenValue();
	double evaluate();
	std::string toString() const;
protected:
	const double _value;
	ExpressionTokenPtr clone() const { return ExpressionTokenPtr(new TokenValue(_value)); };
};

