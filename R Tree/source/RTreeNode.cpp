#ifdef SJTU_RTREENODE_HPP

#ifndef SJTU_RTREENODE_CPP
#define SJTU_RTREENODE_CPP


template<class T, size_t M, size_t D>
RTreeNode<T, M, D>::RTreeNode() {
	size = level = 0;
	father = nullptr;
}

template<class T, size_t M, size_t D>
RTreeNode<T, M, D>::~RTreeNode() {
	for (int i = 0; i < size; i++) {
		if (level == 0) {
			delete static_cast<std::pair<HyperBound<D>, T> *>(child[i]);
		}
		child[i] = nullptr;
	}
	father = nullptr;
	level = size = 0;
}

template<class T, size_t M, size_t D>
void RTreeNode<T, M, D>::remove(const void *key) {
	for (int i = 0; i < size; i++) {
		if (child[i] == key) {
			for (int j = i; j < size - 1; j++) {
				child[j] = child[j + 1];
			}
			size--;
			break;
		}
	}
}

template<class T, size_t M, size_t D>
void RTreeNode<T, M, D>::append(void *key, bool flag) {
	child[size++] = key;
	if (flag) {
		static_cast<RTreeNode<T, M, D> *>(key) -> father = this;
	}
}

template<class T, size_t M, size_t D>
void RTreeNode<T, M, D>::update() {
	box = HyperBound<D>();
	if (level > 0) {
		for (int i = 0; i < size; i++) {
			box = box + static_cast<RTreeNode<T, M, D> *>(child[i]) -> box;
		}
	} else {
		for (int i = 0; i < size; i++) {
			box = box + static_cast<std::pair<HyperBound<D>, T> *>(child[i]) -> first;
		}
	}
}

#endif

#endif
