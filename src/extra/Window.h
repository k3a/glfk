/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/

class Window
{
    typedef void(*FramebufferSizeCallback) (unsigned width, unsigned height);
    typedef void(*KeyCallback)(int key, int scancode, int action, int mods);

public:
    Window();
    ~Window();

    bool Create(unsigned width, unsigned height, const char* title);
    void SwapBuffers();
    void PollEvents();
    bool ShouldClose();

    FramebufferSizeCallback SetFramebufferSizeCallback(FramebufferSizeCallback cb);
    Window::KeyCallback SetKeyCallback(KeyCallback cb);

private:
    struct sPrivate;
        sPrivate *_private;
};
