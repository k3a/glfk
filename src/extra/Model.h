/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "core/Buffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"

#include <vector>

class Model
{
public:
    Model();
    
public:
    bool IsValid()const{ return _valid; };
    VertexArray& GetVAO(){ return _vao; };
    Model& Draw(DrawMode::E mode = DrawMode::TRIANGLES);
    
    Model& SetProgram(const Program& prg);
    Model& SetIndexBuffer(const IndexBuffer& ib, IndicesType::E indtype, unsigned count);
    Model& AddVertexBuffer(const VertexBuffer& vb);
    
protected:
    VertexArray _vao;
    
private:
    bool _valid;
    
    IndexBuffer _ib;
    IndicesType::E _ibType;
    unsigned _ibCount;
    
    typedef std::vector<VertexBuffer> VertexBufferArray;
    VertexBufferArray _vbs;
    
    Program _program;
};


class CuboidModel : public Model
{
public:
    CuboidModel(float width, float height, float depth);
};
