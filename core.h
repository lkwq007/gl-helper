#pragma once
#ifndef _GL_HELPER_CORE_H
#define _GL_HELPER_CORE_H

#include "common.h"

// this glhelper is based on GLFW3 and GLAD
#include <iostream>
#include <string>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
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
			//set_logger();
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
				printf("[GLFW] Failed to create GLFW window");
				glfwTerminate();
				throw("Failed to create GLFW window");
			}
			// using this context
			glfwMakeContextCurrent(window);
			// load OpenGL functions
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				printf("[GLAD] Failed to initialize GLAD");
				glfwTerminate();
				throw("Failed to initialize GLAD");
			}
#ifdef DEBUG

#endif // DEBUG

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
		//// logger
		//std::shared_ptr<spdlog::logger> _logger;
		//// logger init
		//inline void set_logger()
		//{
		//	_logger = spdlog::get("Core");
		//	if (!_logger)
		//	{
		//		_logger = spdlog::stdout_logger_st("Core");
		//	}
		//}
	};
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


#endif // !_GL_HELPER_CORE_H
