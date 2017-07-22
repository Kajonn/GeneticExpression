#pragma once
#include "ExpressionToken.h"
class TokenValue :
	public ExpressionToken
{
public:
	TokenValue(double value);
	~TokenValue();
	double evaluate() const;
	std::string toString() const;
protected:
	const double _value;
	std::unique_ptr<ExpressionToken> clone() const {
		return std::unique_ptr<ExpressionToken>(new TokenValue(_value));
	};
};

