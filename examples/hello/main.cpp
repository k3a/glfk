/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#include <stdio.h>

#include "extra/Window.h"
#include "core/Renderer.h"

Window win(640, 480, "GLFK");

static void resize_cb(unsigned w, unsigned h) 
{
    printf("FB Resize: %ux%u\n", w, h);
    R::Viewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main()
{
    win.SetFramebufferSizeCallback(resize_cb);

    R::ClearColor(0,1,1,0);
    while(!win.ShouldClose()) {
        R::Clear();

        win.EndFrame();
    }

    return 0;
}
