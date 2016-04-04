template<int M>
void BPlusTree<M>::load() {
	io.load(root);
}

template<int M>
void BPlusTree<M>::init() {
	io.init(root);
}

template<int M>
BPlusTree<M>::BPlusTree(const char *path) : io(path) {
}

template<int M>
BPlusTree<M>::~BPlusTree() {
}

template<int M>
BPlusResult BPlusTree<M>::find(const int &key) {
	long pCur = root;
	BPlusNode<M> curNode;
	do{
		io.read(pCur, curNode);
		int it = curNode.nChild - 1;
		for (; it > 0 && key < curNode.key[it]; it--);
		if (curNode.isLeaf && key == curNode.key[it]) {
			return BPlusResult(true, curNode.child[it]);
		}
		pCur = curNode.child[it];
	}
	while (!curNode.isLeaf);
	return BPlusResult(false, 0);
}

template<int M>
void BPlusTree<M>::split(BPlusNode<M> &father, BPlusNode<M> &curNode, const int &childId, const int &key) {
	BPlusNode<M> newNode;
	long pNew = io.alloc(newNode);
	for (int i = father.nChild; i > childId + 1; i--) {
		father.key[i] = father.key[i - 1];
		father.child[i] = father.child[i - 1];
	}
	father.nChild++;
	int middle = (curNode.nChild >> 1);
	newNode.isLeaf = curNode.isLeaf;
	for (int i = middle; i < curNode.nChild; i++) {
		newNode.child[newNode.nChild] = curNode.child[i];
		newNode.key[newNode.nChild] = curNode.key[i];
		curNode.key[i] = 0;
		curNode.child[i] = 0;
		newNode.nChild++;
	}
	curNode.nChild = middle;
	father.key[childId + 1] = newNode.key[0];
	father.child[childId + 1] = pNew;
	io.write(pNew, newNode);
}

template<int M>
void BPlusTree<M>::insert(const int &key, const long &value) {
	BPlusNode<M> curNode;
	io.read(root, curNode);
	if (curNode.nChild == M) {
		BPlusNode<M> newNode(root, curNode);
		long pNew = io.alloc(newNode);
		io.write(pNew, newNode);
		split(newNode, curNode, 0, key);
		io.write(root, curNode);
		root = pNew;
		curNode = newNode;
		io.setRoot(root);
	}
	insert(curNode, key, value);
	io.write(root, curNode);
}

template<int M>
void BPlusTree<M>::insert(BPlusNode<M> &curNode, const int &key, const long &value) {
	int it = std::max(0, curNode.nChild - 1);
	for (; it > 0 && curNode.key[it] > key; it--);
	if (curNode.isLeaf) {
		if (it < curNode.nChild && curNode.key[it] == key) {
			throw BPlusError("Existed key.");
		}
		if (it < curNode.nChild && curNode.key[it] < key) it++;
		for (int i = curNode.nChild; i > it; i--) {
			curNode.key[i] = curNode.key[i - 1];
			curNode.child[i] = curNode.child[i - 1];
		}
		curNode.nChild++;
		curNode.key[it] = key;
		curNode.child[it] = value;
		return;
	}
	BPlusNode<M> nextNode;
	io.read(curNode.child[it], nextNode);
	if (nextNode.nChild == M) {
		split(curNode, nextNode, it, key);
		if (it + 1 < curNode.nChild && key > curNode.key[it + 1]) {
			io.write(curNode.child[it], nextNode);
			it++;
			io.read(curNode.child[it], nextNode);
		}
	}
	insert(nextNode, key, value);
	io.write(curNode.child[it], nextNode);
	curNode.key[it] = nextNode.key[0];
}

template<int M>
BPlusNode<M> BPlusTree<M>::find(long pCur, const int &key) {
	BPlusNode<M> curNode;
	do{
		io.read(pCur, curNode);
		int it = curNode.nChild - 1;
		for (; it > 0 && key < curNode.key[it]; it--);
		if (curNode.isLeaf && key == curNode.key[it]) {
			return curNode;
		}
		pCur = curNode.child[it];
	}
	while (!curNode.isLeaf);
	return curNode;
}

