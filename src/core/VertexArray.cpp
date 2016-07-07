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
    PrintGLError("creating VAO");
    
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
    PrintGLError("binding VAO");
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
