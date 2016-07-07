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

void PrintGLError(const char* where)
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
    
    if(error == GL_NO_ERROR)
        printf("GL error during %s: GL_NO_ERROR: No error has been recorded.\n", where);
    else if(error == GL_INVALID_ENUM)
        printf("GL error during %s: GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.\n", where);
    else if(error == GL_INVALID_VALUE)
        printf("GL error during %s: GL_INVALID_VALUE: A numeric argument is out of range.\n", where);
    else if(error == GL_INVALID_OPERATION)
        printf("GL error during %s: GL_INVALID_OPERATION: The specified operation is not allowed in the current state.\n", where);
    else if(error == GL_OUT_OF_MEMORY)
        printf("GL error during %s: GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.\n", where);
    else
        printf("GL error during %s: Unknown OpenGL Error Code!\n", where);
}

