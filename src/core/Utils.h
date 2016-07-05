#pragma once

#include <string>

std::string ReadFile(const char* path);
void PrintGLError(const char* where);


class NoCopy
{
protected:
	NoCopy(){};

private:
	NoCopy(const NoCopy& other);
};
