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
	std::vector<std::shared_ptr<TokenValue>> tokensop;

	std::unique_ptr<TokenOperator> plusOp(new TokenOperator('+'));
	std::unique_ptr<TokenOperator> minusOp(new TokenOperator('-'));
	std::unique_ptr<TokenOperator> divOp(new TokenOperator('/'));
	std::unique_ptr<TokenOperator> mulOp(new TokenOperator('*'));

	GenePtr plus = geneFactory.addGene(plusOp.get());
	GenePtr minus = geneFactory.addGene(minusOp.get());
	GenePtr div = geneFactory.addGene(divOp.get());
	GenePtr mul = geneFactory.addGene(mulOp.get());


	for (size_t i = 0; i < tokens; i++)
	{
		std::shared_ptr<TokenValue>valueToken(new TokenValue(i));
		tokensop.push_back(valueToken);
		GenePtr newGene = geneFactory.addGene(valueToken.get());
		geneValues.push_back(newGene);
	}

	Tester tester;
	tester.runTest(geneSize, tokens);

	GeneticExpressionGenerator generator;
	generator.generateExpression(100, 1000, 10000, 10, geneFactory);

}
