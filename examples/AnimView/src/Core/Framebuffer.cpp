#include "Framebuffer.h"

#include <glad/glad.h>

namespace AnimView {

Framebuffer::Framebuffer(int width, int height)
    : m_Width(width), m_Height(height)
{
    Create();
}

Framebuffer::~Framebuffer()
{
    Destroy();
}

void Framebuffer::Create()
{
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    // --- Color attachment (texture) ---
    glGenTextures(1, &m_ColorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

    // --- Depth + stencil (renderbuffer) ---
    glGenRenderbuffers(1, &m_DepthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Destroy()
{
    if (m_FBO)
    {
        glDeleteFramebuffers(1,   &m_FBO);
        glDeleteTextures(1,       &m_ColorAttachment);
        glDeleteRenderbuffers(1,  &m_DepthRBO);
        m_FBO             = 0;
        m_ColorAttachment = 0;
        m_DepthRBO        = 0;
    }
}

void Framebuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glViewport(0, 0, m_Width, m_Height);
}

void Framebuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(int width, int height)
{
    if (width == m_Width && height == m_Height)
        return;

    m_Width  = width;
    m_Height = height;
    Destroy();
    Create();
}

} // namespace AnimView
