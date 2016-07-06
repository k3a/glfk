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
#include "core/Shader.h"
#include "core/Texture.h"

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
out vec2 vCoord; \n\
void main(){ \n\
    gl_Position = vec4(inPos, 1.0); \n\
    vCoord = inPos.xy * 0.5 + 0.5; \n\
} \n\
";
static const char* fsSrc = "\
#version 150 \n\
in vec2 vCoord; \n\
out vec4 outColor; \n\
uniform vec3 uColor; \n\
uniform sampler2D uTexture; \n\
void main() { \n\
    outColor = vec4( texture(uTexture, vCoord.xy).rgb /*+ uColor/2.0*/ , 1.0); \n\
}";

static void resize_cb(unsigned w, unsigned h) 
{
    std::cout << "FB Resize: " << w << "x" << h << std::endl;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
static void key_cb(int key, int scancode, int action, int mods)
{
    if (key == 256) // GLFW_KEY_ESCAPE
        exit(0);
}

int main()
{
    Window win;
    win.Create(640, 480, "GLFK");
    win.SetFramebufferSizeCallback(resize_cb);
    win.SetKeyCallback(key_cb);

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
        std::cout << "Prog Compiled OK: " << prg.GetNumActiveAttributes() << " attrs, "
            << prg.GetNumActiveUniforms() << " uniforms" << std::endl;
    }

    VertexArray vao;
    
    ArrayBuffer bv(vao);
    bv.SetData(sizeof(unitSquareVertPos), unitSquareVertPos);
    bv.SetAttribPointer(prg.GetAttribute("inPos"), 3, ArrayBuffer::FLOAT);
    vao.EnableAttribArray(prg.GetAttribute("inPos"));

    ElementArrayBuffer bi(vao);
    bi.SetData(sizeof(unitSquareInd), unitSquareInd);
    
    Texture2D tex;
    unsigned char texData[] = {
        255, 0, 0, 255,  0, 255, 0, 255,
        0, 0, 255, 255,  255, 255, 0, 255
    };
    tex.SetImage(0, GL_RGB, 2, 2, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    tex.GenerateMipmap();
    tex.SetToUnit(0);
    prg.SetUniformTextureUnit("uTexture", tex.GetUnit());
    
    R::ClearColor(0,1,1,0);
    float time = 0;
    
    while(!win.ShouldClose()) {
        time += 0.01;
        R::Clear();

        prg.Use();
        prg.SetUniform("uColor", 0.0, sinf(time), 1.0);
        
        vao.DrawElements(VertexArray::TRIANGLE_FAN, 4, VertexArray::UNSIGNED_BYTE);
        
        win.SwapBuffers();
        win.PollEvents();
    }

    return 0;
}
