#pragma once
#ifndef _GL_HELPER_RBO_H
#define _GL_HELPER_RBO_H

#include "common.h"

namespace GLHelper
{
	class RenderBuffer
	{
	public:
		GLuint ID;
		GLsizei width, height;
		GLenum format;
		RenderBuffer()
		{
			glGenRenderbuffers(1, &ID);
		}
		~RenderBuffer()
		{
			glDeleteRenderbuffers(1, &ID);
		}
		// establish data storage for rbo
		inline void storage()
		{
			glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
		}
		// establish data storage, format, dimensions and sample count of a renderbuffer object's image
		inline void storageMultisample(GLsizei samples, GLenum internalFormat, GLsizei _width, GLsizei _height)
		{
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, _width, _height);
		}
		// set size
		inline void setSize(GLsizei _width, GLsizei _height)
		{
			width = _width;
			height = _height;
		}
		// set format
		inline void setFormat(GLenum _format)
		{
			format = _format;
		}
		// bind this render buffer
		inline void bind()
		{
			// the target must be GL_RENDERBUFFER
			glBindRenderbuffer(GL_RENDERBUFFER, ID);
		}
		// unbind this render buffer
		inline void unbind()
		{
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	private:

	};
}

#endif // !_GL_HELPER_RBO_H