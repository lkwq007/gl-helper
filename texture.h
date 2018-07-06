#pragma once
#ifndef _GL_HELPER_TEXTURE_H
#define _GL_HELPER_TEXTURE_H

#include "common.h"
#include <set>
#include <algorithm>

namespace GLHelper
{
	// the type of texturing target
	// only implement some API
	// I really need the DSA feature
	enum TextureType
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_1D_ARRAY,
		TEXTURE_2D_ARRAY,
		TEXTURE_RECTANGLE,
		TEXTURE_CUBE_MAP,
		TEXTURE_CUBE_MAP_ARRAY,
		TEXTURE_BUFFER,
		TEXTURE_2D_MULTISAMPLE,
		TEXTURE_2D_MULTISAMPLE_ARRAY,
		TEXTURE_TYPE_COUNT
	};
	GLenum GLTextureType[TEXTURE_TYPE_COUNT] =
	{
		GL_TEXTURE_1D,
		GL_TEXTURE_2D,
		GL_TEXTURE_3D,
		GL_TEXTURE_1D_ARRAY,
		GL_TEXTURE_2D_ARRAY,
		GL_TEXTURE_RECTANGLE,
		GL_TEXTURE_CUBE_MAP,
		GL_TEXTURE_CUBE_MAP_ARRAY,
		GL_TEXTURE_BUFFER,
		GL_TEXTURE_2D_MULTISAMPLE,
		GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	};
	// not the best practice, I guess
	class Texture
	{
	public:
		// Texture id/name
		GLuint ID;
		// Texture Unit
		GLint UNIT;
		// Texture type
		TextureType type;
		// create 1 texture
		Texture() :type()
		{
			glGenTextures(1, &ID);
			UNIT = fetchUnit();
		}
		Texture(TextureType _type) :type(_type)
		{
			glGenTextures(1, &ID);
			UNIT = fetchUnit();
			active();
			bind();
		}
		Texture(TextureType _type, GLint unit) :type(_type), UNIT(unit)
		{
			glGenTextures(1, &ID);
			active();
			bind();
		}
		~Texture()
		{
			glDeleteTextures(1, &ID);
			deleteUnit(UNIT);
		}
		// set type
		inline void setType(TextureType _type)
		{
			type = _type;
		}
		// int parameter
		inline void texParameter(GLenum pname, GLint param)
		{
			glTexParameteri(typeMap(type), pname, param);
		}
		// float parameter
		inline void texParameter(GLenum pname, GLfloat param)
		{
			glTexParameterf(typeMap(type), pname, param);
		}
		// tex image 2d, for cube texture, the target can be other GLenum
		inline void texImage(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data)
		{
			glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
		}
		// tex image 1d
		inline void texImage(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * data)
		{
			glTexImage1D(target, level, internalFormat, width, border, format, type, data);
		}
		// tex image 3d
		inline void texImage(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * data)
		{
			glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, data);
		}
		// checking whether this Texture object corresponds to a texture
		inline bool checkSelf()
		{
			return bool(glIsTexture(ID));
		}
		// checking whether this texture name corresponds to a texture
		static bool isTexture(GLuint tex)
		{
			return bool(glIsTexture(tex));
		}
		// active texture unit
		void active()
		{
			glActiveTexture(GL_TEXTURE0 + UNIT);
		}
		// bind target
		inline void bind()
		{
			glBindTexture(typeMap(type), ID);
		}
		// generate mipmaps, okay I cannot use glGenerateTextureMipmap()
		inline void generateMipmap()
		{
			glGenerateMipmap(typeMap(type));
		}
		// map the GLenum target
		static inline GLenum typeMap(TextureType _type)
		{
			return GLTextureType[int(_type)];
		}
		static GLint textureUnit;
		// record the textureUnits
		static std::set<GLint> reservedUnit;
		// for compatibility
		static void skipUnit(GLint temp)
		{
			reservedUnit.insert(temp);
		}
		// get and unused unit number
		static GLint fetchUnit()
		{
			auto search = reservedUnit.find(textureUnit);
			if (search != reservedUnit.end())
			{
				textureUnit++;
			}
			reservedUnit.insert(textureUnit);
			return textureUnit;
		}
		// delete unit
		static void deleteUnit(GLint unit)
		{
			reservedUnit.erase(unit);
		}
	private:
		//// logger
		//std::shared_ptr<spdlog::logger> _logger;
		//// logger init
		//inline void set_logger()
		//{
		//	_logger = spdlog::get("Texture");
		//	if (!_logger)
		//	{
		//		_logger = spdlog::stdout_logger_st("Texture");
		//	}
		//}
	};
	GLint Texture::textureUnit = 0;
}
#endif // !_GL_HELPER_TEXTURE_H