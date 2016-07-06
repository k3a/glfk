#pragma once

// include opengl headers
#ifdef GLFK_HAS_GLFW
# define GLFW_INCLUDE_GLCOREARB // make sure to include gl3 core header
# include <GLFW/glfw3.h>
#elif defined(__APPLE__)
# include <OpenGL/gl3.h>
#elif defined(_WIN32)
# include <windows.h>
# pragma comment(lib, "opengl32")
# include <gl/gl.h>
#else
# include <GL/gl.h>
#endif

class Renderer
{
	public:
		static void Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		static void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
		static void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices = NULL);
		static void DrawArrays(GLenum mode, GLint first, GLsizei count);
};
typedef Renderer R;

// useful macros
#define GLFK_AUTO_BIND(...) Bind(__VA_ARGS__)
#ifdef GLFK_ENSURE_UNBIND
# define GLFK_AUTO_UNBIND(...) Unbind(__VA_ARGS__)
#else
# define GLFK_AUTO_UNBIND(...)
#endif

