#pragma once

#include "stdafx.h"
#include "Chromosome.h"

class ChromosomeFactory
{
public:
	ChromosomeFactory();
	~ChromosomeFactory();
	Chromosome generateChromosome(size_t geneSize, unsigned int nGenes);
};

