#pragma once
#ifndef _GL_HELPER_FBO_H
#define _GL_HELPER_FBO_H

#include "common.h"
#include "texture.h"

namespace GLHelper
{
	class FrameBuffer
	{
	public:
		// framebuffer object name
		GLuint ID;
		// generate 1 fbo
		FrameBuffer()
		{
			glGenFramebuffers(1, &ID);
		}
		// delete this fbo
		~FrameBuffer()
		{
			glDeleteFramebuffers(1, &ID);
		}
		// bind to GL_FRAMEBUFFER
		inline void bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, ID);
		}
		// unbind this fbo
		inline void unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		// bind to some target
		inline void bind(GLenum target)
		{
			glBindFramebuffer(target, ID);
		}
		// unbind this fbo
		inline void unbind(GLenum target)
		{
			glBindFramebuffer(target, 0);
		}
		// 
		inline void textureLayer(GLenum attachment, const Texture &tex, GLint level, GLint layer)
		{
			glFramebufferTextureLayer(GL_FRAMEBUFFER, attachment, tex.ID, level, layer);
		}
		inline void texture3D(GLenum attachment, GLenum textarget, const Texture &tex, GLint level, GLint layer)
		{
			glFramebufferTexture3D(GL_FRAMEBUFFER, attachment, textarget, tex.ID, level, layer);
		}
		inline void texture2D(GLenum attachment, GLenum textarget, const Texture &tex, GLint level)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textarget, tex.ID, level);
		}
		inline void texture1D(GLenum attachment, GLenum textarget, const Texture &tex, GLint level)
		{
			glFramebufferTexture1D(GL_FRAMEBUFFER, attachment, textarget, tex.ID, level);
		}
	private:

	};
}

#endif // !_GL_HELPER_FBO_H
