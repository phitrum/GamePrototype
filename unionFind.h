#pragma once
#include "constants.h"

class UnionFind {
	std::vector<int> _sets;
	int _number_of_sets;

public:
	UnionFind() {
		_number_of_sets = 0;
	}

	void Reset(int number_of_sets) {
		_sets.clear();
		_sets.resize(number_of_sets, -1);
		_number_of_sets = number_of_sets;
	}

	bool Union(int set_a, int set_b) {
		int root_a = Find(set_a), root_b = Find(set_b);
		if (root_a == root_b) return false;
		_sets[root_a] += _sets[root_b];
		_sets[root_b] = root_a;
		_number_of_sets--;
		return true;
	}

	int Find(int element) {
		if (_sets[element] < 0) return element;
		return (_sets[element] = Find(_sets[element]));
	}

	inline int GetNumberOfSets() {
		return _number_of_sets;
	}
};