#ifndef SJTU_BPLUSTREE_HPP
#define SJTU_BPLUSTREE_HPP

#include "BPlusError.hpp"
#include "BPlusIO.hpp"
#include "BPlusNode.hpp"
#include "BPlusResult.hpp"

namespace sjtu{

template<int M>
class BPlusTree : public BPlusBase{
private:
	BPlusIO<M> io;
	long root;
	//void Delete(int w, const int &key);
	void split(BPlusNode<M> &father, BPlusNode<M> &curNode, const int &childId, const int &key);
	void insert(BPlusNode<M> &curNode, const int &key, const long &value);
	BPlusNode<M> find(long pCur, const int &key);
	void erase(const long &w, const int &key);
	
public:
	BPlusTree(const char *path);
	void load();
	void init();
	void insert(const int &key, const long &value);
	void remove(const int &key);
	BPlusResult find(const int &key);
	virtual ~BPlusTree();
	
};

#include "Implementation/BPlusTree.hpp"

}
#endif
