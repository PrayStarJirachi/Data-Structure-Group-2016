#ifdef SJTU_FOREST_HPP

#ifndef SJTU_FOREST_CPP
#define SJTU_FOREST_CPP

template<class T, class A, class M>
Forest<T, A, M>::Forest() : size(0) {
}

template<class T, class A, class M>
void Forest<T, A, M>::allocate(Node &x) {
	if (x.p != nullptr) {
		delete x.p;
	}
	x.p = new LCTNode<T, A, M>(++size, T());
}

template<class T, class A, class M>
void Forest<T, A, M>::allocate(Node &x, const T &value) {
	if (x.p != nullptr) {
		delete x.p;
	}
	x.p = new LCTNode<T, A, M>(++size, value);
}

template<class T, class A, class M>
Forest<T, A, M>::Node::Node() : p(nullptr) {
}

template<class T, class A, class M>
Forest<T, A, M>::Node::~Node() {
	delete p;
}

template<class T, class A, class M>
void Forest<T, A, M>::setRoot(const Forest<T, A, M>::Node &u) {
	LCTree<T, A, M>::setRoot(u.p);
}

template<class T, class A, class M>
void Forest<T, A, M>::link(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	LCTree<T, A, M>::link(u.p, v.p);
}

template<class T, class A, class M>
void Forest<T, A, M>::cut(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	LCTree<T, A, M>::cut(u.p, v.p);
}

template<class T, class A, class M>
void Forest<T, A, M>::modify(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v, const T &value) {
	this -> modifyChain(u.p, v.p, value);
}

template<class T, class A, class M>
void Forest<T, A, M>::modify(const Forest<T, A, M>::Node &u, const T &value) {
	this -> modifySubtree(u.p, value);
}

template<class T, class A, class M>
T Forest<T, A, M>::query(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	return this -> queryChain(u.p, v.p);
}

template<class T, class A, class M>
T Forest<T, A, M>::query(const Forest<T, A, M>::Node &u) {
	return this -> querySubtree(u.p);
}

#endif

#endif
