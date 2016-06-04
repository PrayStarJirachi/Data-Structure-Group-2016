#ifdef SJTU_RTREE_HPP

#ifndef SJTU_RTREE_CPP
#define SJTU_RTREE_CPP

template<class T, size_t M, size_t D>
void RTree<T, M, D>::__find(const RTreeNode<T, M, D> * const x, const HyperBound<D> &bound, std::vector<T> &storge)const {
	if (x -> level == 0) {
		for (int i = 0; i < x -> size; i++) {
			const std::pair<HyperBound<D>, T> * const now = static_cast<const std::pair<HyperBound<D>, T> * const>(x -> child[i]);
			if (bound.isOverLap(now -> first)) {
				storge.push_back(now -> second);
			}
		}
		return;
	}
	for (int i = 0; i < x -> size; i++) {
		const RTreeNode<T, M, D> * const son = static_cast<const RTreeNode<T, M, D> * const>(x -> child[i]);
		if (bound.isOverLap(son -> box)) {
			__find(son, bound, storge);
		}
	}
}

template<class T, size_t M, size_t D>
std::vector<T> RTree<T, M, D>::getPointSet(const HyperBound<D> &bound)const {
	static std::vector<T> ret;
	ret.clear();
	__find(root, bound, ret);
	return ret;
}

