#include "stdafx.h"
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

	GenePtr plus = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('+')));
	GenePtr minus = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('-')));
	GenePtr div = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('/')));
	GenePtr mul = geneFactory.addGene(ExpressionTokenPtr(new TokenOperator('*')));

	for (size_t i = 0; i < tokens; i++)
	{
		GenePtr newGene = geneFactory.addGene(ExpressionTokenPtr(new TokenValue(i)));
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

		for each (auto var in geneValues)
		{
			codes.push_back(var->getCode());
		}

		for each (auto code in codes)
		{
			chromosome.addCode(code);
			std::cout << code << std::endl;
		}


		int i = 0;
		for each (int var in chromosome.decode())
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
