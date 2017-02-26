#include "stdafx.h"
#include "ChromosomeFactory.h"


ChromosomeFactory::ChromosomeFactory()
{
}


ChromosomeFactory::~ChromosomeFactory()
{
}


Chromosome ChromosomeFactory::generateChromosome(size_t geneSize, unsigned int nGenes)
{
	//ChromosomePtr newChromsome(new Chromosome(geneSize));
	//Chromosome* newChromsomeP = newChromsome.get();
	Chromosome newChromsome(geneSize);
	newChromsome.clear(nGenes);

	int geneValues = std::pow(2, geneSize);

	for (size_t i = 0; i < nGenes; i++) {
	
		newChromsome.setCode(i, std::rand() % geneValues);
	}

	return newChromsome;
}
