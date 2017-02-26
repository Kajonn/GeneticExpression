#include "stdafx.h"
#include "GeneFactory.h"
#include "TokenValue.h"


GeneFactory::GeneFactory(size_t size) :
_geneSize(size)
{
	dummyExpression.reset(new TokenValue(0));
}


GeneFactory::~GeneFactory()
{
}


GenePtr GeneFactory::addGene(ExpressionTokenPtr token)
{
	//Generate code

	int geneNr = _codeToGene.size();
	GenePtr newGene(new Gene(geneNr, token));
	_codeToGene.push_back(newGene);

	return newGene;
}

const ExpressionToken &GeneFactory::getExpression(int code) const {

	unsigned int index = code;

	if (index<0 || index >= _codeToGene.size()) {
		//LOG?
		return *dummyExpression;
	}
	else {
		return _codeToGene[index]->getExpression();
	}
}