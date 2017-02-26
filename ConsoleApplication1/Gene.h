#pragma once

#include <memory>
#include "ExpressionToken.h"

class Gene
{
private:
	int _code;
	ExpressionTokenPtr _expression;
public:
	Gene(int code, ExpressionTokenPtr expression);
	~Gene();
	int getCode() const;
	const ExpressionToken& getExpression() const;
};

typedef std::shared_ptr<Gene> GenePtr;