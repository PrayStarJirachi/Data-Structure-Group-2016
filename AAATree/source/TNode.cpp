#ifdef SJTU_TNODE_HPP

#ifndef SJTU_TNODE_CPP
#define SJTU_TNODE_CPP

template<class T, class A, class M>
TNode<T, A, M>::TNode() : size(0), father(nullptr) {
	child[0] = child[1] = nullptr;
}

template<class T, class A, class M>
TNode<T, A, M>::~TNode() {
	// TODO
}

#endif

#endif
