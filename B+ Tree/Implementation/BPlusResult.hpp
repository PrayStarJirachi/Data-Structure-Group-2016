BPlusResult::BPlusResult(const bool &exist, const long &filePosition) : exist(exist), filePosition(filePosition) {
}

BPlusResult::operator const long & ()const {
	return filePosition;
}
