#pragma once
#ifndef _GL_HELPER_BUFFER_H
#define _GL_HELPER_BUFFER_H

#include "common.h"
namespace GLHelper
{
	class Buffer
	{
	public:
		GLuint ID;
		GLenum target;
		Buffer()
		{
			glGenBuffers(1, &ID);
		}
		~Buffer()
		{
			glDeleteBuffers(1, &ID);
		}
		inline void setTarget(GLenum _target)
		{
			target = _target;
		}
		inline void bind()
		{
			glBindBuffer(target, ID);
		}
		inline void unbind()
		{
			glBindBuffer(target, 0);
		}
		inline void data(GLsizeiptr size, const GLvoid * data, GLenum usage)
		{
			glBufferData(target, size, data, usage);
		}
		inline void subData(GLintptr offset, GLsizeiptr size, const GLvoid * data)
		{
			glBufferSubData(target, offset, size, data);
		}
	private:

	};
}

#endif // !_GL_HELPER_BUFFER_H