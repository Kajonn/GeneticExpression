#include "stdafx.h"
#include "Chromosome.h"
#include <sstream>

Chromosome::Chromosome(size_t geneSize) :
_geneSize(geneSize),
_nGenes(0),
_changed(true)
{
}


Chromosome::~Chromosome()
{
}

std::vector<int> Chromosome::decode() const 
{
	if (_changed) {

		std::vector<int> rvec(_nGenes);
		int rvecInd = 0;
		int nextCode = 0;
		int currBitInNext = 0;
		for each (bool var in _geneCode)
		{

			nextCode += var;

			if (++currBitInNext == _geneSize) {

				rvec[rvecInd]=nextCode;
				rvecInd++;
				nextCode = 0;
				currBitInNext = 0;
			}
			else {
				nextCode = nextCode << 1;
			}

		}
		_changed = false;
		_bufferedCode = rvec;
	}

	return _bufferedCode;
}

Chromosome Chromosome::combine(const Chromosome &chromosome) const {

	//ChromosomePtr newChromosome(new Chromosome(_geneSize));
	//Chromosome* newChromosomeP = newChromosome.get();
	Chromosome newChromosome(*this);
	newChromosome._changed = true;

	if (chromosome._geneCode.size() == _geneCode.size()) {

		size_t splitbit = std::rand() % _geneCode.size();

		for (size_t i = splitbit; i < _geneCode.size(); i++)
		{
			newChromosome._geneCode[i] = chromosome._geneCode[i];
		}

	}
	return newChromosome;

}

std::string Chromosome::toString() const {
	std::stringstream ss;
	for each (auto var in decode())
	{
		ss << var;
	}
	return ss.str();
}