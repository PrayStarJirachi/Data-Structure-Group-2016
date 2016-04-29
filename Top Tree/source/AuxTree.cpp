#ifdef SJTU_AUXTREE_HPP

#ifndef SJTU_AUXTREE_CPP
#define SJTU_AUXTREE_CPP

// pay attention to srand(timd(NULL)) !!!

template<class T, class A, class M>
void AuxTree<T, A, M> :: LL(AuxNode<T, A, M>* &t){
	AuxNode<T, A, M>* k = t -> child[1];
	k -> pushTagTree();
	t -> child[1] = k -> child[0]; 
	k -> child[0] = t;
	t -> update();
	k -> update();
	t = k;
}

template<class T, class A, class M>	
void AuxTree<T, A, M> :: RR(AuxNode<T, A, M>* &t){
	AuxNode<T, A, M>* k = t -> child[0];
	k -> pushTagTree();
	t -> child[0] = k -> child[1];
	k -> child[1] = t;
	t -> update();
	k -> update();
	t = k;
}

template<class T, class A, class M>
AuxNode<T, A, M>* AuxTree<T, A, M> :: Treap_find(const int &key, AuxNode<T, A, M>* t) {
	if(t == NULL) return NULL;
	t -> pushTagTree();
	if(key < (t -> data -> id)) return Treap_find(key, t -> child[0]); else
	if(key > (t -> data -> id)) return Treap_find(key, t -> child[1]); else
	return t;
}

template<class T, class A, class M>
AuxNode<T, A, M>* AuxTree<T, A, M> :: find(const AuxNode<T, A, M> &rhs) {
	int Key = rhs.data -> id;
	return Treap_find(Key, root);
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: Treap_Insert(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t) {
	if(t == NULL){
		t = new AuxNode<T, A, M>(rhs.data, rand());
		t -> update();
		return;
	}
	t -> pushTagTree();
	if(rhs.data -> id < (t -> data -> id)){
		Treap_Insert(rhs, t -> child[0]);
		if((t -> child[0] -> getrand()) < (t -> getrand())) RR(t);
	}
	else{
		Treap_Insert(rhs, t -> child[1]);
		if((t -> child[1] -> getrand()) < (t -> getrand())) LL(t);
	}
	t -> update();
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: insert(const AuxNode<T, A, M> &rhs) {
	if(find(rhs) != NULL) throw "This ID exist!";
	Treap_Insert(rhs, root);
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: Treap_Delete(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t) {
	t -> pushTagTree();
	if((t -> data -> id) == (rhs.data -> id)){
		if(t -> child[0] == NULL || t -> child[1] == NULL){
			AuxNode<T, A, M>* k = t;
			if(t -> child[0] != NULL)
				t = t -> child[0];
			else 
				t = t -> child[1];
			delete k;
		}
		else{
			if((t -> child[0] -> getrand()) < (t -> child[1] -> getrand())){
				RR(t); 
				Treap_Delete(rhs, t -> child[1]);
				t -> update();
			}
			else{
				LL(t);
				Treap_Delete(rhs, t -> child[0]);
				t -> update();
			}
		}
		return;
	}
	if((rhs.data -> id) < (t -> data -> id)) 
		Treap_Delete(rhs, t -> child[0]);
	else 
		Treap_Delete(rhs, t -> child[1]);
	t -> update();
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: erase(const AuxNode<T, A, M> &rhs) {
	if(find(rhs) == NULL) throw "This ID doesn't exist!";
	Treap_Delete(rhs, root);
}

template<class T, class A, class M>
void AuxTree<T, A, M> :: Treap_Clear(const AuxNode<T, A, M>* t) {
	if(t -> child[0] != NULL) Treap_Clear(t -> child[0]);
	if(t -> child[1] != NULL) Treap_Clear(t -> child[1]);
	delete t;
}

#endif

#endif
