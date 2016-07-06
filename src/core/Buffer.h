/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"
#include "VertexArray.h"

/// Vertex Buffer Object (VBO)
class BaseBuffer : public NoCopy
{
public:
    enum Usage {
        STREAM_DRAW = GL_STREAM_DRAW,
        STREAM_READ = GL_STREAM_READ,
        STREAM_COPY = GL_STREAM_COPY,
        STATIC_DRAW = GL_STATIC_DRAW,
        STATIC_READ = GL_STATIC_READ,
        STATIC_COPY = GL_STATIC_COPY,
        DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        DYNAMIC_READ = GL_DYNAMIC_READ,
        DYNAMIC_COPY = GL_DYNAMIC_COPY
    };
    
    BaseBuffer(VertexArray& vao);
    ~BaseBuffer();

    BaseBuffer& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseBuffer& Unbind(GLenum target){ BindNone(target); return *this; };
    BaseBuffer& SetData(GLenum target, GLsizeiptr size, const GLvoid * data, Usage usage = STATIC_DRAW);

private:
    GLuint _buffer;
};

/// Vertex Buffer Object (VBO) for a single target
class Buffer : public BaseBuffer
{
public:
    Buffer(VertexArray& vao, GLenum target);
    Buffer& Bind();
    Buffer& Unbind();
    Buffer& SetData(GLsizeiptr size, const GLvoid * data, Usage usage = STATIC_DRAW);

private:
    GLenum _target;	
};

/// Vertex Buffer Object (VBO) for GL_ARRAY_BUFFER
class ArrayBuffer : public Buffer
{
public:
    enum AttribType {
        BYTE = GL_BYTE,
        UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        SHORT = GL_SHORT,
        UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
        INT = GL_INT,
        UNSIGNED_INT = GL_UNSIGNED_INT,
        HALF_FLOAT = GL_HALF_FLOAT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE,
        FIXED = GL_FIXED,
        INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
        UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
        UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV
    };
    
    ArrayBuffer(VertexArray& vao) : Buffer(vao, GL_ARRAY_BUFFER) {};

    ArrayBuffer& SetAttribPointer(GLuint index, GLint size, AttribType type, 
            bool normalized = false, GLsizei stride = 0, const GLvoid * pointer = NULL);
};
/// Alias for ArrayBuffer
typedef ArrayBuffer VertexBuffer;

/// Vertex Buffer Object (VBO) for GL_ELEMENT_ARRAY_BUFFER
class ElementArrayBuffer : public Buffer
{
public:
    ElementArrayBuffer(VertexArray& vao) : Buffer(vao, GL_ELEMENT_ARRAY_BUFFER) {};
};
/// Alias for ElementArrayBuffer
typedef ElementArrayBuffer IndexBuffer;


/// Buffer Object for GL_COPY_READ_BUFFER
class CopyReadBuffer : public Buffer
{
public:
    CopyReadBuffer(VertexArray& vao) : Buffer(vao, GL_COPY_READ_BUFFER) {};
};

/// Buffer Object for GL_COPY_READ_BUFFER
class CopyWriteBuffer : public Buffer
{
public:
    CopyWriteBuffer(VertexArray& vao) : Buffer(vao, GL_COPY_WRITE_BUFFER) {};
};

/// Buffer Object for GL_DRAW_INDIRECT_BUFFER
class DrawIndirrectBuffer : public Buffer
{
public:
    DrawIndirrectBuffer(VertexArray& vao) : Buffer(vao, GL_DRAW_INDIRECT_BUFFER) {};
};

/// Buffer Object for GL_PIXEL_PACK_BUFFER
class PixelPackBuffer : public Buffer
{
public:
    PixelPackBuffer(VertexArray& vao) : Buffer(vao, GL_PIXEL_PACK_BUFFER) {};
};

/// Buffer Object for GL_PIXEL_UNPACK_BUFFER
class PixelUnackBuffer : public Buffer
{
public:
    PixelUnackBuffer(VertexArray& vao) : Buffer(vao, GL_PIXEL_UNPACK_BUFFER) {};
};

/// Buffer Object for GL_TEXTURE_BUFFER
class TextureBuffer : public Buffer
{
public:
    TextureBuffer(VertexArray& vao) : Buffer(vao, GL_TEXTURE_BUFFER) {};
};

/// Buffer Object for GL_TRANSFORM_FEEDBACK_BUFFER
class TransformFeedbackBuffer : public Buffer
{
public:
    TransformFeedbackBuffer(VertexArray& vao) : Buffer(vao, GL_TRANSFORM_FEEDBACK_BUFFER) {};
};

/// Buffer Object for GL_UNIFORM_BUFFER
class UniformBuffer : public Buffer
{
public:
    UniformBuffer(VertexArray& vao) : Buffer(vao, GL_UNIFORM_BUFFER) {};
};




