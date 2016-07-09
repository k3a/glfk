/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
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

CuboidModel::CuboidModel(float width, float height, float depth)
{
    float verts[] = {
        -width/2, -height/2, depth/2,   // 0: front bottom-left
        width/2, -height/2, depth/2,    // 1: front bottom-right
        width/2, height/2, depth/2,     // 2: front top right
        -width, height/2, depth/2,      // 3: front top left
        
        -width/2, -height/2, -depth/2,   // 4: front bottom-left
        width/2, -height/2, -depth/2,    // 5: front bottom-right
        width/2, height/2, -depth/2,     // 6: front top right
        -width, height/2, -depth/2,      // 7: front top left
    };
    
    // vertex buffer
    
    VertexBuffer vb(GetVAO());
    
    vb.SetData(sizeof(verts), verts);
    vb.SetAttribPointer(0, 3, AttribType::FLOAT);
    
    AddVertexBuffer(vb);
    
    
    // index buffer
    /*
        7_____6
        /    /|
        3---2 |
        | 4 | 5
        0---1/

    */
    
    unsigned char inds[] = {
        0, 2, 3, 0, 1, 2, // front
        1, 6, 2, 1, 5, 6, // right
        3, 6, 7, 3, 2, 6, // top
        4, 3, 7, 4, 0, 3, // left
        4, 1, 0, 4, 5, 1, // bottom
        5, 7, 6, 5, 4, 7, // back
    };
    
    IndexBuffer ib(GetVAO());
    ib.SetData(sizeof(inds), inds);
    
    SetIndexBuffer(ib, IndicesType::UNSIGNED_BYTE, sizeof(inds)/sizeof(inds[0]));
    
    // shader
    Program prg(VertexShaders::NoTransform(), FragmentShaders::RedColor());
    SetProgram(prg);
}


