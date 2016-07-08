/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"

/// Vertex Array Object (VAO)
class VertexArray : public GLObject
{
public:
    VertexArray();

    VertexArray& Bind();
    static void BindNone();
    VertexArray& Unbind(){ BindNone(); return *this; };

    /// Enables the specified attribute array
    VertexArray& EnableAttribArray(GLuint index, bool enable=true);
    /// Enable attribute array and set array pointer
    VertexArray& SetAttribPointer(GLuint index, GLint size, AttribType::E type,
                                  bool normalized = false, GLsizei stride = 0, const GLvoid * pointer = NULL);
    
    VertexArray& DrawElements(DrawMode::E mode, GLsizei count, IndicesType::E type, const GLvoid * indices = NULL);
    VertexArray& DrawArrays(DrawMode::E mode, GLint first, GLsizei count);
    
private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static GLuint s_boundArray;
#endif
};
