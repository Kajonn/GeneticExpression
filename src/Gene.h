#pragma once

#include <memory>
#include "ExpressionToken.h"

class Gene
{
private:
	int _code;
	const ExpressionToken* _expression;
public:
	Gene(int code, const ExpressionToken* expression);
	~Gene();
	int getCode() const;
	const ExpressionToken& getExpression() const;
};

typedef std::shared_ptr<Gene> GenePtr;
