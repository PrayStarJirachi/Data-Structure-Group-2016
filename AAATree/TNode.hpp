#ifndef SJTU_TNODE_HPP
#define SJTU_TNODE_HPP

#include "TBase.hpp"

namespace sjtu{

template<class D, class T, class DA, class TA, class M>
class TNode : TBase<D, T, DA, TA, M>{
protected:
	D data;
	size_t size;
	TNode *child[2], *father;

	virtual void pushdown() = 0;
	virtual void update() = 0;

};

}

#endif
