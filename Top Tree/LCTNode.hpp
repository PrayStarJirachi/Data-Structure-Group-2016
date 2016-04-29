#ifndef SJTU_LCTNODE_HPP
#define SJTU_LCTNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class LCTree;

template<class T, class A, class M>
class AuxNode;

template<class T, class A, class M>
class LCTNode : public TNode<T, A, M>{
friend class AuxTree<T, A, M>;
friend class LCTree<T, A, M>;
friend class AuxNode<T, A, M>;
private:
	AuxTree<T, A, M> subtree;
	LCTNode *child[2], *father;
	T tagTree, tagChain, sumChain, sumTree, data;
	bool haveTagTree, haveTagChain, reverse;
	size_t sizeChain, sizeTree;

	void makeTagChain(const T &value);
	void makeTagTree(const T &value);
	void makeSwap();

public:
	const size_t id;

	LCTNode(const size_t &id, const T &value);

	void pushTagTree();
	void pushTagChain();
	void update();

};


#include "source/LCTNode.cpp"

}

#include "AuxTree.hpp"

#endif
