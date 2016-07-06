#pragma once

#include <string>

/// Read the whole file into a string
std::string ReadFile(const char* path);

#ifdef DEBUG
/// Check for GL error and print it
void PrintGLError(const char* where);
#else
# define PrintGLError(where)
#endif

/// For marking classes as non-copyable.
/// This is useful if a class holds data like GL objects which can't be duplicated in a copy.
class NoCopy
{
protected:
	NoCopy(){};

private:
	NoCopy(const NoCopy& other);
};
