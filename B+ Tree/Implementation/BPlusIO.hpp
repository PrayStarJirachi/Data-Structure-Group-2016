template<int M>
inline void BPlusIO<M>::init(long &root) {
	if (pFile != NULL) fclose(pFile);
	pFile = fopen(path, "wb+");
	if (pFile == NULL) {
		throw BPlusError("Invaild BPlusTree index file.");
	}
	root = sizeof(root);
	fwrite(reinterpret_cast<const char *>(&root), sizeof(root), 1, pFile);
	root = alloc(BPlusNode<M>());
	write(root, BPlusNode<M>());
}

template<int M>
inline void BPlusIO<M>::load(long &root) {
	if (pFile != NULL) {
		fclose(pFile);
	}
	pFile = fopen(path, "rb+");
	if (pFile == NULL) {
		throw BPlusError("Invaild BPlusTree index file.");
	}
	if (fread(reinterpret_cast<char *>(&root), sizeof(root), 1, pFile) != 1) {
		throw BPlusError("Invaild BPlusTree index file.");
	}
}

template<int M>
BPlusIO<M>::BPlusIO(const char *bPath) : path(bPath) {}

template<int M>
BPlusIO<M>::~BPlusIO() {
	if (pFile != NULL) {
		fclose(pFile);
	}
}

template<int M>
inline void BPlusIO<M>::write(const long &offset, const BPlusNode<M> &buffer) {
	fseek(pFile, offset, SEEK_SET);
	fwrite(reinterpret_cast<const char *>(&buffer), sizeof(buffer), 1, pFile);
}

template<int M>
inline void BPlusIO<M>::read(const long &offset, BPlusNode<M> &buffer) {
	fseek(pFile, offset, SEEK_SET);
	if (fread(reinterpret_cast<char *>(&buffer), sizeof(buffer), 1, pFile) != 1) {
		throw BPlusError("Invaild BPlusTree index file.");
	}
}

template<int M>
inline long BPlusIO<M>::alloc(const BPlusNode<M> &buffer) {
	fseek(pFile, 0, SEEK_END);
	return ftell(pFile);
}

template<int M>
inline void BPlusIO<M>::setRoot(const long &root) {
	fseek(pFile, 0, SEEK_SET);
	fwrite(reinterpret_cast<const char *>(&root), sizeof(root), 1, pFile);
}
