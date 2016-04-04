#ifndef SJTU_BPLUSBASE_HPP
#define SJTU_BPLUSBASE_HPP

#include <cstdio>
#include <cstring>
#include <algorithm>

namespace sjtu{

class BPlusBase{
protected:
	virtual ~BPlusBase();
};

#include "Implementation/BPlusBase.hpp"

}
#endif
