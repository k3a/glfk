/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Utils.h"
#include "Renderer.h"

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

std::string ReadFile(const char* path)
{
    struct stat st;
    FILE* fp;
    char* buf;
    std::string outBuff;

    if ((fp = fopen(path, "rb")) == NULL) {
        return "";
    }

    stat(path, &st);
    
    buf = (char*) malloc(st.st_size);
    fread(buf, 1, st.st_size, fp);
    fclose(fp);
    buf[st.st_size] = '\0';

    outBuff = std::string(buf, st.st_size+1);

    return outBuff;
}

const char* GLErrorToString(unsigned error)
{
    if(error == GL_NO_ERROR) {
        return "GL_NO_ERROR: No error has been recorded.";
    } else if(error == GL_INVALID_ENUM) {
        return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
    } else if(error == GL_INVALID_VALUE) {
        return "GL_INVALID_VALUE: A numeric argument is out of range.\n";
    } else if(error == GL_INVALID_OPERATION) {
        return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
    } else if(error == GL_OUT_OF_MEMORY) {
        return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
    } else if(error == GL_INVALID_FRAMEBUFFER_OPERATION) {
        return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
    } else {
        static char buff[32];
        sprintf(buff, "0x%X", error);
        return buff;
    }
}

void PrintGLErrorImpl(const char* where)
{
#ifndef DEBUG
    return;
#endif
	
    static GLenum prevError = 0;
    static const char* prevErrorWhere = NULL;
    GLenum error = glGetError();
    
    if (!error) {
        return; 
    } else if (error == prevError && where == prevErrorWhere) {
        return; // don't display the same error more times
    }
    
    prevError = error;
    prevErrorWhere = where;
    
    printf("GL error during %s: %s\n", where, GLErrorToString(error));
}

