
class Window
{
	typedef void(*FramebufferSizeCallback) (unsigned width, unsigned height);

public:
	Window();
	~Window();

	bool Create(unsigned width, unsigned height, const char* title);
	void SwapBuffers();
	void PollEvents();
	bool ShouldClose();

	FramebufferSizeCallback SetFramebufferSizeCallback(FramebufferSizeCallback cb);

private:
	struct sPrivate;
   	sPrivate *_private;
};
