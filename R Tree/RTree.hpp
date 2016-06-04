#ifndef SJTU_RTREE_HPP
#define SJTU_RTREE_HPP

#include "RTreeCommon.hpp"
#include "RTreeNode.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
class RTree{
private:
	RTreeNode<T, M, D> *root;

	void __clear(RTreeNode<T, M, D> *now);
	void __find(const RTreeNode<T, M, D> * const now, const HyperBound<D> &bound, std::vector<T> &storge)const;
	RTreeNode<T, M, D> * splitNode(RTreeNode<T, M, D> *now);
	RTreeNode<T, M, D> * Find_Leaf(HyperBound<D> &key, RTreeNode<T, M, D> *t);
	void CondenseTree(RTreeNode<T, M, D> *t, std::vector<RTreeNode<T, M, D> *> &Q);
	RTreeNode<T, M, D> * chooseLeaf(const HyperBound<D> &key, const T &value);
	void adjust(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *brother);
	void pickSeeds(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *t0, RTreeNode<T, M, D> *t1);
	void pickNext(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *t0, RTreeNode<T, M, D> *t1);
	RTreeNode<T, M, D> * Find_Leaf_Exist(const HyperBound<D> &key, RTreeNode<T, M, D> *t);

public:
	RTree();
	void insert(const HyperBound<D> &key, const T &value, bool flag = false);
	bool remove(const HyperBound<D> &key);
	std::vector<T> getPointSet(const HyperBound<D> &bound)const;
	void travel() {
		puts("******************************************************************");
		__travel(root);
		puts("******************************************************************");
	}
	void __print(const RTreeNode<T, M, D> * const root)const {
		puts("----------------------------------------------------------");
		printf("Level = %d, Size = %d [", (int)root -> level, (int)root -> size);
		for (int i = 0; i < D; i++) {
			printf("(%.0f, %.0f)%c ", root -> box.bounds[i].lowerBound, root -> box.bounds[i].upperBound, ",]"[i + 1 == D]);
		}
		puts("");
		if (root -> level == 0) {
			for (int i = 0; i < root -> size; i++) {
				std::pair<HyperBound<D>, T> now = *static_cast<std::pair<HyperBound<D>, T> *>(root -> child[i]);
				printf("(%.0f, %.0f)(%.0f, %.0f) %d\n", root -> box.bounds[0].lowerBound, root -> box.bounds[0].upperBound,
					                             root -> box.bounds[1].lowerBound, root -> box.bounds[1].upperBound, now.second);
			}
		}
		puts("----------------------------------------------------------");
	}
	void __travel(const RTreeNode<T, M, D> *root) {
		if (root == nullptr) {
			return;
		}
		__print(root);
		if (root -> level > 0) {
			for (int i = 0; i < root -> size; i++) {
				__travel(static_cast<RTreeNode<T, M, D> *>(root -> child[i]));
			}
		}
	}

	virtual ~RTree();
};

#include "Source/RTree.cpp"

}

#endif
