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

static const char* vsSrc = GLSL150(
    uniform vec2 u_vScale;
                                   
    in vec3 a_vPos;
                                   
    out vec2 v_vCoord;
                                   
    void main(){
        gl_Position = vec4(a_vPos * vec3(u_vScale, 1), 1.0);
        v_vCoord = a_vPos.xy * 0.5 + 0.5;
    }
);

static const char* fsSrc = GLSL150(
    uniform vec3 u_vColor;
    uniform sampler2D u_sTexture;
                                   
    in vec2 v_vCoord;
                                   
    out vec4 f_vColor;

    void main() {
        f_vColor = vec4( texture(u_sTexture, v_vCoord.xy).rgb + u_vColor/2.0 , 1.0);
    }
);

static glm::vec2 s_screenFbSize;
static glm::vec2 s_fbSize = glm::vec2(1024, 1024);

static void resize_cb(unsigned w, unsigned h) 
{
    std::cout << "FB Resize: " << w << "x" << h << std::endl;
    s_screenFbSize = glm::vec2(w, h);
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
    bv.SetAttribPointer(prg.GetAttribute("a_vPos"), 3, AttribType::FLOAT);
    vao.EnableAttribArray(prg.GetAttribute("a_vPos"));
    
    Texture2D tex;
    unsigned char texData[] = {
        255, 0, 0, 255,  0, 255, 0, 255,
        0, 0, 255, 255,  255, 255, 0, 255
    };
    tex.SetImage(0, InternalFormat::RGB, 2, 2, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    tex.GenerateMipmap();
    tex.SetTextureUnit(TextureUnit(0));
    prg.SetUniformTextureUnit("uTexture", tex.GetTextureUnit());
    
    // Framebuffer for offscreen rendering
    Framebuffer fb;
    std::cout << "Max color attachments: " << fb.GetMaxColorAttachments() << std::endl;
    
        // Renderbuffer for storing depth
        Renderbuffer rb;
        rb.SetStorage(InternalFormat::DEPTH_COMPONENT, s_fbSize.x, s_fbSize.y);
        fb.AttachRenderbuffer(GL_DEPTH_ATTACHMENT, rb);
    
        // Texture attachment for rendering color
        Texture2D rt;
        rt.SetEmptyImage(InternalFormat::RGBA8, s_fbSize.x, s_fbSize.y);
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
        
        // draw to the framebuffer
        
        fb.Bind();
        R::Viewport(0, 0, 1024, 1024);
        
        R::Clear();
        
        prg.Use();
        prg.SetUniformTextureUnit("u_sTexture", tex.GetTextureUnit());
        prg.SetUniformFloat("u_vScale", (1.0+sinf(time))/2.0, (1.0+sinf(time))/2.0);
        vao.DrawArrays(DrawMode::TRIANGLE_FAN, 0, 4);
   
        // draw to window
        
        Screen().Bind();
        R::Viewport(0, 0, s_screenFbSize.x, s_screenFbSize.y);
        
        R::Clear();
        
        prg.Use();
        prg.SetUniformFloat("u_vScale", 1, 1);
        prg.SetUniformFloat("u_vColor", 0, 0, 0);
        prg.SetUniformTextureUnit("u_sTexture", rt.GetTextureUnit());
        
        vao.DrawArrays(DrawMode::TRIANGLE_FAN, 0, 4);
        
        
        
        win.EndFrame();
    }

    return 0;
}
