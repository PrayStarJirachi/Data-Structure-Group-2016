#ifdef SJTU_LCTREE_HPP

#ifndef SJTU_LCTREE_CPP
#define SJTU_LCTREE_CPP

template<class T, class A, class M>
void LCTree<T, A, M>::insert(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	if (u == nullptr || v == nullptr) return;
	(u -> subtree).insert(AuxNode<T, A, M>(v, rand()));
	u -> update();
}

template<class T, class A, class M>
void LCTree<T, A, M>::remove(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	if (u == nullptr || v == nullptr) return;
	(u -> subtree).erase(AuxNode<T, A, M>(v, rand()));
	u -> update();
}

template<class T, class A, class M>
void LCTree<T, A, M>::rotate(LCTNode<T, A, M> *u, int c) {
	LCTNode<T, A, M> *v = u->father;
	v->child[c] = u->child[c ^ 1];
	if (u->child[c ^ 1] != nullptr) {
		u->child[c ^ 1]->father = v;
	}
	u->father = v->father;
	if (v->father != nullptr) {
		if (v->father->child[0] == v) {
			u->father->child[0] = u;
		} else if (v->father->child[1] == v) {
			u->father->child[1] = u;
		}
	}
	v->father = u;
	u->child[c ^ 1] = v;
	v->update();
	u->update();
}

template<class T, class A, class M>
void LCTree<T, A, M>::zig(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::rotate(u, 0);
}

template<class T, class A, class M>
void LCTree<T, A, M>::zag(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::rotate(u, 1);
}

template<class T, class A, class M>
LCTNode<T, A, M>* LCTree<T, A, M>::getSplayRoot(LCTNode<T, A, M> *u) {
	while (!LCTree<T, A, M>::isSplayRoot(u)) {
		u = u->father;
	}
	return u;
}

template<class T, class A, class M>
bool LCTree<T, A, M>::isSplayRoot(LCTNode<T, A, M> *u) {
	return u->father == nullptr || (u->father->child[0] != u && u->father->child[1] != u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::splay(LCTNode<T, A, M> *u) {
	LCTNode<T, A, M> * uRoot = LCTree<T, A, M>::getSplayRoot(u);
	LCTNode<T, A, M> * tmp = uRoot -> father;
	remove(uRoot->father, uRoot);
	while (!isSplayRoot(u)) {
		LCTNode<T, A, M> *v = u->father;
		if (isSplayRoot(v)) {
			v->pushTagChain();
			u->pushTagChain();
			if (v->child[0] == u) {
				LCTree<T, A, M>::zig(u);
			} else {
				LCTree<T, A, M>::zag(u);
			}
		} else {
			LCTNode<T, A, M> *w = v->father;
			w->pushTagChain();
			v->pushTagChain();
			u->pushTagChain();
			if (w->child[0] == v) {
				if (v->child[0] == u) {
					LCTree<T, A, M>::zig(v);
					LCTree<T, A, M>::zig(u);
				} else {
					LCTree<T, A, M>::zag(u);
					LCTree<T, A, M>::zig(u);
				}
			} else {
				if (v->child[1] == u) {
					LCTree<T, A, M>::zag(v);
					LCTree<T, A, M>::zag(u);
				} else {
					LCTree<T, A, M>::zig(u);
					LCTree<T, A, M>::zag(u);
				}
			}
		}
	}
	insert(u->father, u);
}

template<class T, class A, class M>
LCTNode<T, A, M>* LCTree<T, A, M>::access(LCTNode<T, A, M> *u) {
	static std::vector<LCTNode<T, A, M>*> vec;
	vec.clear();
	LCTNode<T, A, M> *step = u;
	while (step != nullptr) {
		vec.push_back(step);
		step = step->father;
	}
	std::reverse(vec.begin(), vec.end());
	for (auto p : vec) {
		p->pushTagTree();
		p->pushTagChain();
	}
	LCTNode<T, A, M>* v = nullptr;
	for ( ; u != nullptr; u = u->father) {
		LCTree<T, A, M>::splay(u);
		LCTree<T, A, M>::remove(u, v);
		LCTree<T, A, M>::insert(u, u->child[1]);
		u->child[1] = v;
		v = u;
		v->update();
	}
	return v;
}

template<class T, class A, class M>
LCTNode<T, A, M> * LCTree<T, A, M>::setRoot(LCTNode<T, A, M> *u) {
	LCTNode<T, A, M> * tmp = LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	LCTNode<T, A, M> *p = u;
	while (p -> child[0] != nullptr) {
		p = p -> child[0];
	}
	u->makeSwap();
	//LCTree<T, A, M>::splay(u);
	return p;
}

template<class T, class A, class M>
void LCTree<T, A, M>::link(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	u->father = v;
	insert(v, u);
	LCTree<T, A, M>::access(u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::cut(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	v->child[0]->father = nullptr;
	v->child[0] = nullptr;
	v->update();
}

template<class T, class A, class M>
void LCTree<T, A, M>::modifyChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v, const T &value) { 
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	v->makeTagChain(value);
}

template<class T, class A, class M>
T LCTree<T, A, M>::queryChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	return v->sumChain;
}

template<class T, class A, class M>
void LCTree<T, A, M>::modifySubtree(LCTNode<T, A, M> *u, const T &value) {
	LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	u->subtree.makeDelta(value);
	u->data = this -> add(u -> data, value);
}

template<class T, class A, class M>
T LCTree<T, A, M>::querySubtree(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	return this -> add(u->subtree.getSum(), u->data);
}

#endif

#endif
