#pragma once

#include "stdafx.h"
#include <vector>
#include "Gene.h"

class Chromosome;
typedef std::shared_ptr<Chromosome> ChromosomePtr;
class Chromosome
{
private:
	//typedef unsigned long long ChromVecItem;
	size_t _geneSize;
	int _nGenes;
	std::vector<bool> _geneCode;

	mutable std::vector<int> _bufferedCode;
	mutable bool _changed;
public:
	Chromosome(size_t geneSize = 0);
	~Chromosome();
	std::vector<int> decode() const;
	inline void addCode(int code);
	inline void clear(int resize = 0);
	inline void setCode(int ind, int code);
	Chromosome combine(const Chromosome &chromosome) const;
	void clear();
	std::string toString() const;

	Chromosome&operator=(const Chromosome&src) {
		_geneSize = src._geneSize;
		_geneCode = src._geneCode;
		_nGenes = src._nGenes;
		_bufferedCode = src._bufferedCode;
		_changed = src._changed;
		return *this;
	}
};

void Chromosome::addCode(int code)
{
	for (int i = (int)(_geneSize - 1); i >= 0; i--)
	{
		_geneCode.push_back((code >> i) & 0x1);
	}
	_nGenes++;
	_changed = true;
}

void Chromosome::clear(int resize) {
	_geneCode.clear();
	_geneCode.resize(resize*_geneSize);
	_nGenes = resize;
}

void Chromosome::setCode(int ind, int code)
{
	int indcnt = ind*_geneSize;
	for (int i = (int)(_geneSize - 1); i >= 0; i--)
	{
		_geneCode[indcnt] = (code >> i) & 0x1;
		indcnt++;
	}
	_changed = true;
}
