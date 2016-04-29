#ifdef SJTU_AUXNODE_HPP

#ifndef SJTU_AUXNODE_CPP
#define SJTU_AUXNODE_CPP

template<class T, class A, class M>
void AuxNode<T, A, M>::makeTagTree(const T &value) {
	if (!haveTagTree) {
		tagTree = value;
		haveTagTree = true;
	} else {
		tagTree = this -> add(tagTree, value);
	}
	data -> makeTagTree(value);
	sum = this -> add(sum, this -> mult(size, value));
}

template<class T, class A, class M>
void AuxNode<T, A, M>::pushTagTree() {
	if (haveTagTree) {
		haveTagTree = false;
		if (child[0] != nullptr) {
			child[0] -> makeTagTree(tagTree);
		}
		if (child[1] != nullptr) {
			child[1] -> makeTagTree(tagTree);
		}
	}
}

template<class T, class A, class M>
AuxNode<T, A, M>::AuxNode(LCTNode<T, A, M> *data, int Rnd) : tagTree(), size(0), sum(), data(data), rnd(Rnd) {
	father = child[0] = child[1] = nullptr;
	haveTagTree = false;
}

template<class T, class A, class M>
inline int AuxNode<T, A, M>::getrand()const {
	return rnd;
}

template<class T, class A, class M>
void AuxNode<T, A, M>::update() {
	size = data -> sizeTree + data -> sizeChain;
	sum = this -> add(data -> sumTree, data -> sumChain);
	if (child[0] != nullptr) {
		size += child[0] -> size;
		sum = this -> add(sum, child[0] -> sum);
	}
	if (child[1] != nullptr) {
		size += child[1] -> size;
		sum = this -> add(sum, child[1] -> sum);
	}
}

#endif

#endif
