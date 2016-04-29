#ifndef SJTU_TBASE_HPP
#define SJTU_TBASE_HPP

#include <cstddef>
#include <functional>

namespace sjtu{

template<class T, class A, class M>
class TBase{
protected:
	static A add;
	static M mult;

public:
	TBase();
	virtual ~TBase();

};

template<class T, class A, class M>
A TBase<T, A, M>::add;

template<class T, class A, class M>
M TBase<T, A, M>::mult;

#include "source/TBase.cpp"

}

#endif
