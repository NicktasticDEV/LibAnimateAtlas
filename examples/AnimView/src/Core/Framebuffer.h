#pragma once

namespace AnimView {

// Wraps an OpenGL Framebuffer Object (FBO) with a color texture attachment
// and a depth/stencil renderbuffer. Use Bind() before rendering your scene,
// then Unbind() when done. Pass GetColorAttachment() to ImGui::Image().
class Framebuffer {
public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    // Bind the FBO and set the GL viewport to match its size
    void Bind() const;

    // Restore the default framebuffer (screen)
    void Unbind() const;

    // Rebuild the FBO if the size changed (call when the panel is resized)
    void Resize(int width, int height);

    unsigned int GetColorAttachment() const { return m_ColorAttachment; }
    int GetWidth()  const { return m_Width; }
    int GetHeight() const { return m_Height; }

private:
    void Create();
    void Destroy();

private:
    unsigned int m_FBO             = 0;
    unsigned int m_ColorAttachment = 0;
    unsigned int m_DepthRBO        = 0;
    int m_Width;
    int m_Height;
};

} // namespace AnimView
