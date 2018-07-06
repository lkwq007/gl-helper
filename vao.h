#pragma once
#ifndef _GL_HELPER_VAO_H
#define _GL_HELPER_VAO_H

#include "common.h"

namespace GLHelper
{
	class VertexArray
	{
	public:
		GLuint ID;
		VertexArray()
		{
			glGenVertexArrays(1, &ID);
		}
		~VertexArray()
		{
			glDeleteVertexArrays(1, &ID);
		}
		inline void bind()
		{
			glBindVertexArray(ID);
		}
		inline void unbind()
		{
			glBindVertexArray(0);
		}
	private:

	};
}

#endif // !_GL_HELPER_VAO_H