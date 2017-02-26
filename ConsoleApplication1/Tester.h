#pragma once

#include "GeneFactory.h"
#include "Chromosome.h"
#include "GeneFactory.h"
#include "TokenValue.h"

class Tester
{
public:
	Tester();
	~Tester();
	bool runTest(size_t geneSize, unsigned int tokens);
};

