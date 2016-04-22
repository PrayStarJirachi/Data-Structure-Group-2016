#ifndef SJTU_LCTREE_HPP
#define SJTU_LCTREE_HPP

#include "LCTNode.hpp"
#include "TBase.hpp"

namespace sjtu{

template<class T, class A, class M>
class LCTree : public TBase<T, A, M>{
private:

protected:
	void access(LCTNode<T, A, M> *p);
	void setRoot(LCTNode<T, A, M> *p);

};

#include "source/LCTree.cpp"

}

#endif
