#ifndef SJTU_LCTREE_HPP
#define SJTU_LCTREE_HPP

#include <vector>
#include <algorithm>
#include "TBase.hpp"
#include "LCTNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class LCTree : public TBase<T, A, M>{
private:
	LCTNode<T, A, M>* access(LCTNode<T, A, M> *u);
	static void insert(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	static void remove(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	static bool isSplayRoot(LCTNode<T, A, M> *u);

protected:
	static void rotate(LCTNode<T, A, M> *u, int c);
	static void zig(LCTNode<T, A, M> *u);
	static void zag(LCTNode<T, A, M> *u);
	static LCTNode<T, A, M>* getSplayRoot(LCTNode<T, A, M> *u);
	static void splay(LCTNode<T, A, M> *u);
	void link(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void cut(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void modifyChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v, const T &value);
	T queryChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void modifySubtree(LCTNode<T, A, M> *u, const T &value);
	T querySubtree(LCTNode<T, A, M> *u);
	LCTNode<T, A, M> * setRoot(LCTNode<T, A, M> *u);

};

#include "source/LCTree.cpp"

}

#endif
