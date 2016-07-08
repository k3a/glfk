GLFK - Minimalistic and Modular OpenGL C++ Framework
====================================================

C++ OOP Wrapper for OpenGL 3.2+.
Static linking of dependencies (to prevent broken builds on dependency updates).
Builds static library by default (dynamic linking is not very useful here as often only one graphical app is running).

## Structure ##
The code is divided into Core and Extra sections.

### Main Core Goals ###

- One opengl object = one class
- Minimalistic, no complicated and confusing c++ structures or exceptions
- Modular, only Utils.cpp/.h, Enums.h and Renderer.cpp/.h are required so you can use classes you need only
- Methods resembling original OpenGL function names
- Automatic binding, optional unbinding on bindable objects (GLFK_ENSURE_UNBIND)
- Fast and production-ready

### Main Extra Goals ###

- Simplify and abstract OpenGL context creation (GLFW/GLAD/others)
- Integrate optional 3rd-party libraries which do the job better, then writing them from scratch
- Use Core classes to define more complex non-GL structures like Material, Effect, Mesh

## Core Style and Quality Rules ##

- Use { on a separate line only for .cpp method and function definition blocks
- Encapsulate even an 'if' with one-line block using { and }
- All #defines declared in code included by user must start with GLFK_ (with rare handy user stuff like GLSL macro)
- Every class must be documented with a short description of purpose of the class
- Documentation is required only for parts which looks confusing or are not well readable
- Methods generally don't need to be documented unless it is not clear what they do
- Don't make or throw any C++ exceptions!
- Use `std::string` only when you need to store a volatile char* in a string object. For example don't use it when GL returns static `const char*`.
- Enums in Enums.h must represent GL constants

## How to Help ##

- Add missing methods and functionality
- Provide bug reports

## TODO ##

- glDrawBuffers or something like that for multiple render targets
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
- Put headers into a separate subfolder
- New features of GL 3.x+ like multisample alternatives (glRenderbufferStorageMultisample)
- handle proxy textures somehow


