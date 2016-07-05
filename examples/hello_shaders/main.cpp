#include <stdio.h>

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
in vec3 inPos;\n\
void main(){ \n\
	gl_Position = vec4(inPos, 1.0); \n\
} \n\
";
static const char* fsSrc = "\
#version 150 \n\
out vec4 outColor;\
void main() { \n\
	outColor = vec4(1,0,0,1); \n\
}";

static void resize_cb(unsigned w, unsigned h) 
{
	printf("FB Resize: %ux%u\n", w, h);
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main()
{
	Window win;
	win.Create(640, 480, "GLFK");
	win.SetFramebufferSizeCallback(resize_cb);

	BaseShader* vs = VertexShader::FromString(vsSrc);
	if (!vs->Compile()) {
		std::string log = vs->GetInfoLog();
		printf("VS Error: %s\n", log.c_str());
	}
	BaseShader* fs = FragmentShader::FromString(fsSrc);
	if (!fs->Compile()) {
		std::string log = fs->GetInfoLog();
		printf("FS Error: %s\n", log.c_str());
	}
	Program prg;
	prg.AttachShader(*vs).AttachShader(*fs);
	if (!prg.Link()) {
		std::string log = prg.GetInfoLog();
		printf("Prog Link Error: %s\n", log.c_str());
	}

	VertexArray va;
	va.Bind();
		ArrayBuffer bv;
		bv.SetData(sizeof(unitSquareVertPos), unitSquareVertPos);
		bv.SetAttribPointer(0, 3, GL_FLOAT);
		va.EnableAttribArray(0);

		ElementArrayBuffer bi;
		bi.SetData(sizeof(unitSquareInd), unitSquareInd);
	va.Unbind();

	R::ClearColor(0,1,1,0);
	while(!win.ShouldClose()) {
		R::Clear();

		prg.Use();
		va.Bind();
		R::DrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE);
		va.Unbind();

		win.SwapBuffers();
		win.PollEvents();
	}

	return 0;
}
