#pragma once
#ifndef _GL_HELPER_PROGRAM_H
#define _GL_HELPER_PROGRAM_H

#include "shader.h"
#include "common.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GLHelper
{
	class Program
	{
	public:
		GLuint ID;
		Program()
		{
			ID = glCreateProgram();
		}
		~Program()
		{
			glDeleteProgram(ID);
		}
		void attach(const Shader &shader)
		{
			glAttachShader(ID, shader.ID);
		}
		// attach a computer shader from path
		inline void attach(const char* compPath)
		{
			ID = glCreateProgram();
			Shader comp(compPath, COMPUTE_SHADER);
			attach(comp);
			link();
		}
		// attach a vert+(gemo)+frag shaders from paths
		inline void attach(const char* vertPath, const char* fragPath, const char* geomPath = nullptr)
		{
			ID = glCreateProgram();
			Shader vert(vertPath, VERTEX_SHADER);
			attach(vert);
			if (geomPath)
			{
				Shader geom(geomPath, GEOMETRY_SHADER);
				attach(geom);
			}
			if (fragPath)
			{
				Shader frag(fragPath, FRAGMENT_SHADER);
				attach(frag);
			}
			link();
		}
		inline void link()
		{
			glLinkProgram(ID);
			checkLinkErrors();
		}
		inline void use()
		{
			glUseProgram(ID);
		}
		// bool
		inline void setBool(const std::string &name, bool value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (GLint)value);
		}
		inline void setBool(const std::string &name, GLsizei count, bool *value) const
		{
			// it's ugly, but it works
			GLint *temp = new GLint[count]();
			for (int i = 0; i < count; i++)
			{
				temp[i] = (GLint)value[i];
			}
			glUniform1iv(glGetUniformLocation(ID, name.c_str()), count, temp);
			delete[] temp;
		}
		// float
		inline void setFloat(const std::string &name, GLfloat value) const
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}
		inline void setFloat(const std::string &name, GLsizei count, GLfloat *value) const
		{
			glUniform1fv(glGetUniformLocation(ID, name.c_str()), count, value);
		}
		// int
		inline void setInt(const std::string &name, GLint value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}
		inline void setInt(const std::string &name, GLsizei count, GLint *value) const
		{
			glUniform1iv(glGetUniformLocation(ID, name.c_str()), count, value);
		}
		// uint
		inline void setUint(const std::string &name, GLuint v0) const
		{
			glUniform1ui(glGetUniformLocation(ID, name.c_str()), v0);
		}
		inline void setUint(const std::string &name, GLsizei count, GLuint *v0) const
		{
			glUniform1uiv(glGetUniformLocation(ID, name.c_str()), count, v0);
		}
		// vec2
		inline void setVec2(const std::string &name, GLfloat x, GLfloat y) const
		{
			glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
		}
		inline void setVec2(const std::string &name, const glm::vec2 &value) const
		{
			glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setVec2(const std::string &name, GLsizei count, const glm::vec2 *value) const
		{
			glUniform2fv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// vec3
		inline void setVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z) const
		{
			glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
		}
		inline void setVec3(const std::string &name, const glm::vec3 &value) const
		{
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setVec3(const std::string &name, GLsizei count, const glm::vec3 *value) const
		{
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// vec4
		inline void setVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		{
			glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
		}
		inline void setVec4(const std::string &name, const glm::vec4 &value) const
		{
			glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setVec4(const std::string &name, GLsizei count, const glm::vec4 *value) const
		{
			glUniform4fv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// ivec2
		inline void setIvec2(const std::string &name, GLint x, GLint y) const
		{
			glUniform2i(glGetUniformLocation(ID, name.c_str()), x, y);
		}
		inline void setIvec2(const std::string &name, const glm::ivec2 &value) const
		{
			glUniform2iv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setIvec2(const std::string &name, GLsizei count, const glm::ivec2 *value) const
		{
			glUniform2iv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// ivec3
		inline void setIvec3(const std::string &name, GLint x, GLint y, GLint z) const
		{
			glUniform3i(glGetUniformLocation(ID, name.c_str()), x, y, z);
		}
		inline void setIvec3(const std::string &name, const glm::ivec3 &value) const
		{
			glUniform3iv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setIvec3(const std::string &name, GLsizei count, const glm::ivec3 *value) const
		{
			glUniform3iv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// ivec4
		inline void setIvec4(const std::string &name, GLint x, GLint y, GLint z, GLint w)
		{
			glUniform4i(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
		}
		inline void setIvec4(const std::string &name, const glm::ivec4 &value) const
		{
			glUniform4iv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setIvec4(const std::string &name, GLsizei count, const glm::ivec4 *value) const
		{
			glUniform4iv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}

		// uvec2
		inline void setUvec2(const std::string &name, GLuint x, GLuint y) const
		{
			glUniform2ui(glGetUniformLocation(ID, name.c_str()), x, y);
		}
		inline void setUvec2(const std::string &name, const glm::uvec2 &value) const
		{
			glUniform2uiv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setUvec2(const std::string &name, GLsizei count, const glm::uvec2 *value) const
		{
			glUniform2uiv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// uvec3
		inline void setUvec3(const std::string &name, GLuint x, GLuint y, GLuint z) const
		{
			glUniform3ui(glGetUniformLocation(ID, name.c_str()), x, y, z);
		}
		inline void setUvec3(const std::string &name, const glm::uvec3 &value) const
		{
			glUniform3uiv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setUvec3(const std::string &name, GLsizei count, const glm::uvec3 *value) const
		{
			glUniform3uiv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// uvec4
		inline void setUvec4(const std::string &name, GLuint x, GLuint y, GLuint z, GLuint w)
		{
			glUniform4ui(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
		}
		inline void setUvec4(const std::string &name, const glm::uvec4 &value) const
		{
			glUniform4uiv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
		}
		inline void setUvec4(const std::string &name, GLsizei count, const glm::uvec4 *value) const
		{
			glUniform4uiv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(value[0]));
		}
		// bvec2
		inline void setBvec2(const std::string &name, bool x, bool y) const
		{
			glUniform2i(glGetUniformLocation(ID, name.c_str()), (GLint)x, (GLint)y);
		}
		inline void setBvec2(const std::string &name, const glm::bvec2 &value) const
		{
			glm::ivec2 temp = glm::ivec2(value);
			glUniform2iv(glGetUniformLocation(ID, name.c_str()), 1, &temp[0]);
		}
		inline void setBvec2(const std::string &name, GLsizei count, const glm::bvec2 *value) const
		{
			glm::ivec2 *temp = new glm::ivec2[count]();
			for (int i = 0; i < count; i++)
			{
				temp[i] = glm::ivec2(value[i]);
			}
			glUniform2iv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(temp[0]));
			delete[] temp;
		}
		// bvec3
		inline void setBvec3(const std::string &name, bool x, bool y, bool z) const
		{
			glUniform3i(glGetUniformLocation(ID, name.c_str()), (GLint)x, (GLint)y, (GLint)z);
		}
		inline void setBvec3(const std::string &name, const glm::bvec3 &value) const
		{
			glm::ivec3 temp = glm::ivec3(value);
			glUniform3iv(glGetUniformLocation(ID, name.c_str()), 1, &temp[0]);
		}
		inline void setBvec3(const std::string &name, GLsizei count, const glm::bvec3 *value) const
		{
			glm::ivec3 *temp = new glm::ivec3[count]();
			for (int i = 0; i < count; i++)
			{
				temp[i] = glm::ivec3(value[i]);
			}
			glUniform3iv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(temp[0]));
			delete[] temp;
		}
		// bvec4
		inline void setBvec4(const std::string &name, bool x, bool y, bool z, bool w)
		{
			glUniform4i(glGetUniformLocation(ID, name.c_str()), (GLint)x, (GLint)y, (GLint)z, (GLint)w);
		}
		inline void setBvec4(const std::string &name, const glm::bvec4 &value) const
		{
			glm::ivec4 temp = glm::ivec4(value);
			glUniform4iv(glGetUniformLocation(ID, name.c_str()), 1, &temp[0]);
		}
		inline void setBvec4(const std::string &name, GLsizei count, const glm::bvec4 *value) const
		{
			glm::ivec4 *temp = new glm::ivec4[count]();
			for (int i = 0; i < count; i++)
			{
				temp[i] = glm::ivec4(value[i]);
			}
			glUniform4iv(glGetUniformLocation(ID, name.c_str()), count, glm::value_ptr(temp[0]));
			delete[] temp;
		}
		// mat*
		inline void setMat2(const std::string &name, const glm::mat2 &mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		inline void setMat3(const std::string &name, const glm::mat3 &mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		inline void setMat4(const std::string &name, const glm::mat4 &mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		// still remain some functions
	private:
		//// logger
		//std::shared_ptr<spdlog::logger> _logger;
		//// logger init
		//inline void set_logger()
		//{
		//	_logger = spdlog::get("Program");
		//	if (!_logger)
		//	{
		//		_logger = spdlog::stdout_logger_st("Program");
		//	}
		//}
		void checkLinkErrors()
		{
			GLint success;
			GLchar infoLog[1024];
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(ID, 1024, NULL, infoLog);
				// cstdio is faster
				fprintf(stderr,"[OPENGL] PROGRAM_LINK_FAIL: %s\n", infoLog);
				//_logger->error("Program linking failed: {}", infoLog);
			}
		}
	};
};

#endif // !_GL_HELPER_PROGRAM_H