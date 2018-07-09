#pragma once
#ifndef _GL_HELPER_CORE_H
#define _GL_HELPER_CORE_H

#include "common.h"

// this glhelper is based on GLFW3 and GLAD
#include <iostream>
#include <string>

#ifdef _DEBUG

void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "[GLFW] Error %d: %s\n", error, description);
}

// reference: https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
// liam-middlebrook/GLDebugMessageCallback.c
void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar *msg, const void *data)
{
	std::string _source;
	std::string _type;
	std::string _severity;

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		_source = "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "WINDOW SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "SHADER COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "THIRD PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		_source = "UNKNOWN";
		break;
	default:
		_source = "UNKNOWN";
		break;
	}
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "DEPRECATED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "UDEFINED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		_type = "OTHER";
		break;
	case GL_DEBUG_TYPE_MARKER:
		_type = "MARKER";
		break;
	default:
		_type = "UNKNOWN";
		break;
	}
	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		_severity = "LOW";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "NOTIFICATION";
		break;
	default:
		_severity = "UNKNOWN";
		break;
	}
	fprintf(stderr, "[OPENGL] %d: %s of %s severity, raised from %s: %s\n",
		id, _type.c_str(), _severity.c_str(), _source.c_str(), msg);
}
#endif // _DEBUG

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window);
using namespace std;
namespace GLHelper
{
	class Core
	{
	public:
		GLuint width, height;
		string title;
		GLFWwindow *window;
		Core(int _width, int _height, string _title) :width(_width), height(_height), title(_title)
		{
#ifdef _DEBUG
			printf("DEBUG mode is on\n");
			// set glfw error callback
			glfwSetErrorCallback(glfw_error_callback);
#endif // _DEBUG
			// using OpenGL 4.3 core profile
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			// compatiable for apple
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
			// create glfw windows
			window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
			if (window == NULL)
			{
				fprintf(stderr, "[GLFW] Failed to create GLFW window");
				glfwTerminate();
				throw("Failed to create GLFW window");
			}
			// using this context
			glfwMakeContextCurrent(window);
			// load OpenGL functions
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				fprintf(stderr, "[GLAD] Failed to initialize GLAD");
				glfwTerminate();
				throw("Failed to initialize GLAD");
			}
#ifdef _DEBUG
			// set opengl debug message
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLDebugMessageCallback, 0);
#endif // _DEBUG
		}
		~Core()
		{
			glfwTerminate();
		}
		inline int shouldClose()
		{
			return glfwWindowShouldClose(window);
		}
		inline void mainloop()
		{
			//processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	};
}
#endif // !_GL_HELPER_CORE_H
