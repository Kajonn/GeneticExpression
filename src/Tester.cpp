#include "Tester.h"
#include "TokenOperator.h"
#include "ExpressionEvaluator.h"
#include "Logging.h"


Tester::Tester()
{

}


Tester::~Tester()
{
}



bool Tester::runTest(size_t geneSize, unsigned int tokens)
{
	bool succes = true;
	

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


	//Chromosome test
	{
		std::vector<int> codes;
		Chromosome chromosome(geneSize);

		codes.push_back(plus->getCode());
		codes.push_back(minus->getCode());
		codes.push_back(div->getCode());
		codes.push_back(mul->getCode());

		for (auto var : geneValues)
		{
			codes.push_back(var->getCode());
		}

		for (auto code : codes)
		{
			chromosome.addCode(code);
			std::cout << code << std::endl;
		}


		int i = 0;
		for (int var : chromosome.decode())
		{
			std::cout << var << std::endl;
			TEST_ERROR("encoding", codes[i], var, succes);
			/*if (codes[i] != var) {
				std::cerr << "Error in decoding, Expected: " << codes[i] << " Got: " << var << std::endl;
				succes = false;
			}*/
			i++;
		}
	}


	//Expression test
	{
		ExpressionEvaluator evaluator;

		evaluator.addToken( plus->getExpression() );
		evaluator.addToken(geneValues[2]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());
		
		double result = evaluator.evaluate();
		std::cout << result << std::endl;
		TEST_ERROR("evaluator", 4, result, succes);
	}

	//Expression test
	{
		ExpressionEvaluator evaluator;

		evaluator.addToken(minus->getExpression());
		evaluator.addToken(geneValues[3]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());

		double result = evaluator.evaluate(true);
		std::cout << result << std::endl;
		TEST_ERROR("evaluator", 1, result, succes);
	}

	//Expression test
	{
		ExpressionEvaluator evaluator;

		evaluator.addToken(mul->getExpression());
		evaluator.addToken(geneValues[3]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());

		double result = evaluator.evaluate(true);
		std::cout << result << std::endl;
		TEST_ERROR("evaluator", 6, result, succes);
	}

	//Expression test
	{
		ExpressionEvaluator evaluator;

		evaluator.addToken(div->getExpression());
		evaluator.addToken(geneValues[10]->getExpression());
		evaluator.addToken(geneValues[5]->getExpression());

		double result = evaluator.evaluate(true);
		std::cout << result << std::endl;
		TEST_ERROR("evaluator", 2, result, succes);
	}

	//Expression test
	{
		ExpressionEvaluator evaluator;

		evaluator.addToken(div->getExpression());
		evaluator.addToken(minus->getExpression());
		evaluator.addToken(mul->getExpression());
		evaluator.addToken(plus->getExpression());
		evaluator.addToken(plus->getExpression());

		evaluator.addToken(geneValues[2]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());
		evaluator.addToken(geneValues[2]->getExpression());

		double result = evaluator.evaluate(true);
		std::cout << result << std::endl;
		TEST_ERROR("evaluator", 5, result, succes);
	}


	//Generate chromosome
	{
	}

	return succes;
}
