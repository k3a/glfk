/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include <iostream>
#include <math.h>

#include "extra/Window.h"
#include "core/Renderer.h"
#include "core/VertexArray.h"
#include "core/Buffer.h"
#include "core/Shaders.h"

static float unitSquareVertPos[] = { 
    -1, 1, 0, // top left
    -1, -1, 0, // bottom left
    1, -1, 0, // bottom right
    1, 1, 0 // top right
};
static unsigned char unitSquareInd[] = {
    0, 1, 2, 3
};

static const char* vsSrc = "\
#version 150 \n\
in vec3 inPos; \n\
void main(){ \n\
    gl_Position = vec4(inPos, 1.0); \n\
} \n\
";
static const char* fsSrc = "\
#version 150 \n\
out vec4 outColor; \n\
uniform vec3 color; \n\
void main() { \n\
    outColor = vec4(color,1); \n\
}";

static void resize_cb(unsigned w, unsigned h) 
{
    std::cout << "FB Resize: " << w << "x" << h << std::endl;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main()
{
    Window win;
    win.Create(640, 480, "GLFK");
    win.SetFramebufferSizeCallback(resize_cb);

    BaseShader* vs = VertexShader::FromString(vsSrc);
    if (!vs->Compile()) {
        std::cout << "VS Error: " << vs->GetInfoLog() << std::endl;
    }
    BaseShader* fs = FragmentShader::FromString(fsSrc);
    if (!fs->Compile()) {
        std::cout << "FS Error: " << fs->GetInfoLog() << std::endl;
    }
    Program prg;
    prg.AttachShader(*vs).AttachShader(*fs);
    if (!prg.Link()) {
        std::cout << "Prog Error: " << prg.GetInfoLog() << std::endl;
    } else {
        std::cout << "Prog Compiled OK: " << prg.GetNumActiveAttributes() << " attrs"
            << prg.GetNumActiveUniforms() << " uniforms" << std::endl;
    }

    VertexArray vao;
    
    ArrayBuffer bv(vao);
    bv.SetData(sizeof(unitSquareVertPos), unitSquareVertPos);
    bv.SetAttribPointer(prg.GetAttribute("inPos"), 3, ArrayBuffer::FLOAT);
    vao.EnableAttribArray(prg.GetAttribute("inPos"));

    ElementArrayBuffer bi(vao);
    bi.SetData(sizeof(unitSquareInd), unitSquareInd);

    R::ClearColor(0,1,1,0);
    float time = 0;
    
    while(!win.ShouldClose()) {
        time += 0.01;
        R::Clear();

        prg.Use();
        prg.SetUniform("color", (float)1.0, (float)sinf(time), (float)0.0);
        
        vao.DrawElements(VertexArray::TRIANGLE_FAN, 4, VertexArray::UNSIGNED_BYTE);
        
        win.SwapBuffers();
        win.PollEvents();
    }

    return 0;
}
