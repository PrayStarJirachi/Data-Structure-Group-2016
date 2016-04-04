#ifndef SJTU_BPLUSNODE_HPP
#define SJTU_BPLUSNODE_HPP

#include "BPlusBase.hpp"
#include "BPlusIO.hpp"

namespace sjtu{

template<int M>
class BPlusTree;

template<int M>
class BPlusNode : public BPlusBase{
friend class BPlusTree<M>;
private:
	int nChild, key[M];
	long child[M];
	bool isLeaf;
	BPlusNode(const long &child, const BPlusNode<M> &rhs);

public:
	BPlusNode();
	
};

#include "Implementation/BPlusNode.hpp"

}
#endif
