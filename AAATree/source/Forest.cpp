#ifdef SJTU_FOREST_HPP

#ifndef SJTU_FOREST_CPP
#define SJTU_FOREST_CPP

template<class T, class A, class M>
Forest<T, A, M>::Forest() : size(0) {
}

template<class T, class A, class M>
Forest<T, A, M>::~Forest() {
	// TODO
}

template<class T, class A, class M>
void Forest<T, A, M>::link(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	// TODO
}

template<class T, class A, class M>
void Forest<T, A, M>::cut(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	// TODO
}

template<class T, class A, class M>
void Forest<T, A, M>::modify(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v, const T &value) {
	// TODO
}

template<class T, class A, class M>
void Forest<T, A, M>::modify(const Forest<T, A, M>::Node &u, const T &value) {
	// TODO
}

template<class T, class A, class M>
T Forest<T, A, M>::query(const Forest<T, A, M>::Node &u, const Forest<T, A, M>::Node &v) {
	// TODO
}

template<class T, class A, class M>
T Forest<T, A, M>::query(const Forest<T, A, M>::Node &u) {
	// TODO
}

#endif

#endif