template<class T, size_t M, size_t D>
RTree<T, M, D>::RTree() {
	root = new RTreeNode<T, M, D>();
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::__clear(RTreeNode<T, M, D> *now) {
	if (now -> level > 0) {
		for (int i = 0; i < now -> size; i++) {
			__clear(static_cast<RTreeNode<T, M, D> *>(now -> child[i]));
		}
	}
	delete now;
	now = NULL;
}

template<class T, size_t M, size_t D>
RTree<T, M, D>::~RTree() {
	__clear(root);
}

template<class T, size_t M, size_t D>
RTreeNode<T, M, D> * RTree<T, M, D>::splitNode(RTreeNode<T, M, D>* u) {
	RTreeNode<T, M, D> *tmp[2];
	tmp[0] = new RTreeNode<T, M, D>(*u);
	tmp[1] = new RTreeNode<T, M, D>(*u);
	tmp[0]->size = 0;
	tmp[1]->size = 0;
	pickSeeds(u, tmp[0], tmp[1]);
	
	while (u->size > 0) {
		if (tmp[0]->size > tmp[1]->size) {
			std::swap(tmp[0], tmp[1]);
		}
		if (tmp[0]->size + u->size <= M) {
			for (int i = 0; i < u->size; i ++) {
				tmp[0]->append(u->child[i], u->level > 0);
			}
			break;
		}
		pickNext(u, tmp[0], tmp[1]);
	}
	(*u) = *tmp[0];
	if (u -> level > 0) {
		for (int i = 0; i < u->size; i ++) {
			static_cast<RTreeNode<T, M, D> *>(u->child[i])->father = u;
		}
	}
	return tmp[1];
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::pickSeeds(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *t0, RTreeNode<T, M, D> *t1) {
	std::pair<int, int> tmp = std::make_pair(-1, -1);
	double max = -1;
	for (int i = 0; i < u->size; i ++) {
		for (int j = i + 1; j < u->size; j ++) {
			if (u -> level == 0) {
				auto pi = static_cast<std::pair<HyperBound<D>, T> *>(u->child[i]);
				auto pj = static_cast<std::pair<HyperBound<D>, T> *>(u->child[j]);
				if (std::abs(pi->first.area() - pj->first.area()) > max) {
					max = std::abs(pi->first.area() - pj->first.area());
					tmp = std::make_pair(i, j);
				}
			} else {
				auto pi = static_cast<RTreeNode<T, M, D> *>(u->child[i]);
				auto pj = static_cast<RTreeNode<T, M, D> *>(u->child[j]);
				if (std::abs(pi->box.area() - pj->box.area()) > max) {
					max = std::abs(pi->box.area() - pj->box.area());
					tmp = std::make_pair(i, j);
				}
			}
		}
	}
	t0->append(u->child[tmp.first], u -> level > 0);
	t1->append(u->child[tmp.second], u -> level > 0);
	u->remove(u->child[tmp.second]);
	u->remove(u->child[tmp.first]);
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::pickNext(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *t0, RTreeNode<T, M, D> *t1) {
	t0->update();
	t1->update();
	
	std::pair<int, RTreeNode<T, M, D> *> best;
	int max = -1;
	for (int i = 0; i < u->size; i ++) {
		double delta[2];
		if (u -> level > 0) {
			auto tmp = static_cast<RTreeNode<T, M, D> *>(u->child[i]);
			delta[0] = (t0->box + tmp->box).area() - t0->box.area();
			delta[1] = (t1->box + tmp->box).area() - t1->box.area();
		} else {
			auto tmp = static_cast<std::pair<HyperBound<D>, T> *>(u->child[i]);
			delta[0] = (t0->box + tmp->first).area() - t0->box.area();
			delta[1] = (t1->box + tmp->first).area() - t1->box.area();
		}
		if (delta[0] > max && t0->size < M) {
			max = delta[0];
			best = std::make_pair(i, t0);
		}
		if (delta[1] > max && t1->size < M) {
			max = delta[1];
			best = std::make_pair(i, t1);
		}
	}
	best.second->append(u->child[best.first], u->level > 0);
	u->remove(u->child[best.first]);
}

template<class T, size_t M, size_t D>
RTreeNode<T, M, D> * RTree<T, M, D>::chooseLeaf(const HyperBound<D> &key, const T &value) {
	RTreeNode<T, M, D> *u = root;
	while (true) {
		if (u->level == 0) {
			return u;
		}
		RTreeNode<T, M, D> *v = nullptr;
		double max = -DBL_MAX;
		for (int i = 0; i < u->size; i ++) {
			double s = (static_cast<RTreeNode<T, M, D> *>(u->child[i])->box + key).area();
			if (s > max) {
				max = s;
				v = static_cast<RTreeNode<T, M, D> *>(u->child[i]);
			}
		}
		u = v;
	}
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::adjust(RTreeNode<T, M, D> *u, RTreeNode<T, M, D> *brother) {
	if (u == root) {
		if (brother != nullptr) {
			root = new RTreeNode<T, M, D>();
			root->append(u);
			root->append(brother);
			root->level = u->level + 1;
			root->update();
		}
		return ;
	}
	
	RTreeNode<T, M, D> *father = u->father;
	if (brother != nullptr) {
		father->append(brother);
	}
	father->update();
	RTreeNode<T, M, D> *v = nullptr;
	if (father->size > M) {
		v = splitNode(father);
	}
	adjust(father, v);
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::insert(const HyperBound<D> &key, const T &value, bool flag) {
	RTreeNode<T, M, D> *target = chooseLeaf(key, value);
	
	target->child[target->size ++] = new std::pair<HyperBound<D>, T>(key, value);
	target->update();
	
	RTreeNode<T, M, D> *v = nullptr;
	if (target->size > M) {
		v = splitNode(target);
	}
	adjust(target, v);
}

template<class T, size_t M, size_t D>
RTreeNode<T, M, D> * RTree<T, M, D>::Find_Leaf_Exist(const HyperBound<D> &key, RTreeNode<T, M, D> *t)
{
	if(!(t -> level))
	{
		std::pair<HyperBound<D>, T> *X;
		for(int i = 0; i < t -> size; i++)
		{
			X = static_cast<std::pair<HyperBound<D>, T>* >(t -> child[i]);
			if(X -> first == key) 
				return t;
		}
		return NULL;
	}
	else
	{
		HyperBound<D> Y;
		RTreeNode<T, M, D> *P;
		for(int i = 0; i < t -> size; i++)
		{
			P = static_cast<RTreeNode<T, M, D> *>(t -> child[i]);
			Y = P -> box;
			if(key.inside(Y))
			{
				RTreeNode<T, M, D> *Z;
				Z = Find_Leaf_Exist(key, P);
				if(Z != NULL)
				{
					return Z;
				}
			}
		}
	}
}

template<class T, size_t M, size_t D>
void RTree<T, M, D>::CondenseTree(RTreeNode<T, M, D> *t, std::vector<RTreeNode<T, M, D> *> &Q)
{
	if(t != root)
	{
		RTreeNode<T, M, D> *parent = t -> father;
		int p;
		RTreeNode<T, M, D> *Y;
		for(p = 0; p < parent -> size; p++)
		{
			Y = static_cast<RTreeNode<T, M, D> *>(parent -> child[p]);
			if(Y == t)
				break;
		}
		if(t -> size < (M >> 1))
		{
			for(int j = p; j < (parent -> size) - 1; j++)
			{
				parent -> child[j] = parent -> child[j + 1];
			}
			--(parent -> size);
			Q.push_back(t);
		}
		else
		{
			Y = static_cast<RTreeNode<T, M, D> *>(parent -> child[0]);
			parent -> box = Y -> box;
			for(int i = 1; i < parent -> size; i++)
			{
				Y = static_cast<RTreeNode<T, M, D> *>(parent -> child[i]);
				parent -> box = parent -> box + Y -> box;
			}
		}
		CondenseTree(parent, Q);
	} else
	if(t == root && Q.size() > 0)
	{
		int len = Q.size();
		for(int i = 0; i < len; i++)
		{
			if(!(Q[i] -> level))
			{
				std::pair<HyperBound<D>, T> *X;
				for(int j = 0; j < Q[i] -> size; j++)
				{
					X = static_cast<std::pair<HyperBound<D>, T> *>(Q[i] -> child[j]);
					insert(X -> first, X -> second);
				}
			}
		}
		for(int i = 0; i < len; i++)
		{
			delete Q[i];
		}
	}
}

template<class T, size_t M, size_t D>
bool RTree<T, M, D>::remove(const HyperBound<D> &key)
{
	RTreeNode<T, M, D> *P;
	P = Find_Leaf_Exist(key, root);
	if(P == NULL)
		return false;
	
	int p;
	std::pair<HyperBound<D>, T> *X;
	for(p = 0; p < P -> size; p++)
	{
		X = static_cast<std::pair<HyperBound<D>, T>* >(P -> child[p]);
		if(X -> first == key)
			break;
	}
	
	delete X;
	for(int i = p; i < (P -> size) - 1; i++)
	{
		P -> child[i] = P -> child[i + 1];
	}
	--(P -> size);
	
	std::vector<RTreeNode<T, M, D> *> Q;
	CondenseTree(P, Q);

	while (root -> size == 1 && root -> level != 0)
	{
		RTreeNode<T, M, D> *U = root;
		root = static_cast<RTreeNode<T, M, D> *>(root -> child[0]);
		delete U;
	}
	
	return true;
		
}

#endif

#endif
