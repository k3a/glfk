#include "extra/Window.h"

#include <stdio.h>

#define GLFW_INCLUDE_GLCOREARB // make sure to include gl3 core header
#include <GLFW/glfw3.h>

struct Window::sPrivate {
	sPrivate() 
	:	window(NULL),
		framebufferSizeCallback(NULL)
   	{};

	GLFWwindow* window;

	Window::FramebufferSizeCallback framebufferSizeCallback;
	static void _FramebufferSizeCallback(GLFWwindow *w, int width, int height) 
	{
		sPrivate* p = (sPrivate*)glfwGetWindowUserPointer(w);
		if (p->framebufferSizeCallback) p->framebufferSizeCallback(width, height);
	}
};

Window::Window() 
: _private(new sPrivate) 
{
    if (!glfwInit())
        return;
}

Window::~Window() 
{
    glfwTerminate();

	delete _private;
}

bool Window::Create(unsigned width, unsigned height, const char* title) 
{
#ifdef DEBUG
	printf("DEBUG enabled\n");
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_DEPTH_BITS, 16);

    _private->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!_private->window)
    {
		printf("ERR: Unable to create GLFW Window");
        return false;
    }

	glfwSetWindowUserPointer(_private->window, _private);
	glfwMakeContextCurrent(_private->window);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLint n, i;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	printf("Extensions: ");
	for (i = 0; i < n; i++) {
		printf("%s ", glGetStringi(GL_EXTENSIONS, i));
	}
	printf("\n\n");

	// clear gl errors
	glGetError();

	return true;
}


Window::FramebufferSizeCallback Window::SetFramebufferSizeCallback(FramebufferSizeCallback cb)
{
	FramebufferSizeCallback prev = _private->framebufferSizeCallback;
	_private->framebufferSizeCallback = cb;
	glfwSetFramebufferSizeCallback(_private->window, _private->_FramebufferSizeCallback);

	// call if set for the first time
	if (prev != cb) { 
		int width, height;
		glfwGetFramebufferSize(_private->window, &width, &height);
		cb(width, height);
	}

	return prev;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(_private->window);
}
void Window::PollEvents()
{
	glfwPollEvents();
}
bool Window::ShouldClose() 
{
	return glfwWindowShouldClose(_private->window);
}



