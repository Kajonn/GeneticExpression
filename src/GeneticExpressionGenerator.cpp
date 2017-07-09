#include "GeneticExpressionGenerator.h"

#include "ChromosomeFactory.h"
#include "GeneFactory.h"
#include <algorithm>
#include <chrono>
#include <iostream>

#define PRINT_ELAPSED(T1, T2) \
	time_span = duration_cast<duration<double>>(T2 - T1); \
	std::cout << "Elapsed " << time_span.count() << " seconds."; \
	std::cout << std::endl;


GeneticExpressionGenerator::GeneticExpressionGenerator()
{
}


GeneticExpressionGenerator::~GeneticExpressionGenerator()
{
}

ExpressionEvaluatorPtr GeneticExpressionGenerator::generateExpression(double target, unsigned int maxGenerations, unsigned int individualsInGeneration, unsigned int chromosomeSize, GeneFactory& geneFactory)
{
	
	using namespace std::chrono;
	steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> time_span;

	ChromosomeFactory factory;
	size_t geneSize = geneFactory.getGeneSize();

	std::vector<ScoredChromosome> scoredChromosomes(individualsInGeneration);
	std::vector<Chromosome> storedChromosomes(individualsInGeneration);
	
	ExpressionEvaluatorPtr bestExpression;
	
	std::cout << "Generating random start generation" << std::endl;
	t1 = steady_clock::now();
	for (size_t i = 0; i < individualsInGeneration; i++)
	{
		Chromosome chrom = factory.generateChromosome(geneSize, chromosomeSize);
		storedChromosomes[i]=factory.generateChromosome(geneSize, chromosomeSize);
		scoredChromosomes[i]=ScoredChromosome(&storedChromosomes[i], 0);
	}
	t2 = steady_clock::now();
	PRINT_ELAPSED(t1, t2);
	std::cout << "Done: " << std::endl;

	for (size_t i = 0; i < maxGenerations; i++)
	{
		std::cout << "Generation: " << i << std::endl;
		//Evaluate generation

		std::cout << "Evaluate generation" << std::endl;
		t1 = steady_clock::now();
		for (auto &chrom : scoredChromosomes)
		{
			ExpressionEvaluator expr;
			for (auto var : chrom.chromosome->decode())
			{
				const ExpressionToken &token = geneFactory.getExpression(var);
				//std::cout << token.toString();
				expr.addToken(token);
			}
			//std::cout << std::endl;
			double result = expr.evaluate();
			chrom.score = std::abs(result - target);
		}
		t2 = steady_clock::now();
		PRINT_ELAPSED(t1, t2);
	
		std::cout << "Sort generation" << std::endl;
		t1 = steady_clock::now();
		std::sort(scoredChromosomes.begin(), scoredChromosomes.end(), 
				[](ScoredChromosome a, ScoredChromosome b) 
				{
					return a.score < b.score; 
				});
		t2 = steady_clock::now();
		PRINT_ELAPSED(t1, t2);
		
		std::cout << "Copy best expression:" << std::endl;
		//Print best
		t1 = steady_clock::now();
		bestExpression.reset(new ExpressionEvaluator());
		for (auto var : scoredChromosomes.begin()->chromosome->decode())
		{
			const ExpressionToken &token = geneFactory.getExpression(var);
			std::cout << token.toString() << " ";
			bestExpression->addToken(token);
		}
		std::cout << std::endl;
		bestExpression->evaluate(true);
		t2 = steady_clock::now();
		PRINT_ELAPSED(t1, t2);

		if (scoredChromosomes.begin()->score == 0) {
			break;
		}
		else if(i!=maxGenerations){

			std::cout << "Genrating new generation:" << std::endl;
			//Generate new generation
			t1 = steady_clock::now();
			std::vector<Chromosome> newGeneration;
			newGeneration.reserve(individualsInGeneration);
			for (size_t j = 1; j < scoredChromosomes.size()+1; j++)
			{
				Chromosome* crom1 = scoredChromosomes[std::rand() % j].chromosome;
				Chromosome* crom2 = scoredChromosomes[std::rand() % j].chromosome;

				newGeneration.push_back(crom1->combine(*crom2));
			}

			//Replace generation
			for (size_t j = 0; j < scoredChromosomes.size(); j++)
			{
				storedChromosomes[j] = newGeneration[j];
				scoredChromosomes[j].chromosome = &storedChromosomes[j];
				scoredChromosomes[j].score = 0;
			}
			t2 = steady_clock::now();
			PRINT_ELAPSED(t1, t2);

		}
	}
	
	std::cout << "Finished! Best expression for target " << target << ":" << std::endl;
	bestExpression->evaluate(true);
	return bestExpression;
}
