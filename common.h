#pragma once
#ifndef _COMMON_H
#define _COMMON_H
// only 5th+ Generation Intel Core Processors support OpenGL 4.5, so I still use OpenGL 4.3
// cannot use new `glCreate*` functions
// but the compute shader and debug callback are great
// GLAD & GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//// spdlog
//// we need logging
//#include <spdlog/spdlog.h>

#include <cstdio>
#include <string>

inline void checkErrors(std::string desc) {
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		fprintf(stderr,"[OpenGL] Error in \"%s\": (%d)\n", desc.c_str(), e);
	}
}

#endif // !_COMMON_H