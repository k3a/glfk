/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/

class Window
{
    typedef void(*FramebufferSizeCallback) (unsigned width, unsigned height);
    typedef void(*KeyCallback)(int key, int scancode, int action, int mods);

public:
    /// Create an instance
    Window();
    /// Create a window with specified width, height and title
    Window(unsigned width, unsigned height, const char* title, bool srgb= true);
    
    ~Window();

    /** Creates a GL context and window.
     \param srgb If true, creates a sRGB framebuffer and automatically does the conversion 
     from linear colors to sRGB when writing to the framebuffer.
     */
    bool Create(unsigned width, unsigned height, const char* title, bool srgb = true);
    bool Valid()const{ return _valid; };
    Window& SwapBuffers();
    Window& PollEvents();
    Window& GetFramebufferSize(int& width, int& height);
    bool ShouldClose();
    
    static void EnableDebugLog(bool enable);

    FramebufferSizeCallback SetFramebufferSizeCallback(FramebufferSizeCallback cb);
    Window::KeyCallback SetKeyCallback(KeyCallback cb);
    
    // helpers
    bool EndFrame(){ SwapBuffers(); PollEvents(); return ShouldClose(); };

private:
    struct sPrivate;
    sPrivate *_private;
    bool _valid;
};
