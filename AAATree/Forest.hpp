#ifndef SJTU_FOREST_HPP
#define SJTU_FOREST_HPP

#include "LCTree.hpp"

namespace sjtu{

template<class T, class A, class M>
class Forest : public LCTree<T, A, M>{
private:
	size_t size;

public:
	class Node{
	private:
		LCTNode<T, A, M> *p;
	
	public:
		Node();

	};

	Forest();
	~Forest();

	Node createTree();
	void link(const Node &u, const Node &v);
	void cut(const Node &u, const Node &v);
	void modify(const Node &u, const Node &v, const T &value);
	void modify(const Node &u, const T &value);
	T query(const Node &u, const Node &v);
	T query(const Node &u);

};

#include "source/Forest.cpp"

}

#endif
