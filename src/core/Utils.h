/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include <string>

/// Read the whole file into a string
std::string ReadFile(const char* path);

/// Convert GL error code to stirng
const char* GLErrorToString(unsigned error);

#ifdef DEBUG
/// Check for GL error and print it
# define PrintGLError(where) PrintGLErrorImpl(where " (" __FILE__ ")")
void PrintGLErrorImpl(const char* where);
# ifdef WIN32
#  include <intrin.h>
#  define DebugBreak() __debugbreak()
# else
#  include <signal.h>
#  define DebugBreak() raise(SIGSTOP)
# endif
#else
# define PrintGLError(where)
# define DebugBreak()
#endif

/// For marking classes as non-copyable.
/// This is useful if a class holds data which can't be duplicated in a copy.
class NoCopy
{
protected:
    NoCopy(){};

private:
    NoCopy(const NoCopy& other);
};

#define GLFK_PACKED __attribute__((packed))
