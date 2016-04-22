#ifndef SJTU_LCNODE_HPP
#define SJTU_LCNODE_HPP

#include "TNode.hpp"

template<class D, class T, class DA, class TA, class M>
class LCTree;

template<class D, class T, class DA, class TA, class M>
class AuxTree;

template<class D, class T, class DA, class TA, class M>
class LCNode : TNode<D, T, DA, TA, M>{
friend class LCTree<D, T, DA, TA, M>;
private:
	T tagChain, tagTree;
	AuxTree<D, T, DA, TA, M> subtree;

	void pushdown();
	void update();

public:
	virtual ~LCNode();

};

#include "source/LCNode.hpp"

#endif
