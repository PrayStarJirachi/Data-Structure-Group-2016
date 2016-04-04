#ifndef SJTU_BPLUSERROR_HPP
#define SJTU_BPLUSERROR_HPP

#include "BPlusBase.hpp"

namespace sjtu{

class BPlusError : public BPlusBase{
private:
	const char *errorMessage;
	
public:
	BPlusError(const char *message);
	const char * getMessage()const;
	virtual ~BPlusError();
	
};

#include "Implementation/BPlusError.hpp"

}
#endif
