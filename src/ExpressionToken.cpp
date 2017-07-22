#include "ExpressionToken.h"


ExpressionToken::ExpressionToken(TokenType type) : _type(type),
_leftToken(NULL), _rightToken(NULL)
{
}


ExpressionToken::~ExpressionToken()
{
}

void ExpressionToken::addLeftToken(ExpressionToken const * token)
{
	_leftToken = token;

}

void ExpressionToken::addRightToken(ExpressionToken const * token)
{
	_rightToken = token;

}
