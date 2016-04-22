#ifndef SJTU_TBASE_HPP
#define SJTU_TBASE_HPP

#include <cstddef>
#include <functional>

namespace sjtu{

template<class T, class A, class M>
class TBase{
public:
	TBase();
	virtual ~TBase();

};

#include "source/TBase.cpp"

}

#endif
