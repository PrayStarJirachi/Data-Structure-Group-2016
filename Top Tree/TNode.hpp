#ifndef SJTU_TNODE_HPP
#define SJTU_TNODE_HPP

#include "TBase.hpp"

namespace sjtu{

template<class T, class A, class M>
class TNode : public TBase<T, A, M>{
public:
	TNode();
	virtual ~TNode();

};

#include "source/TNode.cpp"

}

#endif
