#pragma once

#include <string>
#include <ostream>
#include <memory>

class ExpressionToken
{
public:
	enum TokenType
	{
		Operator,
		Value,
		Undef
	};
	ExpressionToken(TokenType type);
	virtual ~ExpressionToken();
	void addLeftToken(ExpressionToken const * token);
	void addRightToken(ExpressionToken const * token);
protected:
	const TokenType _type;
	ExpressionToken const * _rightToken;
	ExpressionToken const * _leftToken;
public:
	virtual std::string toString() const = 0;
	TokenType getType() const { return _type; };
	virtual double evaluate() const = 0;
	virtual std::unique_ptr<ExpressionToken> clone() const = 0;
	
	friend std::ostream& operator<<(std::ostream &os, const ExpressionToken& token);
};


inline std::ostream& operator<<(std::ostream &os, const ExpressionToken& token) {
	os << token.toString();
	return os;
}

