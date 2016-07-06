GLFK - Minimalistic and Moduler OpenGL C++ Framework
====================================================

Divided into Core and Extra.

Main Core Goals:
- One opengl object = one class
- Methods resembling original OpenGL function names
- Automatic binding, optional unbinding on bindable objects

Main Extra Goals:
- Simplify and abstract OpenGL context creation (GLFW/GLAD/others)
- Use Core classes to define more complex non-GL structures like Material or Effect

Core quality rules:
- Use { on a separate line only for .cpp method and function definition blocks
- Encapsulate even an 'if' with one-line block using { and }
- All #defines declared in code included by user must start with GLFK_
- Every class must be documented with a short description of purpose of the class
- Documentation is required only for parts which looks confusing or worse readable
- Methods generally don't need to be documented unless it is not clear what they does
