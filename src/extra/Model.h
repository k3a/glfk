/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include "core/Buffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

GLFK_ENUM(ModelAttribute){
    POSITION,
    NORMAL,
    TANGENT,
    BITANGENT,
    TEXCOORD,
    COLOR,
}GLFK_ENUM_END;

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
    
    struct GLFK_PACKED BasicVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
        
        BasicVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texcoord);
    };
    typedef std::vector<BasicVertex> BasicVertexArray;
    
    struct GLFK_PACKED ComplexVertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 bitangent;
        glm::vec2 texcoord;
        glm::vec4 color;
        
        ComplexVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent,
                const glm::vec3& bitangent, const glm::vec2& texcoord, const glm::vec4& color);
    };
    typedef std::vector<ComplexVertex> ComplexVertexArray;
    
    typedef unsigned int Index;
    typedef std::vector<Index> IndexArray;
    
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

/// Plane oriented in XY
class PlaneModel : public Model
{
public:
    PlaneModel(float width, float height);
};

/// Box with origin at its center, with specified width along X, height along Y and depth along Z
class BoxModel : public Model
{
public:
    BoxModel(float width, float height, float depth);
};
