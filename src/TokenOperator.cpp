#include "TokenOperator.h"
#include <sstream>

TokenOperator::TokenOperator(char op) : ExpressionToken(Operator), _tokenOperator(op)
{
}


TokenOperator::~TokenOperator()
{
}

void TokenOperator::addLeftToken(ExpressionTokenPtr token)
{
	_leftToken = token;

}

void TokenOperator::addRightToken(ExpressionTokenPtr token)
{
	_rightToken = token;

}


double TokenOperator::evaluate()
{
	double right = _rightToken?_rightToken->evaluate():0;
	double left = _leftToken ? _leftToken->evaluate() : 0;

	switch (_tokenOperator)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '/':
		return left / right;
	case '*':
		return left * right;
	default:
		return 0;
	}

}


std::string TokenOperator::toString() const {
	std::stringstream ss;
	if (_leftToken)
		ss << "(" << _leftToken->toString();	

	ss << _tokenOperator;

	if (_rightToken)
		ss << _rightToken->toString() << ")";

	return ss.str();
};
