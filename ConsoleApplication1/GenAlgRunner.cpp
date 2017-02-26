#include "stdafx.h"
#include "GenAlgRunner.h"
#include "GeneFactory.h"
#include "Chromosome.h"
#include "GeneFactory.h"
#include "TokenValue.h"
#include "Tester.h"
#include "TokenOperator.h"
#include "GeneticExpressionGenerator.h"

GenAlgRunner::GenAlgRunner()
{
}


GenAlgRunner::~GenAlgRunner()
{
}

void GenAlgRunner::run() {

	size_t geneSize = 4;
	unsigned int tokens = 12;

	GeneFactory geneFactory(geneSize);

	std::vector<GenePtr> geneValues;

	GenePtr plus = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('+')));
	GenePtr minus = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('-')));
	GenePtr div = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('/')));
	GenePtr mul = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('*')));

	for (size_t i = 0; i < tokens; i++)
	{
		GenePtr newGene = geneFactory.addGene(ExpressionTokenPtr(new TokenValue(i)));
		geneValues.push_back(newGene);
	}

	Tester tester;
	tester.runTest(geneSize, tokens);

	GeneticExpressionGenerator generator;
	generator.generateExpression(100, 1000, 10000, 10, geneFactory);

}
