/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
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
    BaseBuffer(VertexArray vao);

    BaseBuffer& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseBuffer& Unbind(GLenum target){ BindNone(target); return *this; };
    
    /// Set data to the buffer
    BaseBuffer& SetData(GLenum target, GLsizeiptr size, const GLvoid * data, BufferUsage::E usage = BufferUsage::STATIC_DRAW);

private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    typedef std::map<GLenum, GLuint> TargetBufferMap;
    static TargetBufferMap s_boundBufferToTarget;
#endif
    
protected:
    VertexArray _vao;
};

/// Vertex Buffer Object (VBO) for a single target
class Buffer : public BaseBuffer
{
public:
    Buffer(VertexArray vao, GLenum target) : BaseBuffer(vao), _target(target) { }
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
    ArrayBuffer(VertexArray vao) : Buffer(vao, GL_ARRAY_BUFFER) {};
    
    /// Enables or disables the specified attribute array index
    ArrayBuffer& EnableAttribArray(GLuint index, bool enable=true){ _vao.EnableAttribArray(index, enable); return *this; };
    
    /** Enable attribute array and set array pointer
    \note Will also automatically call EnableAttribArray for the index.
    \param normalizeFixedPoint When true, integer format will be mapped to the range [-1,1] (for signed values) or [0,1] 
    (for unsigned values) when they are accessed and converted to floating point. Otherwise, values will be
    converted to floats directly without normalization */
    ArrayBuffer& SetAttribPointer(GLuint index, GLint size, AttribType::E type,
                                    bool normalizeFixedPoint = false, GLsizei stride = 0, const GLvoid * pointer = NULL);
    
    // helpers
    
    static unsigned GetMaxVertexAttributes(){ return Renderer::GetInt(GL_MAX_VERTEX_ATTRIBS); };
};
/// Alias for ArrayBuffer
typedef ArrayBuffer VertexBuffer;

/// Vertex Buffer Object (VBO) for GL_ELEMENT_ARRAY_BUFFER
class ElementArrayBuffer : public Buffer
{
public:
    ElementArrayBuffer(VertexArray vao) : Buffer(vao, GL_ELEMENT_ARRAY_BUFFER) {};
};
/// Alias for ElementArrayBuffer
typedef ElementArrayBuffer IndexBuffer;


/// Buffer Object for GL_COPY_READ_BUFFER
class CopyReadBuffer : public Buffer
{
public:
    CopyReadBuffer(VertexArray vao) : Buffer(vao, GL_COPY_READ_BUFFER) {};
};

/// Buffer Object for GL_COPY_READ_BUFFER
class CopyWriteBuffer : public Buffer
{
public:
    CopyWriteBuffer(VertexArray vao) : Buffer(vao, GL_COPY_WRITE_BUFFER) {};
};

/// Buffer Object for GL_DRAW_INDIRECT_BUFFER
class DrawIndirrectBuffer : public Buffer
{
public:
    DrawIndirrectBuffer(VertexArray vao) : Buffer(vao, GL_DRAW_INDIRECT_BUFFER) {};
};

/// Buffer Object for GL_PIXEL_PACK_BUFFER
class PixelPackBuffer : public Buffer
{
public:
    PixelPackBuffer(VertexArray vao) : Buffer(vao, GL_PIXEL_PACK_BUFFER) {};
};

/// Buffer Object for GL_PIXEL_UNPACK_BUFFER
class PixelUnackBuffer : public Buffer
{
public:
    PixelUnackBuffer(VertexArray vao) : Buffer(vao, GL_PIXEL_UNPACK_BUFFER) {};
};

/// Buffer Object for GL_TEXTURE_BUFFER
class TextureBuffer : public Buffer
{
public:
    TextureBuffer(VertexArray vao) : Buffer(vao, GL_TEXTURE_BUFFER) {};
};

/// Buffer Object for GL_TRANSFORM_FEEDBACK_BUFFER
class TransformFeedbackBuffer : public Buffer
{
public:
    TransformFeedbackBuffer(VertexArray vao) : Buffer(vao, GL_TRANSFORM_FEEDBACK_BUFFER) {};
};

/// Buffer Object for GL_UNIFORM_BUFFER
class UniformBuffer : public Buffer
{
public:
    UniformBuffer(VertexArray vao) : Buffer(vao, GL_UNIFORM_BUFFER) {};
};




