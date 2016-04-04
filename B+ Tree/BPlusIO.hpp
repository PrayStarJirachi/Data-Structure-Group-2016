#ifndef SJTU_BPLUSIO_HPP
#define SJTU_BPLUSIO_HPP

#include "BPlusError.hpp"
#include "BPlusNode.hpp"
#include "BPlusBase.hpp"

namespace sjtu{

template<int M>
class BPlusIO : public BPlusBase{
private:
	typedef FILE * BPlusFilePointer;
	
	const char *path;
	BPlusFilePointer pFile;
	
public:
	explicit BPlusIO(const char *bPath);
	inline void init(long &root);
	inline void load(long &root);
	inline void setRoot(const long &root);
	inline void write(const long &offset, const BPlusNode<M> &buffer);
	inline void read(const long &offset, BPlusNode<M> &buffer);
	inline long alloc(const BPlusNode<M> &buffer);
	
	virtual ~BPlusIO();
	
};

#include "Implementation/BPlusIO.hpp"

}
#endif
