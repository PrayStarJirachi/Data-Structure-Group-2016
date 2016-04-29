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
	friend class Forest<T, A, M>;
	private:
		LCTNode<T, A, M> *p;
	
	public:
		Node();
		Node(const Node &p) = default;
		Node & operator =(const Node &p) = default;

		void allocate();
		void allocate(const T &value = T());

		~Node();

	};

	Forest();

	void allocate(Node &x);
	void allocate(Node &x, const T &value);
	void setRoot(const Node &u);
	void modify(const Node &u, const Node &v, const T &value);
	void modify(const Node &u, const T &value);
	T query(const Node &u, const Node &v);
	T query(const Node &u);
	void link(const Node &u, const Node &v);
	void cut(const Node &u, const Node &v);

};

#include "source/Forest.cpp"

}

#endif
