/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"

/// Vertex Array Object (VAO)
class VertexArray : public NoCopy
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray& Bind();
    static void BindNone();
    VertexArray& Unbind(){ BindNone(); return *this; };

    VertexArray& EnableAttribArray(GLuint index, bool enable=true);

private:
    GLuint _array;
};
