#ifndef SJTU_AUXNODE_HPP
#define SJTU_AUXNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class D, class T, class DA, class TA, class M>
class AuxTree;

template<class D, class T, class DA, class TA, class M>
class AuxNode : TNode<D, T, DA, TA, M>{
friend class AuxTree<D, T, DA, TA, M>;
private:
	T tagTree;
	
	void pushdown();
	void update();

public:
	virtual ~AuxNode();

};

#include "source/AuxNode.cpp"

};

#endif
