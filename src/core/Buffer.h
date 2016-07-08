/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"
#include "VertexArray.h"

#include <map>

/// Vertex Buffer Object (VBO)
class BaseBuffer : public GLObject
{
public:
    BaseBuffer(VertexArray& vao);

    BaseBuffer& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseBuffer& Unbind(GLenum target){ BindNone(target); return *this; };
    BaseBuffer& SetData(GLenum target, GLsizeiptr size, const GLvoid * data, BufferUsage::E usage = BufferUsage::STATIC_DRAW);

private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    typedef std::map<GLenum, GLuint> TargetBufferMap;
    static TargetBufferMap s_boundBufferToTarget;
#endif
};

/// Vertex Buffer Object (VBO) for a single target
class Buffer : public BaseBuffer
{
public:
    Buffer(VertexArray& vao, GLenum target) : BaseBuffer(vao), _target(target) { }
    Buffer& Bind() { return (Buffer&)BaseBuffer::Bind(_target); }
    Buffer& Unbind() { return (Buffer&)BaseBuffer::Unbind(_target); }
    
    Buffer& SetData(GLsizeiptr size, const GLvoid * data, BufferUsage::E usage = BufferUsage::STATIC_DRAW) {
        return (Buffer&)BaseBuffer::SetData(_target, size, data, usage);
    }

protected:
    GLenum _target;	
};

/// Vertex Buffer Object (VBO) for GL_ARRAY_BUFFER
class ArrayBuffer : public Buffer
{
public:    
    ArrayBuffer(VertexArray& vao) : Buffer(vao, GL_ARRAY_BUFFER) {};

    ArrayBuffer& SetAttribPointer(GLuint index, GLint size, AttribType::E type,
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




