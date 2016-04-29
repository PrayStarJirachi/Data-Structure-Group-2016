#ifndef SJTU_AUXTREE_HPP
#define SJTU_AUXTREE_HPP

#include "AuxNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class LCTNode;

template<class T, class A, class M>
class AuxTree{
friend class LCTNode<T, A, M>;
private:	
	AuxNode<T, A, M> *root;
	int size;
	void LL(AuxNode<T, A, M>* &t);
	void RR(AuxNode<T, A, M>* &t);
	AuxNode<T, A, M>* Treap_find(const int &key, AuxNode<T, A, M>* t);
	void Treap_Insert(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t);
	void Treap_Delete(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t);
	void Treap_Clear(const AuxNode<T, A, M>* t);
	
public:	
	AuxTree() : root(nullptr), size(0) {}
	AuxNode<T, A, M>* find(const AuxNode<T, A, M> &rhs);
	void insert(const AuxNode<T, A, M> &rhs);
	void erase(const AuxNode<T, A, M> &rhs);
	AuxNode<T, A, M>* getroot(){
		return root;
	}
	size_t getSize() {
		return root == nullptr ? 0 : root -> size;
	}
	size_t getSum() {
		return root == nullptr ? T() : root -> sum;
	}
	void makeDelta(const T &value) {
		if (root != nullptr) {
			root -> makeTagTree(value);
		}
	}
	~AuxTree(){
		if(root != nullptr) Treap_Clear(root);
	} 
	
};

#include "source/AuxTree.cpp"

}

#endif
