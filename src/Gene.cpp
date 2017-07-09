#include "Gene.h"


Gene::Gene(int code, ExpressionTokenPtr expression) :
_code(code),
_expression(expression)
{
}


Gene::~Gene()
{
}


int Gene::getCode() const
{
	return _code;
}

const ExpressionToken& Gene::getExpression() const
{
	return *_expression;
}
