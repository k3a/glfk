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

static const char* vsSrc = GLSL150(
    in vec3 inPos;
    out vec2 vCoord;
    void main(){
        gl_Position = vec4(inPos, 1.0);
        vCoord = inPos.xy * 0.5 + 0.5;
    }
);
static const char* fsSrc = GLSL150(
    in vec2 vCoord;
    out vec4 outColor;
    uniform vec3 uColor;
    uniform sampler2D uTexture;
    void main() {
        outColor = vec4( texture(uTexture, vCoord.xy).rgb + uColor/2.0 , 1.0);
    }
);

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

    // vertex shader
    BaseShader vs = VertexShader::FromString(vsSrc);
    if (!vs.Compile()) {
        std::cout << "VS Error: " << vs.GetInfoLog() << std::endl;
    }
    // fragment shader
    BaseShader fs = FragmentShader::FromString(fsSrc);
    if (!fs.Compile()) {
        std::cout << "FS Error: " << fs.GetInfoLog() << std::endl;
    }
    // shading program
    Program prg;
    prg.AttachShader(vs).AttachShader(fs);
    if (!prg.Link()) {
        std::cout << "Prog Error: " << prg.GetInfoLog() << std::endl;
    } else {
        std::cout << "Prog Compiled OK: " << prg.GetNumActiveAttributes()
            << " attrs, " << prg.GetNumActiveUniforms() << " uniforms" << std::endl;
    }

    // vertex array object
    VertexArray vao;
    
        // vertex buffer
        ArrayBuffer bv(vao);
        bv.SetData(sizeof(unitSquareVertPos), unitSquareVertPos);
        bv.SetAttribPointer(prg.GetAttribute("inPos"), 3, AttribType::FLOAT);
        vao.EnableAttribArray(prg.GetAttribute("inPos"));

        // index buffer
        ElementArrayBuffer bi(vao);
        bi.SetData(sizeof(unitSquareInd), unitSquareInd);
        
    
    // 2D texture
    Texture2D tex;
    unsigned char texData[] = {
        255, 0, 0, 255,  0, 255, 0, 255,
        0, 0, 255, 255,  255, 255, 0, 255
    };
    tex.SetImage(0, GL_RGB, 2, 2, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    tex.GenerateMipmap();
    tex.SetTextureUnit(TextureUnit(0));
    
    // set texture to program uniform
    prg.SetUniformTextureUnit("uTexture", tex.GetTextureUnit());
    
    // specify clear color
    R::ClearColor(0,1,1,0);
    
    float time = 0;
    while(!win.ShouldClose()) {
        time += 0.01;
        // clear the buffer
        R::Clear();

        // use and set the uniform of a program
        prg.Use();
        prg.SetUniformFloat("uColor", 0, sinf(time), 1);
        
        // draw elements of VAO
        vao.DrawElements(DrawMode::TRIANGLE_FAN, 4, IndicesType::UNSIGNED_BYTE);
        
        // swap buffes and poll events
        win.EndFrame();
    }

    return 0;
}
