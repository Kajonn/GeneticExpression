#pragma once

#include <string>
#include <ostream>
#include <memory>

class ExpressionToken;
typedef std::shared_ptr<ExpressionToken> ExpressionTokenPtr;



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
	virtual void addLeftToken(ExpressionTokenPtr token) {};
	virtual void addRightToken(ExpressionTokenPtr token) {};
protected:
	const TokenType _type;
public:
	virtual std::string toString() const = 0;
	TokenType getType() const { return _type; };
	virtual double evaluate() = 0;
	virtual ExpressionTokenPtr clone() const = 0;
	
	friend std::ostream& operator<<(std::ostream &os, const ExpressionToken& token);
};


inline std::ostream& operator<<(std::ostream &os, const ExpressionToken& token) {
	os << token.toString();
	return os;
}

