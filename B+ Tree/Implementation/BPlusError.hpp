BPlusError::BPlusError(const char *message) : errorMessage(message) {
}

const char * BPlusError::getMessage()const {
	return errorMessage;
}

BPlusError::~BPlusError() {
}
