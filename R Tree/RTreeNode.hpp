#ifndef SJTU_RTREENODE_HPP
#define SJTU_RTREENODE_HPP

#include "RTreeCommon.hpp"

namespace sjtu{

template<class T, size_t M, size_t D>
struct RTreeNode{
	HyperBound<D> box;
	void *child[M + 2];
	RTreeNode<T, M, D> *father;
	size_t level, size;

	RTreeNode();
	virtual ~RTreeNode();

	void remove(const void *key);
	void append(void *key, bool flag = true);
	void update();

};

#include "source/RTreeNode.cpp"

}

#endif
