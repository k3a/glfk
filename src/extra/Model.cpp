/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/

#include "Model.h"
#include "Shaders.h"

#include <stdio.h>

Model::Model()
: _valid(false), _ib(_vao), _ibCount(0)
{
    
}

Model& Model::Draw(DrawMode::E mode)
{
    //TODO: currently supports indexed data only
    
    _program.Bind();
    _vao.DrawElements(mode, _ibCount, _ibType);
    
    return *this;
}

Model& Model::SetProgram(const Program& prg)
{
    _program = prg;
    
    // set common attributes
    _program.BindAttribLocation(ModelAttribute::POSITION, "a_vPosition");
    _program.BindAttribLocation(ModelAttribute::NORMAL, "a_vNormal");
    _program.BindAttribLocation(ModelAttribute::TANGENT, "a_vTangent");
    _program.BindAttribLocation(ModelAttribute::BITANGENT, "a_vBitangent");
    _program.BindAttribLocation(ModelAttribute::TEXCOORD, "a_vTexCoord");
    _program.BindAttribLocation(ModelAttribute::COLOR, "a_vColor");
    
    _valid = _program.Link();
    
    if (!_valid) {
        std::string log = _program.GetInfoLog();
        printf("Shader link failed: %s\n", log.c_str());
    }
    
    return *this;
}

Model& Model::SetIndexBuffer(const IndexBuffer& ib, IndicesType::E indtype, unsigned count)
{
    _ib = ib;
    _ibType = indtype;
    _ibCount = count;
    
    return *this;
}
Model& Model::AddVertexBuffer(const VertexBuffer& vb)
{
    _vbs.push_back(vb);
    
    return *this;
}

//-----------------------------------------------------

Model::BasicVertex::BasicVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texcoord)
: position(position), normal(normal), texcoord(texcoord)
{
}

Model::ComplexVertex::ComplexVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent,
                        const glm::vec3& bitangent, const glm::vec2& texcoord, const glm::vec4& color)
: position(position), normal(normal), tangent(tangent), bitangent(bitangent), texcoord(texcoord), color(color)
{
}

//-----------------------------------------------------

static void AddFace(Model::BasicVertexArray& varr, Model::IndexArray& iarr, const glm::vec3& origin,const glm::vec3& right, const glm::vec3& up)
{
    glm::vec3 normal = glm::normalize(glm::cross(glm::normalize(right), glm::normalize(up)));
    unsigned startIndex = varr.size();
    
    varr.push_back(Model::BasicVertex(origin, normal, glm::vec2(0, 0))); // 0: bottom left
    varr.push_back(Model::BasicVertex(origin + right, normal, glm::vec2(1, 0))); // 1: bottom right
    varr.push_back(Model::BasicVertex(origin + right + up, normal, glm::vec2(1, 1))); // 2: top right
    varr.push_back(Model::BasicVertex(origin + up, normal, glm::vec2(0, 1))); // 3: top left
    
    iarr.push_back(startIndex + 0);
    iarr.push_back(startIndex + 2);
    iarr.push_back(startIndex + 3);
    iarr.push_back(startIndex + 0);
    iarr.push_back(startIndex + 1);
    iarr.push_back(startIndex + 2);
}

//-----------------------------------------------------

PlaneModel::PlaneModel(float width, float height)
{
    BasicVertexArray varr;
    IndexArray iarr;
    
    AddFace(varr, iarr, glm::vec3(-width/2, -height/2, 0), glm::vec3(width, 0, 0), glm::vec3(0, height, 0));
    
    // vertex buffer
    
    VertexBuffer vb(GetVAO());
    
    vb.SetData(sizeof(BasicVertex) * varr.size(), &varr[0]);
    
    BasicVertex* offset = NULL;
    vb.SetAttribPointer(ModelAttribute::POSITION, 3, AttribType::FLOAT, false, sizeof(BasicVertex), &offset->position.x);
    vb.SetAttribPointer(ModelAttribute::NORMAL, 3, AttribType::FLOAT, false, sizeof(BasicVertex), &offset->normal.x);
    vb.SetAttribPointer(ModelAttribute::TEXCOORD, 2, AttribType::FLOAT, false, sizeof(BasicVertex), &offset->texcoord.x);
    
    AddVertexBuffer(vb);
    
    // index buffer
    
    IndexBuffer ib(GetVAO());
    ib.SetData(sizeof(Index) * iarr.size(), &iarr[0]);
    
    SetIndexBuffer(ib, IndicesType::UNSIGNED_INT, iarr.size());
    
    // shader
    
    Program prg(VertexShaders::NoTransform(), FragmentShaders::RedColor());
    SetProgram(prg);
}

//-----------------------------------------------------

BoxModel::BoxModel(float width, float height, float depth)
{
    /*
    7_____6
    /    /|
    3---2 |
    | 4 | 5
    0---1/
     
    */
    
    glm::vec3 verts[8];
    
    verts[0] = glm::vec3(-width/2, -height/2, depth/2);
    verts[1] = glm::vec3(width/2, -height/2, depth/2);
    verts[2] = glm::vec3(width/2, height/2, depth/2);
    verts[3] = glm::vec3(-width/2, height/2, depth/2);
    verts[4] = glm::vec3(-width/2, -height/2, -depth/2);
    verts[5] = glm::vec3(width/2, -height/2, -depth/2);
    verts[6] = glm::vec3(width/2, height/2, -depth/2);
    verts[7] = glm::vec3(-width/2, height/2, -depth/2);
    
    BasicVertexArray varr;
    IndexArray iarr;
    
    AddFace(varr, iarr, verts[0], verts[1]-verts[0], verts[3]-verts[0]); // front
    AddFace(varr, iarr, verts[2], verts[1]-verts[2], verts[6]-verts[2]); // right
    AddFace(varr, iarr, verts[3], verts[2]-verts[3], verts[7]-verts[3]); // top
    AddFace(varr, iarr, verts[1], verts[0]-verts[1], verts[5]-verts[1]); // bottom
    AddFace(varr, iarr, verts[0], verts[3]-verts[0], verts[4]-verts[0]); // left
    AddFace(varr, iarr, verts[5], verts[4]-verts[5], verts[6]-verts[5]); // back
    
    // vertex buffer
    
    VertexBuffer vb(GetVAO());
    
    vb.SetData(sizeof(BasicVertex) * varr.size(), &varr[0]);
    
    BasicVertex* offset = NULL;
    vb.SetAttribPointer(ModelAttribute::POSITION, 3, AttribType::FLOAT, false, sizeof(BasicVertex), &offset->position.x);
    vb.SetAttribPointer(ModelAttribute::NORMAL, 3, AttribType::FLOAT, false, sizeof(BasicVertex), &offset->normal.x);
    vb.SetAttribPointer(ModelAttribute::TEXCOORD, 2, AttribType::FLOAT, false, sizeof(BasicVertex), &offset->texcoord.x);
    
    AddVertexBuffer(vb);
    
    // index buffer
    
    IndexBuffer ib(GetVAO());
    ib.SetData(sizeof(Index) * iarr.size(), &iarr[0]);
    
    SetIndexBuffer(ib, IndicesType::UNSIGNED_INT, iarr.size());
    
    // shader
    
    Program prg(VertexShaders::NoTransform(), FragmentShaders::RedColor());
    SetProgram(prg);
}


