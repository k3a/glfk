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
    enum DrawMode {
        POINTS = GL_POINTS,
        LINE_STRIP = GL_LINE_STRIP,
        LINE_LOOP = GL_LINE_LOOP,
        LINES = GL_LINES,
        LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
        LINES_ADJACENCY = GL_LINES_ADJACENCY,
        TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        TRIANGLE_FAN = GL_TRIANGLE_FAN,
        TRIANGLES = GL_TRIANGLES,
        TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
        PATCHES = GL_PATCHES
    };
    
    enum IndicesType {
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        UNSIGNED_INT = GL_UNSIGNED_INT
    };
    
    VertexArray();
    ~VertexArray();

    GLuint GL()const{ return _array; }
    VertexArray& Bind();
    static void BindNone();
    VertexArray& Unbind(){ BindNone(); return *this; };

    VertexArray& EnableAttribArray(GLuint index, bool enable=true);
    
    void DrawElements(DrawMode mode, GLsizei count, IndicesType type, const GLvoid * indices = NULL);

private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static GLuint s_boundArray;
#endif
    
    GLuint _array;
};
