/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

// include opengl headers
#include <glad.h>
#ifdef GLFK_HAS_GLFW
//# define GLFW_INCLUDE_GLCOREARB // make sure to include gl3 core header
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

#ifdef GLFK_HAS_GLM
# include <glm/vec3.hpp>
# include <glm/vec4.hpp>
# include <glm/mat4x4.hpp>
#endif

#include <assert.h>

#include "Utils.h"
#include "Enums.h"

/// Class encapsulating static functions to general OpenGL commands not bound to any object
class Renderer
{
public:
    static void Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    static void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    static void DrawElements(DrawMode::E mode, GLsizei count, IndicesType::E type, const GLvoid * indices = NULL);
    static void DrawArrays(DrawMode::E mode, GLint first, GLsizei count);
    static void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
    
    /// Return value of GL integer state variable
    static GLint GetInt(GLenum pname);
    /// Return value of indexed GL integer state variable
    static GLint GetInt(GLenum pname, GLuint index);
    /// Return value of GL string state variable
    static const char* GetString(GLenum pname);
    
    // helpers
    static unsigned GetMaxTextureUnits();
};
/// Shortcut to Renderer
typedef Renderer R;

// ---------------------------------------------------------------

/// Print refence counting done with GLObject
#ifdef GLFK_DEBUG_REF_COUNTING
# include <stdio.h>
#endif

/// Class holding a reference counted GL object (OpenGL classes holding a GL objects derives from this)
class GLObject
{
protected:
    typedef void(*DeleteObjectCallbackType1)(GLuint obj);
    typedef void(*DeleteObjectCallbackType2)(GLsizei n, const GLuint* ptr);
    
    /// Default constructor
    GLObject() : _refs(new unsigned(1)), _del1(NULL), _del2(NULL), _obj(0) {
#ifdef GLFK_DEBUG_REF_COUNTING
        printf("%p: new GLObject\n", this);
#endif
    };
    
    /// Copy constructor
    GLObject(const GLObject& other) : _refs(other._refs), _del1(other._del1), _del2(other._del2), _obj(other._obj) {
#ifdef GLFK_DEBUG_REF_COUNTING
        printf("%p: copy with obj %u\n", this, _obj);
#endif
        Retain(); };
    ~GLObject(){ if (_obj>0) Release(); };
    
    /// Copy operator
    GLObject& operator=(const GLObject& other){
        if (this != &other){
#ifdef GLFK_DEBUG_REF_COUNTING
            printf("%p: assigning obj %u from other GLObject %p\n", this, _obj, &other);
#endif
            Release();
            _obj = other._obj;
            _refs = other._refs;
            Retain();
        }
        return *this;
    }
    
    /// Assign a OpenGL object and associated OpenGL Delete function. Can be called one time only.
    GLObject& AssignGLObject(GLuint obj, DeleteObjectCallbackType1 del1) {
        assert(_obj == 0); // assign called second time
        _obj = obj;
        _del1 = del1;
#ifdef GLFK_DEBUG_REF_COUNTING
        printf("%p: assigned obj %u\n", this, _obj);
#endif
        return *this;
    }
    /// Assign a OpenGL object and associated OpenGL Delete function. Can be called one time only.
    GLObject& AssignGLObject(GLuint obj, DeleteObjectCallbackType2 del2) {
        assert(_obj == 0); // assign called second time
        _obj = obj;
        _del2 = del2;
#ifdef GLFK_DEBUG_REF_COUNTING
        printf("%p: assigned obj %u\n", this, _obj);
#endif
        return *this;
    }
    
    /// Retain this object, incrementing reference count
    GLObject& Retain(){ ++*_refs; return *this; };
    
    /// Release this object, decrementing reference count
    GLObject& Release(){
        assert(*_refs > 0); // attempt to release a released object
        if (*_refs == 1) {
#ifdef GLFK_DEBUG_REF_COUNTING
            printf("%p: deleting obj %u using %p or %p\n", this, _obj, _del1, _del2);
#endif
            if (_del1) {
                _del1(_obj);
            } else if (_del2) {
                _del2(1, &_obj);
            }
            _obj = 0;
            delete _refs;
            return *this;
        }
        --*_refs;
        return *this;
    };
    
public:
    
    /// Returns the stored GL object 
    operator GLuint()const{ return _obj; }
    
    /// Returns current reference count
    unsigned RefCount()const{ return *_refs; };
    
private:
    unsigned *_refs;
    DeleteObjectCallbackType1 _del1;
    DeleteObjectCallbackType2 _del2;
protected:
    GLuint _obj;
};

// useful macros -------------------------------------------------

/// Automatically bind an object
#define GLFK_AUTO_BIND(...) Bind(__VA_ARGS__)
#define GLFK_AUTO_BIND_OBJ(obj, ...) obj.Bind(__VA_ARGS__)
#ifdef GLFK_ENSURE_UNBIND
# define GLFK_AUTO_UNBIND(...) Unbind(__VA_ARGS__)
# define GLFK_AUTO_UNBIND_OBJ(obj, ...) obj.Unbind(__VA_ARGS__)
#else
# define GLFK_AUTO_UNBIND(...)
# define GLFK_AUTO_UNBIND_OBJ(...)
#endif
