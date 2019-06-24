#pragma once

#include <glad/glad.h>
#include <IL/devil_cpp_wrapper.hpp>

namespace ImageLibrary 
{
	class ImageLoader
	{
	public:
		GLuint loadImage(string img)
		{
			ILboolean status = ilLoadImage(img.c_str());
			if (status == IL_FALSE)
			{
				fprintf(stderr, "COULD NOT LOAD IMAGE: %s", img.c_str());
			}

			int Width = ilGetInteger(IL_IMAGE_WIDTH);
			int Height = ilGetInteger(IL_IMAGE_HEIGHT);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				Width,
				Height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				ilGetData()
			);

			glBindTexture(GL_TEXTURE_2D, 0);

			return texture;
		}
	};

	class ImageRenderer
	{
	public:
		void RenderImage(GLuint texture_id, int x, int y, int w, int h)
		{

		}
	};

};