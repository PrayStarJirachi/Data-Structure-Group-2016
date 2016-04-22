#ifndef SJTU_TBASE_HPP
#define SJTU_TBASE_HPP

namespace sjtu{

template<class D, class T, class DA, class TA, class M>
class TBase{
protected:
	static DA dataAdd;
	static TA tagAdd;
	static M mult;

public:
	TBase();
	virtual ~TBase();

};

template<class D, class T, class DA, class TA, class M>
DA TBase<D, T, DA, TA, M>::dataAdd;

template<class D, class T, class DA, class TA, class M>
TA TBase<D, T, DA, TA, M>::tagAdd;

template<class D, class T, class DA, class TA, class M>
M TBase<D, T, DA, TA, M>::mult;

#include "source/TBase.cpp"

}

#endif
