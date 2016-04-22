#ifndef SJTU_LCTNODE_HPP
#define SJTU_LCTNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree;

template<class T, class A, class M>
class LCTNode : public TNode<T, A, M>{
private:
	size_t id;
	T tagTree, tagChain;
	AuxTree<T, A, M> subtree;
	bool reverse;

public:
	LCTNode(const size_t &id);

	void pushdown();
	void update();

};

#include "source/LCTNode.cpp"

}

#endif
