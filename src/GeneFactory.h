#pragma once

#include <vector>
#include "Gene.h"
#include "ExpressionToken.h"

class GeneFactory
{
	std::vector<GenePtr> _codeToGene;
	const size_t _geneSize;
	ExpressionTokenPtr dummyExpression;
public:
	GeneFactory(size_t size);
	~GeneFactory();
	size_t getGeneSize() const { return _geneSize; }
	GenePtr addGene(ExpressionTokenPtr token);
	const ExpressionToken &getExpression(int code) const;
};

