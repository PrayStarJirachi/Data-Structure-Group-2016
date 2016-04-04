template<int M>
BPlusNode<M>::BPlusNode() : nChild(0), isLeaf(true) {
	memset(child, 0, sizeof(child));
	memset(key, 0, sizeof(key));
}

template<int M>
BPlusNode<M>::BPlusNode(const long &son, const BPlusNode<M> &rhs) : nChild(0), isLeaf(false) {
	memset(child, 0, sizeof(child));
	memset(key, 0, sizeof(key));
	child[nChild] = son;
	key[nChild] = rhs.key[0];
	nChild++;
}
