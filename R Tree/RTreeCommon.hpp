#ifndef SJTU_RTREECOMMON_HPP
#define SJTU_RTREECOMMON_HPP

#include <cstddef>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cstdarg>

namespace sjtu{

struct Bound{
	static const double EPS;

	double lowerBound, upperBound;

	Bound();
	Bound(const double &lB, const double &rB);

	inline static int __dcmp(const double &x);
	inline bool inside(const Bound &rhs)const;

	friend Bound operator +(const Bound &a, const Bound &b) {
		return Bound(std::min(a.lowerBound, b.lowerBound),
				     std::max(a.upperBound, b.upperBound));
	}
	friend bool operator ==(const Bound &a, const Bound &b) {
		return __dcmp(a.lowerBound - b.lowerBound) == 0 &&
		       __dcmp(a.upperBound - b.upperBound) == 0;
	}

};

const double Bound::EPS = 1e-10;

template<size_t M>
class HyperBound{
friend HyperBound<M> operator +(const HyperBound<M> &a, const HyperBound<M> &b) {
	HyperBound<M> ret;
	for (int i = 0; i < M; i++) {
		ret.bounds[i] = a.bounds[i] + b.bounds[i];
	}
	return ret;
}
friend bool operator ==(const HyperBound<M> &a, const HyperBound<M> &b) {
	for (int i = 0; i < M; i++) {
		if (!(a.bounds[i] == b.bounds[i])) {
			return false;
		}
	}
	return true;
}
private:

public:
	Bound bounds[M];
	HyperBound();
	HyperBound(const std::vector<Bound> &rhs);

	double area()const;
	bool isOverLap(const HyperBound<M> &rhs)const;
	bool inside(const HyperBound<M> &rhs)const;

};

#include "source/RTreeCommon.cpp"

}

#endif
