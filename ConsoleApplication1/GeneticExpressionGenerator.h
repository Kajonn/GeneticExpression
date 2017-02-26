#pragma once

#include "ExpressionEvaluator.h"
#include "Chromosome.h"

class GeneFactory;

class GeneticExpressionGenerator
{
	class ScoredChromosome {
	public:
		Chromosome* chromosome;
		double score;
		ScoredChromosome() : chromosome(NULL), score(0) {}
		ScoredChromosome(Chromosome* chromosome_,
			double score_) : chromosome(chromosome_), score(score) {}
		bool operator()(const ScoredChromosome &a, const ScoredChromosome& b) {
			return a.score < b.score;
		}
	};

public:
	GeneticExpressionGenerator();
	~GeneticExpressionGenerator();
	ExpressionEvaluatorPtr generateExpression(double target, unsigned int maxGenerations, unsigned int individualsInGeneration, unsigned int chromosomeSize, GeneFactory& geneFactory);
};

