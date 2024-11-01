#include "Exception.h"
#include <sstream>

SpecialException::SpecialException(int line, const char* file) noexcept : line(line), file(file){}

const char* SpecialException::what() const noexcept {
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	//we use this whatBuffer to keep a pointer to this string, oss will be destroyed at the end of the function
	return whatBuffer.c_str();
}

const char* SpecialException::GetType() const noexcept {
	return "Custom Exception";
}

int SpecialException::GetLine() const noexcept {
	return line;
}

const std::string& SpecialException::GetFile() const noexcept {
	return file;
}

std::string SpecialException::GetOriginString() const noexcept {
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}