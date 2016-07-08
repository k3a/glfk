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

void Renderer::DrawElements(DrawMode::E mode, GLsizei count, IndicesType::E type, const GLvoid * indices)
{
    glDrawElements(mode, count, type, indices);
}

void Renderer::DrawArrays(DrawMode::E mode, GLint first, GLsizei count)
{
    glDrawArrays(mode, first, count);
}

static void Renderer::Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
}

GLint Renderer::GetInt(GLenum pname)
{
    GLint val;
    glGetIntegerv(pname, &val);
    return val;
}

const char* Renderer::GetString(GLenum pname)
{
    const char* val;
    val = (const char*)glGetString(pname);
    return val;
}

unsigned Renderer::GetMaxTextureUnits()
{
    static unsigned s_max = 0;
    if (s_max > 0) {
        return s_max;
    }
    
    return (s_max = GetInt(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS));
}
