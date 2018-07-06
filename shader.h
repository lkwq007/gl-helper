/*
reference: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
*/
#pragma once
#ifndef _GL_HELPER_SHADER_H
#define _GL_HELPER_SHADER_H

#include "common.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GLHelper
{
	enum ShaderType
	{
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		SHADERTYPE_COUNT
	};
	GLchar ShaderName[6][24] = {
		"VERTEX_SHADER",
		"GEOMETRY_SHADER",
		"FRAGMENT_SHADER",
		"COMPUTE_SHADER",
		"TESS_CONTROL_SHADER",
		"TESS_EVALUATION_SHADER"
	};
	// default file extension used by GLSLang
	GLchar ShaderExt[6][8] = {
		"vert",
		"geom",
		"frag",
		"tesc",
		"tese",
		"comp"
	};
	class Shader
	{
	public:
		GLuint ID;
		ShaderType type;
		// create shader from a string array
		Shader(GLsizei count, const GLchar** shaderCode, const GLint *length, ShaderType _type) : type(_type)
		{
			// set logger
			//set_logger();
			// create and compile the shader
			construct(count, shaderCode, length);
		};
		// read shader code from file with specified extension
		Shader(const GLchar* shaderPath)
		{
			// set logger
			//set_logger();
			// judge shader type
			getTypeFromExt(shaderPath);
			std::string shaderStr = readCode(shaderPath);
			// get shader code
			const char *shaderCode = shaderStr.c_str();
			// create and compile the shader
			construct(shaderCode);
		};
		// read shader code from file with specified type
		Shader(const GLchar* shaderPath, ShaderType _type) : type(_type)
		{
			// set logger
			//set_logger();
			// read shader file
			std::string shaderStr = readCode(shaderPath);
			// get shader code
			const char *shaderCode = shaderStr.c_str();
			// create and compile the shader
			construct(shaderCode);
		};
		// just delete the shader
		~Shader()
		{
			// delete the shader
			glDeleteShader(ID);
		}
	private:
		//// logger
		//std::shared_ptr<spdlog::logger> _logger;
		//// logger init
		//inline void set_logger()
		//{
		//	_logger = spdlog::get("Shader");
		//	if (!_logger)
		//	{
		//		_logger = spdlog::stdout_logger_st("Shader");
		//	}
		//}
		// map ShaderType to GLenum shader type
		inline GLenum typeMap(ShaderType type)
		{
			GLenum ret;
			switch (type)
			{
			case GLHelper::VERTEX_SHADER:
				ret = GL_VERTEX_SHADER;
				break;
			case GLHelper::GEOMETRY_SHADER:
				ret = GL_GEOMETRY_SHADER;
				break;
			case GLHelper::FRAGMENT_SHADER:
				ret = GL_FRAGMENT_SHADER;
				break;
			case GLHelper::COMPUTE_SHADER:
				ret = GL_COMPUTE_SHADER;
				break;
			case GLHelper::TESS_CONTROL_SHADER:
				ret = GL_TESS_CONTROL_SHADER;
				break;
			case GLHelper::TESS_EVALUATION_SHADER:
				ret = GL_TESS_EVALUATION_SHADER;
				break;
			default:
				ret = GL_VERTEX_SHADER;
				break;
			}
			return ret;
		}
		// map ShaderType to ShaderName
		inline GLchar *nameMap(ShaderType type)
		{
			return ShaderName[type];
		}
		// infer the type using Khronos' convention
		void getTypeFromExt(const GLchar* shaderPath)
		{
			std::string path = std::string(shaderPath);
			std::string ext = path.substr(path.find_last_of(".") + 1);
			for (int i = 0; i < SHADERTYPE_COUNT; i++)
			{
				if (ext == ShaderExt[i])
				{
					type = ShaderType(i);
					return;
				}
			}
			type = ShaderType(0);
		}
		// check compile errors
		std::string readCode(const GLchar* shaderPath)
		{
			// retrieve source code from filepath
			std::string shaderStr;
			std::ifstream shaderFile;
			// exceptions for ifstream object
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				// open file
				shaderFile.open(shaderPath);
				std::stringstream shaderStream;
				// read file's buffer content into stream
				shaderStream << shaderFile.rdbuf();
				// close file
				shaderFile.close();
				// get string
				shaderStr = shaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				// reading file fails
				//_logger->error("Read \"{}\" failed", shaderPath);
				printf("[OPENGL]SHADER_READ_FAIL: %s\n", shaderPath);
				shaderStr.empty();
			}
			return shaderStr;
		}
		void checkCompileErrors()
		{
			GLint success;
			GLchar infoLog[1024];
			glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(ID, 1024, NULL, infoLog);
				// std::cout << infoLog << std::endl;
				// _logger->error("{} compilation error: {}", ShaderName[type], infoLog);
				printf("[OPENGL]SHADER_COMPILATION_FAIL: %s\n", infoLog);
			}
		}
		// construct the shader
		void construct(const GLchar *shaderCode)
		{
			ID = glCreateShader(typeMap(type));
			glShaderSource(ID, 1, &shaderCode, NULL);
			glCompileShader(ID);
			checkCompileErrors();
		}
		// construct the shader
		void construct(GLsizei count, const GLchar** shaderCode, const GLint *length)
		{
			ID = glCreateShader(typeMap(type));
			glShaderSource(ID, count, shaderCode, length);
			glCompileShader(ID);
			checkCompileErrors();
		}
	};
}
#endif // !_GL_HELPER_SHADER_H
