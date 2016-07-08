/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include <stdio.h>

#include "extra/Window.h"
#include "core/Renderer.h"

static void resize_cb(unsigned w, unsigned h) 
{
    printf("FB Resize: %ux%u\n", w, h);
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main()
{
    printf("Hey World!\n");

    Window win;
    win.Create(640, 480, "GLFK");
    win.SetFramebufferSizeCallback(resize_cb);

    R::ClearColor(0,1,1,0);
    while(!win.ShouldClose()) {
        R::Clear();

        win.EndFrame();
    }

    return 0;
}