template<int M>
void BPlusTree<M>::remove(const int &key){
	BPlusResult T = find(key);
	if(!T.exist) throw BPlusError("The key doesn't exist.");
	
	erase(root, key);
	
	BPlusNode<M> rot;
	io.read(root, rot);
	
	if(!rot.isLeaf && rot.nChild == 1) {
		rot.nChild = 0;
		io.write(root, rot);
		root = rot.child[0];
		io.setRoot(root);
	}
}

template<int M>
void BPlusTree<M>::erase(const long &w, const int &key) {
	int i;
	
	BPlusNode<M> x;
	io.read(w, x);
	
	for (i = 0; i + 1 < x.nChild && key >= x.key[i + 1]; i ++);
	
	if (i < x.nChild && key == x.key[i]) {
		if(!x.isLeaf) {
			BPlusNode<M> son;
			io.read(x.child[i], son);
			
			if(son.isLeaf) {
				if(son.nChild > (M >> 1)){
					son.nChild--;
					for(int j = 0; j < son.nChild; j++){
						son.key[j] = son.key[j + 1];
						son.child[j] = son.child[j + 1];
					}
					x.key[i] = son.key[0];
					io.write(w, x);
					io.write(x.child[i], son);
					return;
				}
				else {
					if(i > 0){
						BPlusNode<M> lson;
						io.read(x.child[i - 1], lson);
						if(lson.nChild > (M >> 1)){
							lson.nChild--;
							son.key[0] = lson.key[lson.nChild];
							son.child[0] = lson.child[lson.nChild];
							x.key[i] = son.key[0];
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i - 1], lson);
							return;
						}
						else {
							for(int j = 1; j < son.nChild; j++){
								lson.key[lson.nChild] = son.key[j];
								lson.child[lson.nChild++] = son.child[j];
							}
							son.nChild = 0;
							io.write(x.child[i], son);
							
							for(int j = i; j < x.nChild - 1; j++){
								x.key[j] = x.key[j + 1];
								x.child[j] = x.child[j + 1];
							}
							x.nChild--;
							
							io.write(w, x);
							io.write(x.child[i - 1], lson);
							return;
						}
					}
					else if(i < x.nChild - 1){
						BPlusNode<M> rson;
						io.read(x.child[i + 1], rson);
						if(rson.nChild > (M >> 1)){
							x.key[i + 1] = rson.key[1];
							son.key[son.nChild] = rson.key[0];
							son.child[son.nChild++] = rson.child[0];
							for(int j = 0; j < rson.nChild - 1; j++){
								rson.key[j] = rson.key[j + 1];
								rson.child[j] = rson.child[j + 1];
							}
							rson.nChild--;
							
							x.key[i] = son.key[1];
							for(int j = 0; j < son.nChild - 1; j++){
								son.key[j] = son.key[j + 1];
								son.child[j] = son.child[j + 1];
							}
							son.nChild--;
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i + 1], rson);
							return;
						}
						else {
							for(int j = 0; j < rson.nChild; j++){
								son.key[son.nChild] = rson.key[j];
								son.child[son.nChild++] = rson.child[j];
							}
							rson.nChild = 0;
							io.write(x.child[i + 1], rson);
							
							for(int j = i + 1; j < x.nChild - 1; j++){
								x.key[j] = x.key[j + 1];
								x.child[j] = x.child[j + 1];
							}
							x.nChild--;
							
							for(int j = 0; j < son.nChild - 1; j++){
								son.key[j] = son.key[j + 1];
								son.child[j] = son.child[j + 1];
							}
							son.nChild--;
							x.key[i] = son.key[0];
							
							io.write(w, x);
							io.write(x.child[i], son);
							return;
						}
					}
					else {
						for(int j = 0; j < son.nChild - 1; j++){
							son.key[j] = son.key[j + 1];
							son.child[j] = son.child[j + 1];
						} 
						son.nChild--;
						x.key[i] = son.key[0];
						
						io.write(w, x);
						io.write(x.child[i], son);
						return;
					}
				}
			}
			else {
				BPlusNode<M> P = find(w, key);
				
				x.key[i] = P.key[1];
				io.write(w, x);
				
				if(son.nChild > (M >> 1)){
					erase(x.child[i], key);
					return;
				} 
				else { 
					if(i > 0){
						BPlusNode<M> lson;
						io.read(x.child[i - 1], lson);
						
						if(lson.nChild > (M >> 1)){
							for(int j = son.nChild; j > 0; j--){
								son.key[j] = son.key[j - 1];
								son.child[j] = son.child[j - 1];
							}
							lson.nChild--;
							son.key[0] = lson.key[lson.nChild];
							son.child[0] = lson.child[lson.nChild];
							son.nChild++;
							x.key[i] = son.key[0];
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i - 1], lson);
							
							erase(x.child[i], key);
							return;
						}
						else {
							for(int j = 0; j < son.nChild; j++){
								lson.key[lson.nChild] = son.key[j];
								lson.child[lson.nChild++] = son.child[j];
							}
							
							son.nChild = 0;
							io.write(x.child[i], son);
							
							for(int j = i; j < x.nChild - 1; j++){
								x.key[j] = x.key[j + 1];
								x.child[j] = x.child[j + 1];
							} 
							x.nChild--;
							
							io.write(w, x);
							io.write(x.child[i - 1], lson);
							
							erase(x.child[i - 1], key);
							return;
						}
					} else 
					if(i < x.nChild - 1){
						BPlusNode<M> rson;
						io.read(x.child[i + 1], rson);
						
						if(rson.nChild > (M >> 1)){
							son.key[son.nChild] = rson.key[0];
							son.child[son.nChild++] = rson.child[0];
							
							
							for(int j = 0; j < rson.nChild - 1; j++){
								rson.key[j] = rson.key[j + 1];
								rson.child[j] = rson.child[j + 1];
							}
							rson.nChild--;
							x.key[i + 1] = rson.key[0];
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i + 1], rson);
							
							erase(x.child[i], key);
							return;
						}
						else {
							for(int j = 0; j < rson.nChild; j++){
								son.key[son.nChild] = rson.key[j];
								son.child[son.nChild++] = rson.child[j];
							}
							
							rson.nChild = 0;
							io.write(x.child[i + 1], rson);
							
							for(int j = i + 1; j < x.nChild - 1; j++){
								x.key[j] = x.key[j + 1];
								x.child[j] = x.child[j + 1];
							} 
							x.nChild--;
							
							io.write(w, x);
							io.write(x.child[i], son);
							
							erase(x.child[i], key);
							return;
						}
					}
					else {
						erase(x.child[i], key);
						return; 
					}
				}
			}
		}
		else {
			//printf("--------------------------------------------\n");
			for(int j = i; j < x.nChild - 1; j++){
				x.key[j] = x.key[j + 1];
				x.child[j] = x.child[j + 1];
			}
			x.nChild--;
			io.write(w, x);
			return;
		}
	} else {
		if (!x.isLeaf) {
			BPlusNode<M> son;
			io.read(x.child[i], son);
			
			if (!son.isLeaf) {
				if (son.nChild > M / 2) {
					//H
				} else {
					if (i > 0) {
						BPlusNode<M> lson;
						io.read(x.child[i - 1], lson);
						
						if (lson.nChild > M / 2) {
							//I
							for (int j = son.nChild; j > 0; j --) {
								son.child[j] = son.child[j - 1];
								son.key[j] = son.key[j - 1];
							}
							son.child[0] = lson.child[lson.nChild - 1];
							son.key[0] = lson.key[lson.nChild - 1];
							x.key[i] = son.key[0];
							son.nChild ++;
							lson.nChild --;
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i - 1], lson);
						} else {
							//J
							for (int j = 0; j < son.nChild; j ++) {
								lson.child[lson.nChild] = son.child[j];
								lson.key[lson.nChild++] = son.key[j];
							}
							for (int j = i; j + 1 < x.nChild; j ++) {
								x.child[j] = x.child[j + 1];
								x.key[j] = x.key[j + 1];
							}
							x.nChild --;
							
							io.write(w, x);
							io.write(x.child[--i], lson);
						}
					} else {
						BPlusNode<M> rson;
						io.read(x.child[i + 1], rson);
						
						if (rson.nChild > M / 2) {
							//K
							son.child[son.nChild] = rson.child[0];
							son.key[son.nChild++] = rson.key[0];
							
							for (int j = 0; j + 1 < rson.nChild; j ++) {
								rson.child[j] = rson.child[j + 1];
								rson.key[j] = rson.key[j + 1];
							}
							rson.nChild --;
							x.key[i + 1] = rson.key[0];
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i + 1], rson);
						} else {
							//L
							for (int j = 0; j < (int)rson.nChild; j ++) {
								son.child[son.nChild] = rson.child[j];
								son.key[son.nChild++] = rson.key[j];
							}
							for (int j = i + 1; j + 1 < x.nChild; j ++) {
								x.child[j] = x.child[j + 1];
								x.key[j] = x.key[j + 1];
							}
							x.nChild --;
							
							io.write(w, x);
							io.write(x.child[i], son);
						}
					}
				}
			} else {
				if (son.nChild > M / 2) {
					//M
				} else {
					if (i > 0) {
						BPlusNode<M> lson;
						io.read(x.child[i - 1], lson);
						
						if (lson.nChild > M / 2) {
							//N
							for (int j = son.nChild; j > 0; j --) {
								son.child[j] = son.child[j - 1];
								son.key[j] = son.key[j - 1];
							}
							son.child[0] = lson.child[lson.nChild - 1];
							son.key[0] = lson.key[lson.nChild - 1];
							x.key[i] = son.key[0];
							son.nChild ++;
							lson.nChild --;
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i - 1], lson);
						} else {
							//O
							for (int j = 0; j < son.nChild; j ++) {
								lson.child[lson.nChild] = son.child[j];
								lson.key[lson.nChild++] = son.key[j];
							}
							for (int j = i; j + 1 < x.nChild; j ++) {
								x.child[j] = x.child[j + 1];
								x.key[j] = x.key[j + 1];
							}
							x.nChild --;
							
							io.write(w, x);
							io.write(x.child[--i], lson);
						}
					} else {
						BPlusNode<M> rson;
						io.read(x.child[i + 1], rson);
						
						if (rson.nChild > M / 2) {
							//P
							son.child[son.nChild] = rson.child[0];
							son.key[son.nChild++] = rson.key[0];
							
							for (int j = 0; j + 1 < rson.nChild; j ++) {
								rson.child[j] = rson.child[j + 1];
								rson.key[j] = rson.key[j + 1];
							}
							rson.nChild --;
							x.key[i + 1] = rson.key[0];
							
							io.write(w, x);
							io.write(x.child[i], son);
							io.write(x.child[i + 1], rson);
						} else {
							//Q
							for (int j = 0; j < (int)rson.nChild; j ++) {
								son.child[son.nChild] = rson.child[j];
								son.key[son.nChild++] = rson.key[j];
							}
							for (int j = i + 1; j + 1 < x.nChild; j ++) {
								x.child[j] = x.child[j + 1];
								x.key[j] = x.key[j + 1];
							}
							x.nChild --;
							
							io.write(w, x);
							io.write(x.child[i], son);
						}
					}
				}
			}
		}
		erase(x.child[i], key);
	}
}
