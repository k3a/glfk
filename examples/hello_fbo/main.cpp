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
#include "core/Framebuffer.h"
#include "core/Renderbuffer.h"

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
    uniform vec2 scale;
    in vec3 inPos;
    out vec2 vCoord;
    void main(){
        gl_Position = vec4(inPos * vec3(scale, 1), 1.0);
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

    BaseShader vs = VertexShader::FromString(vsSrc);
    if (!vs.Compile()) {
        std::cout << "VS Error: " << vs.GetInfoLog() << std::endl;
    }
    BaseShader fs = FragmentShader::FromString(fsSrc);
    if (!fs.Compile()) {
        std::cout << "FS Error: " << fs.GetInfoLog() << std::endl;
    }
    Program prg;
    prg.AttachShader(vs).AttachShader(fs);
    if (!prg.Link()) {
        std::cout << "Prog Error: " << prg.GetInfoLog() << std::endl;
    } else {
        std::cout << "Prog Compiled OK: " << prg.GetNumActiveAttributes()
            << " attrs, " << prg.GetNumActiveUniforms() << " uniforms" << std::endl;
    }

    VertexArray vao;
    
        ArrayBuffer bv(vao);
        bv.SetData(sizeof(unitSquareVertPos), unitSquareVertPos);
        bv.SetAttribPointer(prg.GetAttribute("inPos"), 3, AttribType::FLOAT);
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
    tex.SetTextureUnit(TextureUnit(0));
    prg.SetUniformTextureUnit("uTexture", tex.GetTextureUnit());
    
    // Framebuffer for offscreen rendering
    Framebuffer fb;
    std::cout << "Max color attachments: " << fb.GetMaxColorAttachments() << std::endl;
    
        // Renderbuffer for storing depth
        Renderbuffer rb;
        rb.SetStorage(GL_DEPTH_COMPONENT, 1024, 1024);
        fb.AttachRenderbuffer(GL_DEPTH_ATTACHMENT, rb);
    
        // Texture attachment for rendering color
        Texture2D rt;
        rt.SetEmptyImage(GL_RGBA8, 1024, 1024);
        rt.SetTextureUnit(TextureUnit(1));
        rt.SetFilter(MinFilterMode::NEAREST, MagFilterMode::NEAREST); // when set, mipmaps doesn't need to be generated
        fb.AttachTexture2D(GL_COLOR_ATTACHMENT0, rt, 0);
    
    if (fb.CheckStatus() != FramebufferStatus::FRAMEBUFFER_COMPLETE) {
        std::cout << "Incomplete framebuffer" << std::endl;
    }
    
    R::ClearColor(0,1,1,0);
    float time = 0;
    
    while(!win.ShouldClose()) {
        time += 0.01;
        
        // draw to FB
        fb.Bind();
        glViewport(0, 0, 1024, 1024); //TODO: needed?
        fb.Clear();
        prg.Use();
        prg.SetUniformTextureUnit("uTexture", tex.GetTextureUnit());
        prg.SetUniformFloat("scale", sinf(time), sinf(time));
        vao.DrawElements(DrawMode::TRIANGLE_FAN, 4, IndicesType::UNSIGNED_BYTE);
        
        // draw to window
        fb.Unbind();
        //rt.GenerateMipmap();
        
        R::Clear();

        prg.Use();
        prg.SetUniformFloat("scale", 1, 1);
        prg.SetUniformFloat("uColor", 0, sinf(time), 1);
        prg.SetUniformTextureUnit("uTexture", rt.GetTextureUnit());
        
        vao.DrawElements(DrawMode::TRIANGLE_FAN, 4, IndicesType::UNSIGNED_BYTE);
        
        
        
        win.EndFrame();
    }

    return 0;
}
