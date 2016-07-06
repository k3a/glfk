/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Renderer.h"
#include "Utils.h"

void Renderer::Clear(GLbitfield mask)
{
    glClear(mask);
}
void Renderer::ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    glClearColor(red, green, blue, alpha);
}

void Renderer::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
{
    glDrawElements(mode, count, type, indices);
    PrintGLError("drawing elements");
}

void DrawArrays(GLenum mode, GLint first, GLsizei count)
{
    glDrawArrays(mode, first, count);
    PrintGLError("drawing arrays");
}
