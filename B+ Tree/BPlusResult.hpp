#ifndef SJTU_BPLUSRESULT_HPP
#define SJTU_BPLUSRESULT_HPP

namespace sjtu{

struct BPlusResult{
	long filePosition;
	bool exist;
	BPlusResult() {}
	explicit BPlusResult(const bool &exist, const long &filePosition);
	operator const long & ()const;
};

#include "Implementation/BPlusResult.hpp"

}
#endif
