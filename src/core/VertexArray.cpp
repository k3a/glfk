/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "VertexArray.h"

#ifdef GLFK_PREVENT_MULTIPLE_BIND
GLuint VertexArray::s_boundArray = 0;
#endif

VertexArray::VertexArray()
{
    GLuint array;
    glGenVertexArrays(1, &array);
    
    AssignGLObject(array, glDeleteVertexArrays);
}

VertexArray& VertexArray::Bind()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundArray == *this)
        return *this;
    s_boundArray = *this;
#endif
    
    glBindVertexArray(*this);
    return *this;
}
void VertexArray::BindNone()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundArray == 0)
        return;
    s_boundArray = 0;
#endif
    
    glBindVertexArray(0);
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
    return *this;
}

VertexArray& VertexArray::DrawElements(DrawMode::E mode, GLsizei count, IndicesType::E type, const GLvoid * indices)
{
    GLFK_AUTO_BIND();
    Renderer::DrawElements(mode, count, type, indices);
    GLFK_AUTO_UNBIND();
    return *this;
}

VertexArray& VertexArray::DrawArrays(DrawMode::E mode, GLint first, GLsizei count)
{
    GLFK_AUTO_BIND();
    Renderer::DrawArrays(mode, first, count);
    GLFK_AUTO_UNBIND();
    return *this;
}
