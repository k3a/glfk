/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_array);
    PrintGLError("creating VAO");
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_array);
    PrintGLError("deleting VAO");
}

VertexArray& VertexArray::Bind()
{
    glBindVertexArray(_array);
    PrintGLError("binding VAO");
    return *this;
}
void VertexArray::BindNone()
{
    glBindVertexArray(0);
    PrintGLError("binding 0 VAO");
}

VertexArray& VertexArray::EnableAttribArray(GLuint index, bool enable)
{
    GLFK_AUTO_BIND();
    if (enable) {
        glEnableVertexAttribArray(index);
    } else { 
        glDisableVertexAttribArray(index);
    }
    GLFK_AUTO_UNBIND();		
    PrintGLError("Enabling or disabling vertex attrib array for VAO");
    return *this;
}

void VertexArray::DrawElements(DrawMode mode, GLsizei count, IndicesType type, const GLvoid * indices)
{
    GLFK_AUTO_BIND();
    Renderer::DrawElements(mode, count, type, indices);
    GLFK_AUTO_UNBIND();
}
