#include <bits/stdc++.h>
#include "RTree.hpp"

using namespace sjtu;

RTree<int, 3, 1> tree;

HyperBound<1> generateBound(int x1, int x2) {
	std::vector<Bound> tmp;
	tmp.push_back(Bound(x1, x2));
	return HyperBound<1>(tmp);
}

int main() {
	tree.insert(generateBound(1, 2), 1);
	tree.insert(generateBound(1, 2), 2);
	tree.insert(generateBound(1, 2), 3);
	tree.insert(generateBound(1, 2), 4);
	tree.insert(generateBound(1, 2), 5);
	tree.insert(generateBound(1, 2), 6);
	tree.insert(generateBound(1, 2), 7);
	tree.insert(generateBound(1, 2), 8);
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.remove(generateBound(1, 2)); tree.travel();
	tree.insert(generateBound(1, 2), 1);
	tree.insert(generateBound(1, 2), 2);
	tree.insert(generateBound(1, 2), 3);
	tree.insert(generateBound(1, 2), 4);
	tree.insert(generateBound(1, 2), 5);
	tree.insert(generateBound(1, 2), 6);
	tree.insert(generateBound(1, 2), 7);
	tree.insert(generateBound(1, 2), 8);
	auto ret = tree.getPointSet(generateBound(1, 2));
	printf("%d\n", (int)ret.size());
	std::sort(ret.begin(), ret.end());
	for (auto element : ret) {
		printf("%d\n", element);
	}
	return 0;
}
